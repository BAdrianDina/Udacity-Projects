// first rust programm, hello world


// Seome useful informations:
// 1. the sign ! calls a macro and not a function. 
// if a fuction is called, then use only println ...
// 2. to compile a rust program, call in terminal rustc *.rs
// 3. to run the programm main.rs, call ./main 
// 4. Cargo is Rust’s build system and package manager
// 5. Rustaceans use Cargo to manage their Rust projects

fn main() {
	//println!("Hello world");
	let _s = dangle();
}

fn dangle() -> String {
	let s = String::from("hello"); 
	
	// thats the return statement, without the return-word;
	s
}