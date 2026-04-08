# 🎓 Student Grade Management System (C++ / Qt)

## 📌 Project Overview  
Welcome to the **Student Grade Management System** — a desktop application developed in **C++ using the Qt Framework**, designed to manage students, professors, courses, and academic grades through an interactive graphical user interface (GUI).

The system simulates real-world academic operations while demonstrating core **Object-Oriented Programming (OOP)** principles. It provides a clean, modular, and scalable architecture with clear separation between user interface and system logic.

---

## 🎯 Features  
- ✅ Manage **Students, Professors, and Courses**
- ✅ Assign and track **grades**
- ✅ Interactive **GUI using Qt (dialogs & widgets)**
- ✅ Layered architecture (UI → Control → Core Logic)
- ✅ Clean implementation of **OOP concepts**
- ✅ Modular and scalable system design
- ✅ Input validation and safe data handling

---

## 📂 File Structure  

| Path | Description |
|---|---|
| **main.cpp** | Application entry point |
| **MainWindow.cpp / .h** | Main GUI controller |
| **Student / Professor / Course / Grade** | Core system classes |
| **GradeManager** | System control & logic manager |
| **Dialogs (StudentDialog, CourseDialog, etc.)** | GUI interaction forms |
| **DataRepository** | Data storage & handling |
| **CMakeLists.txt / .pro** | Build configuration |

---

## 🛠️ Implementation Details  

### 🖥️ Presentation Layer (GUI - Qt)  
- Built using Qt Widgets (QMainWindow, QDialog, QTableWidget)  
- Handles user input and data visualization  
- No direct business logic  

### ⚙️ Control Layer  
- **GradeManager** acts as the central system controller  
- Manages workflows like enrollment, grading, and data handling  
- Coordinates between UI and core logic  

### 🧠 Core Logic Layer  
- Includes classes: **Student, Professor, Course, Grade**  
- Implements all academic rules and data structures  
- Ensures modular and reusable design  

---

## 🧩 OOP Concepts Used  

- 🔒 **Encapsulation** → Private data with controlled access (getters/setters)  
- 🧱 **Abstraction** → Simplified interfaces hiding implementation details  
- 🧬 **Inheritance** → Shared behavior via base classes (e.g., Person)  
- 🔁 **Polymorphism** → Dynamic behavior using overridden functions  

---

## 🔍 System Functionalities  

### 👤 User Capabilities  
- Add and manage students  
- Add and manage professors  
- Assign courses  
- Store and manage grades  
- Display academic data  

---

## 🧪 Testing & Validation  
- Input validation using Qt widgets  
- Safe object initialization  
- Controlled data access  
- Stable GUI interaction  

---

## 📈 Future Enhancements  
- 📊 GPA calculation system  
- 🗄️ Database integration (SQLite)  
- 🔐 User authentication system  
- 📄 Report generation (PDF)  
- 📚 Subject management module  

---

## 🏁 Conclusion  
This project demonstrates a complete implementation of an **OOP-based academic management system** using **C++ and Qt**. It highlights strong software design principles, modular architecture, and scalability, making it a solid foundation for more advanced systems.

---

## 🧑‍💻 Team Members  
- Mohamed Monged  
- Martin Milad  
- Nicole Aziz  
- Mina Ehab  
- Seif Eldeen Waleed  

---

## ⭐ Final Note  
If you found this project useful, please ⭐ star the repository and share it!  
