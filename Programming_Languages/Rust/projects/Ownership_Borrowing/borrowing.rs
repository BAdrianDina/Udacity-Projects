// Define the Book struct with lifetimes for the borrowed &str
struct Book<'a> {
    title: String,      // Owned String for the title
    author: &'a str,    // Borrowed reference to a string slice (&str) for the author
}

// Function to print details of a Book
fn print_book_details(book: &Book) {
    println!("Title: {}", book.title);
    println!("Author: {}", book.author);
}



fn main() {
   // Create a String for the title
    let book_title = String::from("The Rust Programming Language");

    // Create a string slice (&str) for the author
    let author_name = "Steve Klabnik and Carol Nichols";

    // Create an instance of Book
    let book = Book {
        title: book_title,
        author: author_name,
    };

    // Call the function to print book details
    print_book_details(&book);
}