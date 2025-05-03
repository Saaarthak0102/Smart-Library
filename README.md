# Smart Library Management System

A comprehensive C++ application for managing library operations including book inventory, member management, and transaction tracking.

## Features

- Book management (add, search, display)
- Member registration and management
- Book issuing and returning with fine calculation
- Support for different types of library materials (books, e-books, journals)
- Transaction history tracking
- Book reservations using queue data structure
- Recent transactions tracking using stack data structure
- Reporting capabilities (overdue books, book status)
- Exception handling for robust error management
- Sorting capabilities using templated generic manager

## System Requirements

- C++11 or higher
- Standard C++ compiler (g++, clang++, or MSVC)

## Compilation Instructions

### On Linux/macOS

```bash
# Using g++
g++ -std=c++11 Smart_Library_Management_System.cpp -o SmartLibrary

# Using clang++
clang++ -std=c++11 Smart_Library_Management_System.cpp -o SmartLibrary
```

### On Windows

#### Using Command Prompt with MinGW
```
g++ -std=c++11 Smart_Library_Management_System.cpp -o SmartLibrary.exe
```

#### Using Visual Studio
1. Open Visual Studio
2. Create a new C++ project
3. Add the Smart_Library_Management_System.cpp file to your project
4. Build the solution (Ctrl+Shift+B)

#### Using Visual Studio Code
1. Install C/C++ extension
2. Configure tasks.json for building with g++ or MSVC
3. Press Ctrl+Shift+B to build

## Running the Application

### On Linux/macOS
```bash
./SmartLibrary
```

### On Windows
```
SmartLibrary.exe
```

## Using the System

Once running, the application presents a menu-driven interface:

1. **Display All Books** - Shows all books in the library with their details
2. **Display All Members** - Shows all registered members
3. **Issue Book** - Issue a book to a member (requires Member ID and Book ID)
4. **Return Book** - Process a book return (requires Member ID and Book ID)
5. **Generate Overdue Report** - Shows all overdue books
6. **Display Recent Transactions** - Shows the most recent library transactions
7. **Generate Book Status Report** - Shows the status of all books
8. **Sort Books by ID** - Sorts the book collection by their IDs
0. **Exit** - Quit the application

## Sample Data

The system comes pre-loaded with sample data:

### Books
- B001: The C++ Programming Language by Bjarne Stroustrup
- B002: Data Structures Using C++ by D.S. Malik
- B003: Design Patterns by Erich Gamma et al.
- EB001: Clean Code by Robert C. Martin (E-Book)
- J001: IEEE Software by IEEE (Journal)

### Members
- M001: John Doe (john@example.com)
- M002: Jane Smith (jane@example.com)

### Staff
- L001: Alice Brown (Head Librarian)

## Error Handling

The system uses custom exceptions to handle various error conditions:

- BookNotFoundException - When a requested book is not found
- InvalidMemberException - When an invalid member ID is used
- MaxIssueLimitException - When a member tries to issue more books than allowed

## Code Structure

The system uses several C++ features and STL containers:
- Classes for Book, Member, Transaction, Librarian
- Inheritance for specialized book types (EBook, Journal)
- Vector for storing books, transactions, and staff
- List for storing members
- Stack for tracking recent transactions
- Queue for book reservations
- Templates for generic sorting and searching

## Troubleshooting

### Compilation Issues
- Ensure you have a C++11 compatible compiler
- Check for any missing header files or syntax errors

### Runtime Issues
- Follow the menu instructions carefully
- Use the sample IDs for testing (B001, M001, etc.)
- Check error messages for guidance

## License

This software is available for educational purposes.

## Author

Smart Library Management System Team
