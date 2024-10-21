use std::cmp::PartialEq;
use std::sync::{Arc, RwLock};
use tokio::io::{AsyncReadExt};
use tokio::{net, runtime};
use crate::request::{Method,Resource,Request};
use crate::route::{Route};
use crate::respond::{Respond};

pub struct Server {
    listener_addr: &'static str,
    listener_port: i32,
    status: bool,
    routes:RwLock<Vec<Route>>,
}
impl Server {
    pub fn new(listener_port:i32) -> Arc<Self> {
        if listener_port < 1 || listener_port > 65535 {
            panic!("listener port must be between 1 and 65535");
        }
        Arc::new(
            Self {
                listener_addr: "127.0.0.1",
                listener_port,
                status: false,
                routes: RwLock::new(Vec::new()),
            }
        )
    }
    pub fn start(self: Arc<Self>) {
        let address=format!("{}:{}", self.listener_addr, self.listener_port);
        let rt = runtime::Runtime::new().unwrap();
        println!("Listening on {}", address);
        let listener =rt.block_on(async { net::TcpListener::bind(address).await.expect("Failed to bind listener") });
        rt.block_on(self.receive(listener));
    }
}


impl Server {
    async fn receive(self:Arc<Self>,listener:net::TcpListener) {
        loop {
            let (mut socket, _) = listener.accept().await.expect("Failed to accept connection");
            let server = self.clone();
            tokio::spawn(async move {
                let mut buf = [0; 1024];
                if let Err(e) = socket.read(&mut buf).await {
                    println!("Failed to read from socket: {}", e);
                    return;
                }
                let content = match String::from_utf8(buf.to_vec()) {
                    Ok(s) => s,
                    Err(e1) => {
                        println!("Failed to convert buffer to string: {}", e1);
                        return;
                    }
                };
                let request = match Request::build(content) {
                    Some(req) => req,
                    None => {
                        println!("Request parsing failed");
                        return;
                    }
                };
                let respond=Respond::build(socket);
                for route in server.routes.read().expect("Unable to read route").iter() {
                    if request.method() == &route.method && request.path() == &route.path {
                        (route.function)(request, respond);
                        return;
                    }
                }
                respond.body("Not Found".to_string());
                respond.status_message("Not Found".to_string());
                respond.status_code("403".to_string());
                respond.send();
                return;
            });
        }
    }
}

impl Server {
    pub fn route(self:&Arc<Self>, path: &'static str, method: &'static str, function: impl Fn(Request, Arc<Respond>) + Send + Sync + 'static) {
        let tmp_method=method.to_uppercase().as_str().into();
        let tmp_path;
        if path.ends_with("/") && path.len() > 1 {
            tmp_path=path.trim_end_matches("/").into();
        }else {
            tmp_path=path.into();
        }
        if tmp_method == Method::Uninitialized {panic!("该方法未被定义")}
        let route = Route { path:tmp_path, method:tmp_method, function: Box::new(function) };
        self.routes.write().expect("Route write failed").push(route);
    }
}
