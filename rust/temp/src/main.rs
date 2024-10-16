use core::Server;
mod core;

fn main() {
    let server = core::Server::new( 8000);
    server.start();
}