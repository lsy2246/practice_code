use std::sync::Arc;
use crate::request::{Method, Request};
use crate::respond::{Respond};

pub(crate) struct Route {
    pub path: &'static str,
    pub method: Method,
    pub function: Box<dyn Fn(Request,Arc<Respond>) + Send + Sync>,
}

