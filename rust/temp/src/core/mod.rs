use tokio::io::{AsyncReadExt, AsyncWriteExt};
use tokio::{net, runtime};
use tokio::sync;


pub struct Server {
    listener_addr: &'static str,
    listener_port: i32,
    status: bool,
    route_vec:Vec<(&'static str,&'static str)>,
}
impl Server {
    pub fn new(listener_port:i32) -> Self {
        if listener_port < 1 || listener_port > 65535 {
            panic!("listener port must be between 1 and 65535");
        }
        Self {
            listener_addr: "127.0.0.1",
            listener_port,
            status: false,
            route_vec: Vec::new(),
        }
    }
    pub fn start(&self) {
        let address=format!("{}:{}", self.listener_addr, self.listener_port);
        let rt = runtime::Runtime::new().unwrap();
        println!("Listening on {}", address);
        let listener =rt.block_on(async { net::TcpListener::bind(address).await.expect("Failed to bind listener") });
        rt.block_on(Self::receive(listener))
    }
    async fn receive(listener:net::TcpListener) {
        loop {
            let (mut socket, _) = listener.accept().await.expect("Failed to accept connection");
            tokio::spawn(async move {
                println!("监听成功");
                let mut buf = [0; 1024];
                socket.read(&mut buf).await.unwrap();
                socket.write_all(b"Hello, World!").await.unwrap();
            });
        }
    }
}