#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include<vector>
#include <sstream>
#include<exception>

using namespace std;

void issueBook();
void returnBook();
void viewNotReturnedBooks();
void searchStudent();
void searchBook();
void studentHistory();
void bookHistory();
void addNewBook();
void addNewStudent();
string getCurrentDate();

//  Function to Get Current Date in DD-MM-YYYY Format
string getCurrentDate() {
    time_t now = time(0);
    tm *time = localtime(&now);
    char date[11];
    sprintf(date, "%02d-%02d-%04d", time->tm_mday, time->tm_mon + 1, 1900 + time->tm_year);
    return string(date);
}

class FileOpenException : public exception {
    string message;
public:
    FileOpenException(const string& fileName) {
        message = "Error: Unable to open file '" + fileName + "'";
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
};


class Book {
    public:
        string bookNum, title, author, publication;
    
        void input() {
            cin.ignore();

            cout << "Enter Book Number: ";
            getline(cin, bookNum);
    
            cout << "Enter Book Title: ";
            getline(cin, title);
    
            cout << "Enter Book Author: ";
            getline(cin, author);
    
            cout << "Enter Book Publication: ";
            getline(cin, publication);
        }
        
        void saveToFile() {
            ofstream bookFile("all_books.txt", ios::app); // Append mode
            
            if (!bookFile) {
                throw FileOpenException("all_books.txt");
            }

            bookFile << bookNum << "," << title << "," << author << "," << publication << endl;
            bookFile.close();
            cout << "Book added successfully!\n";
        }

        void searchBook() {
            cin.ignore();
            string keyword;
            cout << "Enter Book Number";  // or Title Keyword to Search: 
            getline(cin, keyword);
        
            ifstream inFile("all_books.txt");
        
            if (!inFile) {
                throw FileOpenException("all_books.txt");
            }
        
            string line;
            bool found = false;
        
            cout << "\n--- Search Results ---\n";
            cout << "BookNum | Title | Author | Publication\n";
        
            while (getline(inFile, line)) {
                stringstream ss(line);
                string bNum, bTitle, bAuthor, bPub;
        
                getline(ss, bNum, ',');
                getline(ss, bTitle, ',');
                getline(ss, bAuthor, ',');
                getline(ss, bPub, ',');
        
                if (bNum == keyword /*|| lowerTitle.find(lowerKeyword) != string::npos*/) {
                    cout << bNum << " | " << bTitle << " | " << bAuthor << " | " << bPub << endl;
                    found = true;
                }
            }
        
            inFile.close();
        
            if (!found) {
                cout << "No matching book found.\n";
            }
        }
};
    
class Student {
    public:
        string enr, name, className, email, mobile;
    
        // Function to take input from librarian
        void input() {
            cin.ignore();
            cout << "Enter Enrollment Number: ";
            getline(cin, enr);
    
            cout << "Enter Student Name: ";
            getline(cin, name);
    
            cout << "Enter Class: ";
            getline(cin, className);
    
            cout << "Enter Email: ";
            getline(cin, email);
    
            cout << "Enter Mobile Number: ";
            getline(cin, mobile);
        }
    
        // Function to save student details to file
        void saveToFile() {
            ofstream studFile("all_stud.txt", ios::app); // Append mode
            if (!studFile) {
                throw FileOpenException("all_stud.txt");
            }

            studFile << enr << "," << name << "," << className << "," << email << "," << mobile << endl;
            studFile.close();
    
            cout << "Student added successfully!\n";
        }

        void searchStudent() {
            cin.ignore();
            string searchEnr;
            cout << "Enter Student Enrollment Number to Search: ";
            getline(cin, searchEnr);
        
            ifstream inFile("all_stud.txt");
            if (!inFile) {
                throw FileOpenException("all_stud.txt");
            }
        
            string line;
            bool found = false;
        
            while (getline(inFile, line)) {
                stringstream ss(line);
                string enr, name, clas, email, mob;
        
                getline(ss, enr, ',');
                getline(ss, name, ',');
                getline(ss, clas, ',');
                getline(ss, email, ',');
                getline(ss, mob, ',');
        
                if (enr == searchEnr) {
                    cout << "\n--- Student Found ---\n";
                    cout << "Enrollment No: " << enr << endl;
                    cout << "Name         : " << name << endl;
                    cout << "Class        : " << clas << endl;
                    cout << "Email        : " << email << endl;
                    cout << "Mobile No    : " << mob << endl;
                    found = true;
                    break; // No need to check further
                }
            }
        
            inFile.close();
        
            if (!found) {
                cout << "No student found with enrollment number " << searchEnr << ".\n";
            }
        }
};
     
class IssuedBook {
    public:
        string bookNum, studEnr, issueDate, returnDate, returnStatus;
    
        void issue() {
            cin.ignore();

            cout << "Enter Book Number: ";
            getline(cin, bookNum);
        
            cout << "Enter Student Enrollment Number: ";
            getline(cin, studEnr);
        
            issueDate = getCurrentDate();
            returnDate = "-";           // Not returned yet
            returnStatus = "false";
            saveToFile();
        }

        void saveToFile(){
            ofstream issueFile("all_issued.txt", ios::app); // Append mode
            if (!issueFile) {
                throw FileOpenException("all_issued.txt");
            }
            
            issueFile << bookNum << "," << studEnr << "," << issueDate << "," 
            << returnDate << "," << returnStatus << endl;
            
            issueFile.close();
            cout << "Book issued successfully!\n";
        }
        
        void returnBook() {
            cin.ignore();
            cout << "Enter Book Number to Return: ";
            cin >> bookNum;
        
            ifstream inFile("all_issued.txt");

            if (!inFile) {
                throw FileOpenException("all_issued.txt");
            }

            vector<string> lines;
            string line;
            bool recordFound = false;
        
            while (getline(inFile, line)) {
                stringstream ss(line);
                string bNum, sEnr, issDate, retDate, retStatus;
        
                getline(ss, bNum, ',');
                getline(ss, sEnr, ',');
                getline(ss, issDate, ',');
                getline(ss, retDate, ',');
                getline(ss, retStatus, ',');
        
                if (bNum == bookNum && retStatus == "false") {
                    retDate = getCurrentDate();
                    retStatus = "true";
                    recordFound = true;
                    cout << "Book returned successfully!\n";
                }
        
                // Store (original or updated) line back into the vector
                string updatedLine = bNum + "," + sEnr + "," + issDate + "," + retDate + "," + retStatus;
                lines.push_back(updatedLine);
            }
            inFile.close();
        
            // Rewrite file using updated vector content
            ofstream outFile("all_issued.txt");
            if (!outFile) {
                throw FileOpenException("all_issued.txt");
            }


            for (const string& l : lines) {
                outFile << l << endl;
            }
            outFile.close();
        
            if (!recordFound) {
                cout << "No matching issued book found or already returned.\n";
            }
        }

        void viewNotReturned() {
            ifstream inFile("all_issued.txt");
        
            if (!inFile) {
                throw FileOpenException("all_issued.txt");
            }

            string line;
            bool anyFound = false;
        
            cout << "\n--- Books Not Returned ---\n";
            cout << "BookNum | StudEnr | IssueDate\n";
        
            while (getline(inFile, line)) {
                stringstream ss(line);
                string bNum, sEnr, issDate, retDate, retStatus;
        
                getline(ss, bNum, ',');
                getline(ss, sEnr, ',');
                getline(ss, issDate, ',');
                getline(ss, retDate, ',');
                getline(ss, retStatus, ',');
        
                if (retStatus == "false") {
                    cout << bNum << " | " << sEnr << " | " << issDate << endl;
                    anyFound = true;
                }
            }
        
            inFile.close();
        
            if (!anyFound) {
                cout << "All books have been returned.\n";
            }
        }
        
        void studentHistory() {
            cin.ignore();
            string searchEnr;
            cout << "Enter Student Enrollment Number: ";
            getline(cin, searchEnr);
        
            ifstream inFile("all_issued.txt");
        
            if (!inFile) {
                throw FileOpenException("all_issued.txt");
            }
        
            string line;
            bool found = false;
        
            cout << "\n--- Student History ---\n";
            cout << "BookNum | IssueDate | ReturnDate | Status\n";
        
            while (getline(inFile, line)) {
                stringstream ss(line);
                string bNum, sEnr, issDate, retDate, retStatus;
        
                getline(ss, bNum, ',');
                getline(ss, sEnr, ',');
                getline(ss, issDate, ',');
                getline(ss, retDate, ',');
                getline(ss, retStatus, ',');
        
                if (sEnr == searchEnr) {
                    string status = (retStatus == "true") ? "Returned" : "Not Returned";
                    cout << bNum << " | " << issDate << " | " << retDate << " | " << status << endl;
                    found = true;
                }
            }
        
            inFile.close();
        
            if (!found) {
                cout << "No records found for this student.\n";
            }
        }

        void bookHistory() {
            cin.ignore();
            string searchBookNum;
            cout << "Enter Book Number: ";
            getline(cin, searchBookNum);
        
            ifstream inFile("all_issued.txt");
        
            if (!inFile) {
                throw FileOpenException("all_issued.txt");
            }
        
            string line;
            bool found = false;
        
            cout << "\n--- Book History ---\n";
            cout << "StudEnr | IssueDate | ReturnDate | Status\n";
        
            while (getline(inFile, line)) {
                stringstream ss(line);
                string bNum, sEnr, issDate, retDate, retStatus;
        
                getline(ss, bNum, ',');
                getline(ss, sEnr, ',');
                getline(ss, issDate, ',');
                getline(ss, retDate, ',');
                getline(ss, retStatus, ',');
        
                if (bNum == searchBookNum) {
                    string status = (retStatus == "true") ? "Returned" : "Not Returned";
                    cout << sEnr << " | " << issDate << " | " << retDate << " | " << status << endl;
                    found = true;
                }
            }
        
            inFile.close();
        
            if (!found) {
                cout << "No records found for this book.\n";
            }
        }
        
    };
    

int main() {
    int choice;

    while (true) {
        cout << "\n=== Library Management System ===" << endl;
        cout << "Select Operation" << endl;
        cout << "1 - Issue Book" << endl;
        cout << "2 - Return Book" << endl;
        cout << "3 - View Not Returned Books" << endl;
        cout << "4 - Search Student" << endl;
        cout << "5 - Search Book" << endl;
        cout << "6 - Student History" << endl;
        cout << "7 - Book History" << endl;
        cout << "8 - Add New Book" << endl;
        cout << "9 - Add New Student" << endl;
        cout << "0 - Exit" << endl;
        cout << "Enter your choice: ";
        
        cin >> choice;

        switch (choice) {
            case 1: 
                issueBook();
                break;
            case 2:
                returnBook();
                break;
            case 3:
                viewNotReturnedBooks();
                break;
            case 4:
                searchStudent();
                break;
            case 5: 
                searchBook();
                break;
            case 6: 
                studentHistory(); 
                break;
            case 7: 
                bookHistory(); 
                break;
            case 8: 
                addNewBook(); 
                break;
            case 9: 
                addNewStudent(); 
                break;
            case 0: 
                cout << "Exiting system...";
                exit(0);
            
            default: 
                cout << "Invalid Option. Try again.\n"; 
                break;
        }
    }
}


void issueBook() {
    try {
        IssuedBook ib;
        ib.issue();
    } 
    catch (const FileOpenException& e) {
        cerr << e.what() << endl;
    }
}
void returnBook() {
    try {
        IssuedBook ib;
        ib.returnBook();
    }
    catch (const FileOpenException& e) {
        cerr << e.what() << endl;
    }
}
void viewNotReturnedBooks() {
    try {
        IssuedBook ib;
        ib.viewNotReturned();
    } 
    catch (const FileOpenException& e) {
        cerr << e.what() << endl;
    }
}
void searchStudent() {
    try {
        Student newStudent;
        newStudent.searchStudent();
    } 
    catch (const FileOpenException& e) {
        cerr << e.what() << endl;
    }
}
void searchBook() {
    try {
        Book newBook;
        newBook.searchBook();    
    } 
    catch (const FileOpenException& e) {
        cerr << e.what() << endl;
    }
}
void studentHistory() {
    try {
        IssuedBook ib;
        ib.studentHistory();
    } 
    catch (const FileOpenException& e) {
        cerr << e.what() << endl;
    }
}

""

void bookHistory() {
    try {
        IssuedBook ib;
        ib.bookHistory();
    } 
    catch (const FileOpenException& e) {
        cerr << e.what() << endl;
    }    
}
void addNewBook() {
    try {
        Book newBook;
        newBook.input();
        newBook.saveToFile();
    }
    catch (const FileOpenException& e) {
        cerr << e.what() << endl;
    }
}
void addNewStudent() {
    try {
        Student newStudent;
        newStudent.input();
        newStudent.saveToFile();
    } 
    catch (const FileOpenException& e) {
        cerr << e.what() << endl;
    }
}
