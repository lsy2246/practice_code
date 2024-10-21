use std::sync::Arc;
use crate::request::{Method,Resource, Request};
use crate::respond::{Respond};


pub(crate) struct Route {
    pub path: Resource,
    pub method: Method,
    pub function: Box<dyn Fn(Request,Arc<Respond>) + Send + Sync>,
}

