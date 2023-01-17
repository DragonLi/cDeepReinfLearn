#[macro_use] extern crate scan_fmt;
use std::error::Error ;
fn main() -> Result<(),Box<dyn Error>> {
    let (a,b,c) = scan_fmt!( "hello 0x12 345 bye",  // input string
                            "hello {x} {} {}",     // format
                            [hex u8], i32, String) ? ;   // type of a-c Options
    assert_eq!( a, 0x12 ) ;
    assert_eq!( b, 345 ) ;
    assert_eq!( c, "bye" ) ;

    println!("Enter something like: 123-22");
    let (c,d) = scanln_fmt!( "{d}-{d}", // format
                            u16, u8) ? ;  // type of a&b Options
    println!("Got {} and {}",c,d) ;
    // Note - currently scanln_fmt! just calls unwrap() on read_line()

    let (a,b) = scan_fmt_some!( "hello 12 345", // input string
                               "hello {} {}",   // format
                               u8, i32) ;   // types
    assert_eq!( a, Some(12) ) ;
    assert_eq!( b, Some(345) ) ;
    Ok(())
}