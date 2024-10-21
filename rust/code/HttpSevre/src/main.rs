use core::Server;
mod core;
mod request;
mod respond;
mod route;

fn main() {
    let server = Server::new( 8000);
    server.route("/","get",|request, respond| {
        respond.body(String::from("lsy"));
        respond.send();
    });
    server.route("/admin","get",|request, respond| {
        respond.send();
    });
    server.start();
}