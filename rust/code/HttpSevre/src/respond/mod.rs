use std::collections::HashMap;
use std::sync::Arc;
use tokio::sync::Mutex;
use tokio::io::AsyncWriteExt;
use tokio::net::TcpStream;
use tokio::task;


pub struct Respond{
    version:Mutex<String>,
    status_code:Mutex<String>,
    status_message:Mutex<String>,
    headers:Mutex<HashMap<String, String>>,
    body:Mutex<String>,
    socket:Arc<Mutex<TcpStream>>
}


impl Respond {
    pub fn build(socket: TcpStream) -> Arc<Respond> {
        Arc::new(Respond {
            version: Mutex::new("HTTP/1.1".to_string()),
            status_code: Mutex::new("200".to_string()),
            status_message: Mutex::new("OK".to_string()),
            headers: Mutex::new(HashMap::new()),
            body: Mutex::new("Hello, world!".to_string()),
            socket: Arc::new(Mutex::new(socket))
        })
    }
    pub fn format_message(self: &Arc<Self>) -> String {
        task::block_in_place(|| {
            let self_ref = self.clone();
            let mut massage = String::new();
            let mut header = String::new();

            tokio::runtime::Handle::current().block_on(async {
                let version = self_ref.version.lock().await;
                let status_code = self_ref.status_code.lock().await;
                let status_message = self_ref.status_message.lock().await;

                massage.push_str(format!("{} {} {}\r\n", version, status_code, status_message).as_str());

                for (key, value) in self_ref.headers.lock().await.iter() {
                    header += &format!("{}: {}\r\n", key, value);
                }
                massage.push_str(&header);
                massage.push_str("\r\n");
                let body = self_ref.body.lock().await.to_string();
                massage.push_str(body.as_str());
            });

            massage
        })
    }

    pub fn send(self: &Arc<Self>) {
        let self_ref = self.clone();
        task::spawn(async move {
            let message = self_ref.format_message();
            let mut socket = self_ref.socket.lock().await;
            if let Ok(_) = socket.write_all(message.as_ref()).await {
                if let Err(e) = socket.flush().await {
                    println!("Failed to flush: {}", e);
                }
            } else {
                println!("Failed to send content");
            }
        });
    }
}

impl Respond {
    pub fn body(self: &Arc<Self>,content:String) {
        let self_ref = self.clone();
        tokio::spawn(async move {
            let mut body = self_ref.body.lock().await;
            *body = content;
        });
    }
    pub fn status_code(self: &Arc<Self>,code:String) {
        let self_ref = self.clone();
        tokio::spawn(async move {
            let mut status_code = self_ref.status_code.lock().await;
            *status_code = code;
        });
    }
    pub fn status_message(self: &Arc<Self>,massage:String) {
        let self_ref = self.clone();
        tokio::spawn(async move {
            let mut status_message = self_ref.status_message.lock().await;
            *status_message = massage;
        });
    }
}



