use std::cell::RefCell;
use std::rc::Rc;

struct Link {
    value: String,
    next:Option<Rc<RefCell<Link>>>,
    back:Option<Rc<RefCell<Link>>>
}

impl Link {
    fn init(content:&str) -> Option<Rc<RefCell<Link>>> {
        let link=Rc::new(RefCell::new(Link{value:String::from(content),next:None,back:None}));
        link.borrow_mut().next = Some(Rc::clone(&link));
        link.borrow_mut().back = Some(Rc::clone(&link));
     Some(link)
    }
    fn add(old_link:Option<Rc<RefCell<Link>>>,content:&str) -> Option<Rc<RefCell<Link>>> {
        let old_link_ref=old_link.as_ref();
        let new_link=Rc::new(RefCell::new(Link{
            value:String::from(content),
            next:Some(Rc::clone(old_link_ref?.borrow().next.as_ref()?)),
            back:Some(Rc::clone(old_link_ref?))
        }));

        let back_link=old_link_ref?.borrow().back.clone()?;
        if Rc::ptr_eq(old_link_ref?, old_link_ref?.borrow().back.as_ref()?) {
            back_link.borrow_mut().back = Some(Rc::clone(&new_link));
        }
        back_link.borrow_mut().next = Some(Rc::clone(&new_link));
        Some(new_link)
    }
    fn del(link:Option<Rc<RefCell<Link>>>) -> Option<Rc<RefCell<Link>>> {
        let link_ref=link.clone()?;
        let back_link=link_ref.borrow().back.clone()?;
        let next_link=link_ref.borrow().next.clone()?;
        if Rc::ptr_eq(&link_ref, &next_link) {
            drop(link);
            None
        }else {
            back_link.borrow_mut().next=Some(Rc::clone(&next_link));
            next_link.borrow_mut().back=Some(Rc::clone(&back_link));
            Some(next_link)
        }
    }

}

fn main() {
    let link=Link::init("lsy");
    let new_link=Link::add(link,"input");
    let n_n_link=Link::del(new_link);
    let n_n_nlink=Link::del(n_n_link);
    if let None=n_n_nlink {
        println!("删除成功")
    }
}