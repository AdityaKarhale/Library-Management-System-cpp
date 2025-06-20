# 📚 Library Management System (C++)

This is a simple **console-based Library Management System** developed in C++ using **file handling** and **object-oriented programming (OOP)** concepts. It is designed to be used by a librarian for maintaining records of books, students, and issued books.

---

## 🛠 Features

- Add new books and students
- Issue and return books
- View all books that are not yet returned
- Search for books by number or title
- Search for students by enrollment number
- View history of books issued by a student
- View history of all students who issued a book
- User-defined exception handling for file errors
- Data is stored in plain `.txt` files

---

## 📁 File Structure

- `all_books.txt` — stores book details  
  Format: `bookNum,title,author,publication`
- `all_stud.txt` — stores student details  
  Format: `studEnr,name,class,email,mobile`
- `all_issued.txt` — stores issued book records  
  Format: `bookNum,studEnr,issueDate,returnDate,returnStatus`

---

## 🧱 Technologies Used

- **Language**: C++
- **Concepts**: File Handling, Classes, Vectors, Exception Handling
- **Data Storage**: Plain text files (`.txt`)
- **IDE**:  VS Code / Dev C++ (any C++ IDE)

---

## 🚀 How to Run

1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/library-management-system.git
   cd library-management-system

2. Compile the program
3. Run the executables