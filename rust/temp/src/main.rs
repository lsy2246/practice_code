use core::Server;
mod core;
mod request;
mod respond;
mod route;

fn main() {
    let server = Server::new( 8000);
    server.route("/","get",|request, respond| {
        respond.send();
        println!("{}",request.method())
    });
    server.start();
}