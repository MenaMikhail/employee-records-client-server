# employee-records-client-server

# Employee Records Client-Server System (C)

## 📌 Overview
This project is a multithreaded client-server application written in C that manages employee records using TCP sockets. Clients can connect to the server and perform operations such as adding records, searching by name, zip code, or salary.

## 🚀 Features
- Multi-client support using pthreads
- TCP socket communication
- Add new employee records
- Search by name (case-insensitive)
- Search by zip code
- Search by salary with comparison operators (>, <, ==, >=, <=)
- Thread-safe file access using mutex

## 🛠️ Tech Stack
- C
- POSIX Threads (pthreads)
- TCP/IP Sockets
- File Handling (CSV)

## ▶️ How to Run

### 1. Clone repo
git clone https://github.com/your-username/employee-records-client-server-c.git

### 2. Build
make

### 3. Run server
./server/server 3334

### 4. Run client
./client/client 127.0.0.1 3334

## 📂 Data Format
Stored in `records.csv`:
FirstName,LastName,ZipCode,Department,Salary

## 📊 Example

Client Menu:
(1) Add new record  
(2) Search by Name  
(3) Search by Zip Code  
(4) Search by Salary  
(5) Terminate  

Example search:
Enter First Name: John  
Enter Last Name: Doe  

Output:
John,Doe,37013,IT,75000  

## 🧠 What I Learned
- Building client-server systems
- Multithreading and synchronization
- Designing communication protocols
- File-based data management
- Handling concurrent access safely

## 📌 Future Improvements
- Replace CSV with database (SQL)
- Add authentication system
- Improve error handling
- Add logging system

## 👤 Author
Mena Mikhail
