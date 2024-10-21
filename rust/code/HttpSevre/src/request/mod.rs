use std::collections::HashMap;
use std::fmt::Display;
use std::path::Path;

pub enum Method {
    Get,
    Post,
    Uninitialized
}

impl From<&str> for Method {
    fn from(s: &str) -> Method {
        match s{
            "GET" => Method::Get,
            "POST" => Method::Post,
            _ => Method::Uninitialized
        }
    }
}

impl Display for Method {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        let method = match self {
            Method::Get => {"GET"}
            Method::Post => {"POST"}
            Method::Uninitialized => {"Uninitialized"}
        };
        write!(f, "{}", method)
    }
}

impl PartialEq for Method {
    fn eq(&self, other: &Self) -> bool {
        match (self, other) {
            (Method::Get, Method::Get) => true,
            (Method::Post, Method::Post) => true,
            (Method::Uninitialized, Method::Uninitialized) => true,
            _ => false,
        }
    }
}

pub enum Version {
    V1_1,
    Uninitialized
}

impl From<&str> for Version {
    fn from(s: &str) -> Version {
        match s {
            "HTTP/1.1" => Version::V1_1,
            _ => Version::Uninitialized
        }
    }
}

pub enum Resource{
    Path(String),
}

impl PartialEq for &Resource {
    fn eq(&self, other: &Self) -> bool {
        match (self,other) {
            (Resource::Path(path), Resource::Path(other)) => path == other,
        }
    }
}


impl Display for Resource {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        match self {
            Resource::Path(path) => write!(f, "{}", path),
        }
    }
}

impl From<&str> for Resource {
    fn from(s: &str) -> Resource {
        match s{
            s => Resource::Path(s.to_string()),
        }
    }
}


pub struct Request{
    method: Method,
    version: Version,
    resource: Resource,
    headers: HashMap<String, String>,
}

impl Request{
    pub fn build(content:String) -> Option<Request>{
        let mut content =content.lines();

        let request_line =content.next().unwrap_or("");
        if request_line.is_empty(){return None}
        let request_line:Vec<_> = request_line.split_whitespace().collect();
        if request_line.len()<3 {return None}
        let method=request_line[0];
        let resource=request_line[1];

        let version=request_line[2];
        if method.is_empty()||resource.is_empty()||version.is_empty() {return None}

        let mut headers =HashMap::<String, String>::new();
        for i in content {
            if i.len()==0 { break;}
            let parts:Vec<&str> = i.split(": ").collect();
            if parts.len() == 2 {
                headers.insert(parts[0].to_string(), parts[1].to_string());
            }
        };

        Some(Request{
            method: method.into(),
            version: version.into(),
            resource: resource.into(),
            headers,
        })
    }
}

impl Request {
    pub fn method(&self) -> &Method {
        &self.method
    }
    pub fn path(&self) -> &Resource {
        &self.resource
    }
}
