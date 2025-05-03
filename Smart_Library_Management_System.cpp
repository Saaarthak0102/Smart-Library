#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <algorithm>
#include <stdexcept>
#include <ctime>

using namespace std;

// Forward declarations
class Book;
class Member;
class Transaction;

// Custom exceptions
class LibraryException : public exception {
protected:
    string message;
public:
    LibraryException(const string& msg) : message(msg) {}
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};

class BookNotFoundException : public LibraryException {
public:
    BookNotFoundException(const string& bookId) 
        : LibraryException("Book with ID " + bookId + " not found in the library.") {}
};

class InvalidMemberException : public LibraryException {
public:
    InvalidMemberException(const string& memberId) 
        : LibraryException("Member with ID " + memberId + " is not registered.") {}
};

class MaxIssueLimitException : public LibraryException {
public:
    MaxIssueLimitException(const string& memberId) 
        : LibraryException("Member with ID " + memberId + " has reached maximum book issue limit.") {}
};

class Book {
    private:
        string bookId;
        string title;
        string author;
        bool isAvailable;
        string category;
    
    public:
        Book(const string& id, const string& t, const string& a, const string& cat)
            : bookId(id), title(t), author(a), isAvailable(true), category(cat) {}
    
        // Getters
        string getBookId() const { return bookId; }
        string getTitle() const { return title; }
        string getAuthor() const { return author; }
        bool getAvailability() const { return isAvailable; }
        string getCategory() const { return category; }
    
        // Setters
        void setAvailability(bool status) { isAvailable = status; }
    
        // Display book details in tabular format
        void displayDetails() const {
            cout << "| " << bookId << "\t| " << title << "\t| " << author << "\t| " 
                 << category << "\t| " << (isAvailable ? "Available" : "Not Available") << "\t|\n";
        }
    };

class EBook : public Book {
    private:
        string format;
        int fileSizeMB;
    
    public:
        EBook(const string& id, const string& t, const string& a, 
              const string& cat, const string& fmt, int size)
            : Book(id, t, a, cat), format(fmt), fileSizeMB(size) {}
    
        string getFormat() const { return format; }
        int getFileSize() const { return fileSizeMB; }
    
        // Display eBook details in tabular format
        void displayDetails() const {
            cout << "| " << getBookId() << "\t| " << getTitle() << "\t| " << getAuthor() << "\t| "
                 << getCategory() << "\t| Format: " << format << ", File Size: " << fileSizeMB << " MB |\n";
        }
    };

class Journal : public Book {
    private:
        int volume;
        int issue;
        string publishDate;
    
    public:
        Journal(const string& id, const string& t, const string& a, 
               const string& cat, int vol, int iss, const string& date)
            : Book(id, t, a, cat), volume(vol), issue(iss), publishDate(date) {}
    
        int getVolume() const { return volume; }
        int getIssue() const { return issue; }
        string getPublishDate() const { return publishDate; }
    
        // Display journal details in tabular format
        void displayDetails() const {
            cout << "| " << getBookId() << "\t| " << getTitle() << "\t| " << getAuthor() << "\t| "
                 << getCategory() << "\t| Volume: " << volume << ", Issue: " << issue 
                 << ", Publish Date: " << publishDate << " |\n";
        }
    };

class Member {
    private:
        string memberId;
        string name;
        string contactInfo;
        vector<string> issuedBooks;
        int maxBooksAllowed;
    
    public:
        Member(const string& id, const string& n, const string& contact, int maxBooks = 3)
            : memberId(id), name(n), contactInfo(contact), maxBooksAllowed(maxBooks) {}
    
        // Getters
        string getMemberId() const { return memberId; }
        string getName() const { return name; }
        string getContactInfo() const { return contactInfo; }
        int getIssuedBooksCount() const { return issuedBooks.size(); }
        const vector<string>& getIssuedBooks() const { return issuedBooks; }
        int getMaxBooksAllowed() const { return maxBooksAllowed; }
    
        // Issue and return books
        void issueBook(const string& bookId) {
            if (issuedBooks.size() >= maxBooksAllowed) {
                throw MaxIssueLimitException(memberId);
            }
            issuedBooks.push_back(bookId);
        }
    
        void returnBook(const string& bookId) {
            auto it = find(issuedBooks.begin(), issuedBooks.end(), bookId);
            if (it != issuedBooks.end()) {
                issuedBooks.erase(it);
            }
        }
    
        // Display member details in tabular format
        void displayDetails() const {
            cout << "| " << memberId << "\t| " << name << "\t\t| " << contactInfo << "\t| "
                 << issuedBooks.size() << "/" << maxBooksAllowed << "\t|\n";
        }
    };

class Transaction {
    private:
        string transactionId;
        string memberId;
        string bookId;
        time_t issueDate;
        time_t returnDate;
        double fine;
        bool isReturned;
    
    public:
        Transaction(const string& tId, const string& mId, const string& bId)
            : transactionId(tId), memberId(mId), bookId(bId), issueDate(time(nullptr)), 
              returnDate(0), fine(0.0), isReturned(false) {}
    
        // Getters
        string getTransactionId() const { return transactionId; }
        string getMemberId() const { return memberId; }
        string getBookId() const { return bookId; }
        time_t getIssueDate() const { return issueDate; }
        time_t getReturnDate() const { return returnDate; }
        double getFine() const { return fine; }
        bool getReturnStatus() const { return isReturned; }
    
        // Return book and calculate fine
        void returnBook() {
            if (!isReturned) {
                returnDate = time(nullptr);
                isReturned = true;
                calculateFine();
            }
        }
    
        // Calculate fine (Rs. 2 per day after 14 days)
        void calculateFine() {
            const int MAX_DAYS_WITHOUT_FINE = 14;
            const double FINE_PER_DAY = 2.0;
    
            // Calculate days between issue and return
            double diffSeconds = difftime(returnDate, issueDate);
            int diffDays = static_cast<int>(diffSeconds / (60 * 60 * 24));
    
            if (diffDays > MAX_DAYS_WITHOUT_FINE) {
                fine = (diffDays - MAX_DAYS_WITHOUT_FINE) * FINE_PER_DAY;
            }
        }
    
        // Display transaction details in tabular format
        void displayDetails() const {
            cout << "| " << transactionId << "\t| " << memberId << "\t| " << bookId << "\t| ";
    
            // Format and display issue date
            const char* issueDateStr = ctime(&issueDate);
            cout << string(issueDateStr).substr(0, 24) << "\t| ";
    
            if (isReturned) {
                // Format and display return date
                const char* returnDateStr = ctime(&returnDate);
                cout << string(returnDateStr).substr(0, 24) << "\t| Rs. " << fine << "\t|\n";
            } else {
                cout << "Not returned yet\t| N/A\t|\n";
            }
        }
    };

class Librarian {
    private:
        string staffId;
        string name;
        string position;
    
    public:
        Librarian(const string& id, const string& n, const string& pos)
            : staffId(id), name(n), position(pos) {}
    
        // Getters
        string getStaffId() const { return staffId; }
        string getName() const { return name; }
        string getPosition() const { return position; }
    
        // Display librarian details in tabular format
        void displayDetails() const {
            cout << "| " << staffId << "\t| " << name << "\t\t| " << position << "\t|\n";
        }
    };

// Template class for sorting and searching
template<typename T>
class GenericManager {
public:
    // Generic search function
    static int search(const std::vector<T*>& items, const std::string& id, std::string (T::*getIdFunc)() const) {
        for (size_t i = 0; i < items.size(); ++i) {
            if ((items[i]->*getIdFunc)() == id) {
                return static_cast<int>(i);
            }
        }
        return -1; // Not found
    }
    
    // Generic sort function (sorts by ID)
    static void sort(std::vector<T*>& items, std::string (T::*getIdFunc)() const) {
        std::sort(items.begin(), items.end(), [getIdFunc](T* a, T* b) {
            return (a->*getIdFunc)() < (b->*getIdFunc)();
        });
    }
};

class Library {
    private:
        vector<Book*> books;
        list<Member*> members; // Using linked list as required
        vector<Librarian*> staff;
        vector<Transaction*> transactions;
    
        // STL stack for recent transactions
        stack<Transaction*> recentTransactions;
    
        // STL queue for book reservations
        queue<pair<string, string>> bookReservations; // <memberId, bookId>
    
        // Generate unique transaction ID
        string generateTransactionId() {
            static int nextId = 1000;
            return "T" + to_string(++nextId);
        }
    
    public:
        // Destructor to clean up memory
        ~Library() {
            for (auto book : books) delete book;
            for (auto member : members) delete member;
            for (auto staff : staff) delete staff;
            for (auto transaction : transactions) delete transaction;
    
            // Clear stack and queue
            while (!recentTransactions.empty()) {
                recentTransactions.pop();
            }
    
            while (!bookReservations.empty()) {
                bookReservations.pop();
            }
        }
    
        // Book management
        void addBook(Book* book) {
            books.push_back(book);
        }
    
        Book* findBook(const std::string& bookId) {
            int index = GenericManager<Book>::search(books, bookId, &Book::getBookId);
            if (index != -1) {
                return books[index];
            }
            return nullptr;
        }
    
        void displayAllBooks() const {
            cout << "\n=========================================================================================================\n";
            cout << "|\t\t\t\t\tLIBRARY BOOKS (" << books.size() << ")\t\t\t\t\t|\n";
            cout << "=========================================================================================================\n";
            cout << "| Book ID\t| Title\t\t\t\t\t| Author\t\t\t| Status\t|\n";
            cout << "---------------------------------------------------------------------------------------------------------\n";
            for (const auto& book : books) {
                cout << "| " << book->getBookId() << "\t| " << book->getTitle() << "\t| " 
                     << book->getAuthor() << "\t| " 
                     << (book->getAvailability() ? "Available" : "Issued") << "\t|\n";
            }
            cout << "=========================================================================================================\n";
        }
    
        // Member management
        void addMember(Member* member) {
            members.push_back(member);
        }
    
        Member* findMember(const std::string& memberId) {
            for (auto member : members) {
                if (member->getMemberId() == memberId) {
                    return member;
                }
            }
            return nullptr;
        }
    
        void displayAllMembers() const {
            cout << "\n=========================================================================================================\n";
            cout << "|\t\t\t\t\tLIBRARY MEMBERS (" << members.size() << ")\t\t\t\t\t|\n";
            cout << "=========================================================================================================\n";
            cout << "| Member ID\t| Name\t\t\t\t| Contact Info\t\t\t| Books Issued\t|\n";
            cout << "---------------------------------------------------------------------------------------------------------\n";
            for (const auto& member : members) {
                cout << "| " << member->getMemberId() << "\t| " << member->getName() << "\t| " 
                     << member->getContactInfo() << "\t| " 
                     << member->getIssuedBooksCount() << "/" << member->getMaxBooksAllowed() << "\t|\n";
            }
            cout << "=========================================================================================================\n";
        }
    
        // Staff management
        void addStaff(Librarian* librarian) {
            staff.push_back(librarian);
        }
    
        // Transaction operations
        void issueBook(const std::string& memberId, const std::string& bookId) {
            try {
                // Find member
                Member* member = findMember(memberId);
                if (!member) {
                    throw InvalidMemberException(memberId);
                }
    
                // Find book
                Book* book = findBook(bookId);
                if (!book) {
                    throw BookNotFoundException(bookId);
                }
    
                // Check if book is available
                if (!book->getAvailability()) {
                    cout << "Book is not available. Adding to reservation queue.\n";
                    bookReservations.push(make_pair(memberId, bookId));
                    return;
                }
    
                // Issue book
                member->issueBook(bookId);
                book->setAvailability(false);
    
                // Create transaction
                Transaction* transaction = new Transaction(generateTransactionId(), memberId, bookId);
                transactions.push_back(transaction);
    
                // Add to recent transactions stack
                recentTransactions.push(transaction);
    
                cout << "Book issued successfully!\n";
                transaction->displayDetails();
    
            } catch (const LibraryException& e) {
                cerr << "Error: " << e.what() << endl;
                // Rethrowing to demonstrate exception handling
                throw;
            }
        }
    
        void returnBook(const std::string& memberId, const std::string& bookId) {
            try {
                // Find member
                Member* member = findMember(memberId);
                if (!member) {
                    throw InvalidMemberException(memberId);
                }
    
                // Find book
                Book* book = findBook(bookId);
                if (!book) {
                    throw BookNotFoundException(bookId);
                }
    
                // Find transaction
                Transaction* transaction = nullptr;
                for (auto t : transactions) {
                    if (t->getMemberId() == memberId && t->getBookId() == bookId && !t->getReturnStatus()) {
                        transaction = t;
                        break;
                    }
                }
    
                if (!transaction) {
                    throw LibraryException("No active transaction found for this book and member.");
                }
    
                // Process return
                member->returnBook(bookId);
                book->setAvailability(true);
                transaction->returnBook();
    
                // Add to recent transactions stack
                recentTransactions.push(transaction);
    
                cout << "Book returned successfully!\n";
                transaction->displayDetails();
    
                // Check for reservations
                if (!bookReservations.empty()) {
                    auto reservation = bookReservations.front();
                    if (reservation.second == bookId) {
                        cout << "This book has a reservation. Processing...\n";
                        bookReservations.pop();
                        try {
                            issueBook(reservation.first, reservation.second);
                        } catch (const LibraryException& e) {
                            cerr << "Could not process reservation: " << e.what() << endl;
                        }
                    }
                }
    
            } catch (const LibraryException& e) {
                cerr << "Error: " << e.what() << endl;
                throw;
            }
        }
    
        // Generate reports
        void generateOverdueReport() const {
            cout << "\n===== OVERDUE BOOKS REPORT =====\n";
            time_t now = time(nullptr);
        }
    
        void generateBookStatusReport() const {
            std::cout << "\n===== BOOK STATUS REPORT =====\n";
            int available = 0, issued = 0;
    
            std::cout << "Book ID\tTitle\tStatus\n";
            std::cout << "--------------------------\n";
    
            for (const auto& book : books) {
                std::cout << book->getBookId() << "\t" << book->getTitle() << "\t" 
                          << (book->getAvailability() ? "Available" : "Issued") << "\n";
    
                if (book->getAvailability()) {
                    available++;
                } else {
                    issued++;
                }
            }
    
            std::cout << "--------------------------\n";
            std::cout << "Total Books: " << books.size() << "\n";
            std::cout << "Available: " << available << "\n";
            std::cout << "Issued: " << issued << "\n";
        }
    
        void displayRecentTransactions(int count = 5) {
            std::cout << "\n===== RECENT TRANSACTIONS =====\n";
    
            if (recentTransactions.empty()) {
                std::cout << "No recent transactions.\n";
                return;
            }
    
            // Create a copy of the stack to preserve the original
            std::stack<Transaction*> tempStack = recentTransactions;
            std::vector<Transaction*> recentOnes;
    
            // Get the most recent transactions
            int i = 0;
            while (!tempStack.empty() && i < count) {
                recentOnes.push_back(tempStack.top());
                tempStack.pop();
                i++;
            }
    
            // Display in reverse order (most recent first)
            for (const auto& transaction : recentOnes) {
                transaction->displayDetails();
                std::cout << "------------------------\n";
            }
        }
    
        // Sort books by ID
        void sortBooksByID() {
            GenericManager<Book>::sort(books, &Book::getBookId);
            std::cout << "Books sorted by ID.\n";
        }
    };

int main() {
    Library library;

    // Add sample books
    library.addBook(new Book("B001", "The C++ Programming Language", "Bjarne Stroustrup", "Programming"));
    library.addBook(new Book("B002", "Data Structures Using C++", "D.S. Malik", "Programming"));
    library.addBook(new Book("B003", "Design Patterns", "Erich Gamma et al.", "Software Engineering"));
    library.addBook(new EBook("EB001", "Clean Code", "Robert C. Martin", "Programming", "PDF", 15));
    library.addBook(new Journal("J001", "IEEE Software", "IEEE", "Software Engineering", 38, 2, "March 2023"));

    // Add sample members
    library.addMember(new Member("M001", "John Doe", "john@example.com"));
    library.addMember(new Member("M002", "Jane Smith", "jane@example.com"));

    // Add librarian
    library.addStaff(new Librarian("L001", "Alice Brown", "Head Librarian"));

    int choice;
    std::string memberId, bookId;

    do {
        cout << "\n=========================================================================================================\n";
        cout << "|\t\t\t\t\tSMART LIBRARY MANAGEMENT SYSTEM\t\t\t\t\t|\n";
        cout << "=========================================================================================================\n";
        cout << "| Option\t| Action                                                                               |\n";
        cout << "---------------------------------------------------------------------------------------------------------\n";
        cout << "| 1\t\t| Display All Books                                                                   |\n";
        cout << "| 2\t\t| Display All Members                                                                 |\n";
        cout << "| 3\t\t| Issue Book                                                                          |\n";
        cout << "| 4\t\t| Return Book                                                                         |\n";
        cout << "| 5\t\t| Generate Overdue Report                                                             |\n";
        cout << "| 6\t\t| Display Recent Transactions                                                         |\n";
        cout << "| 7\t\t| Generate Book Status Report                                                         |\n";
        cout << "| 8\t\t| Sort Books by ID                                                                    |\n";
        cout << "| 0\t\t| Exit                                                                                |\n";
        cout << "=========================================================================================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        try {
            switch (choice) {
                case 1:
                    library.displayAllBooks();
                    break;

                case 2:
                    library.displayAllMembers();
                    break;

                case 3:
                    cout << "Enter Member ID: ";
                    cin >> memberId;
                    cout << "Enter Book ID: ";
                    cin >> bookId;
                    try {
                        library.issueBook(memberId, bookId);
                    } catch (const LibraryException&) {
                        // Exception is already printed in the issueBook method
                    }
                    break;

                case 4:
                    cout << "Enter Member ID: ";
                    cin >> memberId;
                    cout << "Enter Book ID: ";
                    cin >> bookId;

                    try {
                        library.returnBook(memberId, bookId);
                    } catch (const LibraryException&) {
                        // Exception is already printed in the returnBook method
                    }
                    break;

                case 5:
                    library.generateOverdueReport();
                    break;

                case 6:
                    library.displayRecentTransactions();
                    break;

                case 7:
                    library.generateBookStatusReport();
                    break;

                case 8:
                    library.sortBooksByID();
                    break;

                case 0:
                    cout << "Thank you for using the Smart Library Management System!\n";
                    break;

                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } catch (const std::exception& e) {
            cerr << "An error occurred: " << e.what() << endl;
        }

    } while (choice != 0);

    return 0;
}