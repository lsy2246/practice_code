use std::collections::HashMap;
use std::sync::Arc;
use tokio::sync::Mutex;
use tokio::io::AsyncWriteExt;
use tokio::net::TcpStream;
use tokio::task;

pub struct Respond<'a>{
    version:&'a str,
    status_code:&'a str,
    status_message:&'a str,
    headers:HashMap<&'a str, &'a str>,
    body:&'a str,
    socket:Arc<Mutex<TcpStream>>
}


impl Respond<'_> {
    pub fn build(socket: TcpStream) -> Arc<Respond<'static>> {
        Arc::new(Respond {
            version: "HTTP/1.1",
            status_code: "200",
            status_message: "OK",
            headers: HashMap::new(),
            body: "Hello, world!",
            socket: Arc::new(Mutex::new(socket))
        })
    }
    fn format_message(self:Arc<Self>) -> String {
        let mut massage =String::new();
        let status_line= format!("{} {} {}\r\n", self.status_message,self.version,self.status_message);
        massage.push_str(&status_line);
        let mut header =String::new();
        for (key, value) in self.headers.iter() {
            header += &format!("{}: {}\r\n", key, value);
        }
        massage.push_str("\n\n");
        massage.push_str(self.body);
        massage
    }

    pub fn send(self: Arc<Self>) {
        let socket = self.socket.clone();
        let message = self.format_message();

        task::spawn(async move {
            let mut socket = socket.lock().await;
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



