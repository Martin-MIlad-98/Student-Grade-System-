# Student Grade Management System

A comprehensive desktop application for managing student grades, courses, and academic records. Built with C++ and Qt framework, demonstrating advanced Object-Oriented Programming principles.

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Qt](https://img.shields.io/badge/Qt-6.x-green.svg)
![C++](https://img.shields.io/badge/C++-17-orange.svg)

## Features

### Core Functionality
- **Student Management**: Add, edit, and track student information with automatic GPA calculation
- **Course Management**: Create and manage different course types (Core, Elective, Laboratory)
- **Grade Tracking**: Record and update midterm, final, and assignment scores
- **Teacher Management**: Maintain teacher profiles and course assignments
- **Analytics Dashboard**: View statistics and grade distributions
- **Data Persistence**: Save and load data in JSON format
- **Search & Filter**: Quick search and filter capabilities

### Beautiful Qt GUI
- Modern, professional interface with custom styling
- Tabbed navigation for different modules
- Responsive tables with sorting capabilities
- Dialog-based forms for data entry
- Color-coded buttons and visual feedback
- Clean, intuitive user experience

## OOP Concepts Demonstrated

### 1. **Encapsulation**
- Private member variables with public accessors
- Controlled data access through getters/setters
- Information hiding in all classes

### 2. **Inheritance**
- Base class: `Person` (abstract)
- Derived classes: `Student`, `Teacher`
- Course hierarchy: `Course` → `CoreCourse`, `ElectiveCourse`, `LabCourse`

### 3. **Polymorphism**
- Virtual functions: `getRole()`, `getDisplayInfo()`, `getCourseType()`
- Runtime polymorphism through base class pointers
- Different behavior in derived classes

### 4. **Abstraction**
- Pure virtual functions in `Person` and `Course`
- Abstract interfaces for common operations
- Implementation details hidden from users

### 5. **Operator Overloading**
- Comparison operators for `Person` (==, !=)
- Comparison operators for `Student` (<, >)
- Natural syntax for object comparisons

### 6. **Templates**
- `DataRepository<T>` template class
- Generic collection management
- Type-safe operations

### 7. **Design Patterns**
- **Singleton Pattern**: `GradeManager` (single instance)
- **Repository Pattern**: `DataRepository<T>`
- **MVC Pattern**: Separation of models, views, and logic

### 8. **Smart Pointers**
- `std::shared_ptr<T>` for automatic memory management
- No manual `new`/`delete` operations
- Safe pointer sharing

### 9. **STL Containers**
- `QVector` for dynamic arrays
- `QMap` for key-value storage
- Qt container integration

### 10. **Const Correctness**
- Const member functions
- Const references where appropriate
- Immutable data protection

## Project Structure

```
StudentGradeSystem/
├── src/
│   ├── models/              # Data models
│   │   ├── Person.h/cpp     # Abstract base class
│   │   ├── Student.h/cpp    # Student entity
│   │   ├── Teacher.h/cpp    # Teacher entity
│   │   ├── Course.h/cpp     # Course hierarchy
│   │   └── Grade.h/cpp      # Grade records
│   │
│   ├── data/                # Data management
│   │   ├── DataRepository.h # Template repository
│   │   └── GradeManager.h/cpp # Singleton manager
│   │
│   ├── gui/                 # Qt GUI components
│   │   ├── MainWindow.h/cpp     # Main application window
│   │   ├── StudentDialog.h/cpp  # Student form
│   │   ├── CourseDialog.h/cpp   # Course form
│   │   ├── GradeDialog.h/cpp    # Grade form
│   │   └── TeacherDialog.h/cpp  # Teacher form
│   │
│   └── main.cpp             # Application entry point
│
├── StudentGradeSystem.pro   # Qt project file
├── build.bat                # Windows build script
├── build.sh                 # Unix build script
└── README.md                # This file
```

## Prerequisites

### Required
- **Qt 6.x** (or Qt 5.15+)
  - Qt Core
  - Qt Widgets
  - Qt Charts
- **C++ Compiler** with C++17 support
  - MSVC 2019+ (Windows)
  - GCC 7+ (Linux)
  - Clang 5+ (macOS)

### Installation

#### Windows
Download and install Qt from [qt.io/download](https://www.qt.io/download)
- Select Qt 6.x with MSVC compiler
- Add Qt bin directory to PATH

#### Linux (Ubuntu/Debian)
```bash
sudo apt-get update
sudo apt-get install qt6-base-dev qt6-charts-dev build-essential
```

#### Linux (Fedora)
```bash
sudo dnf install qt6-qtbase-devel qt6-qtcharts-devel gcc-c++
```

#### macOS
```bash
brew install qt@6
```

## Building the Project

### Windows

1. Open Command Prompt or PowerShell
2. Navigate to project directory:
   ```cmd
   cd c:\Users\monge\Desktop\oop\StudentGradeSystem
   ```
3. Run build script:
   ```cmd
   build.bat
   ```
4. Run the application:
   ```cmd
   release\StudentGradeSystem.exe
   ```

### Linux / macOS

1. Open Terminal
2. Navigate to project directory:
   ```bash
   cd ~/Desktop/oop/StudentGradeSystem
   ```
3. Make build script executable:
   ```bash
   chmod +x build.sh
   ```
4. Run build script:
   ```bash
   ./build.sh
   ```
5. Run the application:
   ```bash
   ./StudentGradeSystem
   ```

### Manual Build

If you prefer to build manually:

```bash
qmake StudentGradeSystem.pro
make        # or nmake on Windows with MSVC
            # or mingw32-make on Windows with MinGW
```

## Usage Guide

### Getting Started

1. **Launch the application**
2. **Create sample data**: Go to `Data` → `Create Sample Data`
3. **Explore the tabs**:
   - **Students**: View and manage student records
   - **Courses**: Add and edit courses
   - **Grades**: Track student performance
   - **Teachers**: Manage teaching staff
   - **Analytics**: View system statistics

### Managing Students

1. Click **Students** tab
2. Click **Add Student** button
3. Fill in the form:
   - Personal information
   - Student number
   - Major and enrollment year
4. Click **Add** to save

### Creating Courses

1. Navigate to **Courses** tab
2. Click **Add Course**
3. Select course type:
   - **Core**: Required courses (30% mid, 50% final, 20% assignment)
   - **Elective**: Optional courses (25% mid, 40% final, 35% assignment)
   - **Laboratory**: Hands-on courses (20% mid, 30% final, 50% assignment)
4. Enter course details and save

### Recording Grades

1. Go to **Grades** tab
2. Click **Enroll Student** to register a student in a course
3. Click **Update Grade** to enter scores
4. Grades are automatically calculated based on course type

### Filtering and Searching

- **Search students**: Type in the search box
- **Filter by major**: Use the dropdown menu
- **Sort tables**: Click column headers

### Data Management

- **Save**: `File` → `Save Data` (Ctrl+S)
- **Load**: `File` → `Load Data` (Ctrl+O)
- **Export**: `File` → `Export Report`

## Key Features

### GPA Calculation
The system automatically calculates GPA on a 4.0 scale:
- A (90-100): 4.0
- A- (85-89): 3.7
- B+ (80-84): 3.3
- B (75-79): 3.0
- And so on...

### Academic Standing
Students are automatically classified:
- **Dean's List**: GPA ≥ 3.5
- **Good Standing**: GPA ≥ 3.0
- **Satisfactory**: GPA ≥ 2.0
- **Academic Warning**: GPA ≥ 1.0
- **Academic Probation**: GPA < 1.0

### Weighted Grading
Different course types use different grade weights:
- **Core**: 30% Midterm + 50% Final + 20% Assignments
- **Elective**: 25% Midterm + 40% Final + 35% Assignments
- **Laboratory**: 20% Midterm + 30% Final + 50% Assignments

## Code Quality

- **Clean architecture** with clear separation of concerns
- **Consistent naming**: camelCase for variables, PascalCase for classes
- **Documentation**: Comprehensive comments explaining logic
- **Error handling**: Validation and user-friendly error messages
- **Memory safety**: Smart pointers throughout
- **Qt best practices**: Proper signal/slot connections
- **Professional UI**: Custom styling and responsive design

## Technologies Used

- **Language**: C++17
- **Framework**: Qt 6.x
- **GUI**: Qt Widgets
- **Charts**: Qt Charts
- **Build System**: qmake
- **Data Format**: JSON
- **Design**: Model-View-Controller pattern

## Learning Outcomes

This project demonstrates:
- Professional Qt application development
- Advanced OOP design and implementation
- Modern C++ best practices
- GUI programming with Qt Widgets
- Data persistence with JSON
- Design pattern implementation
- Template programming
- Smart pointer usage
- STL and Qt container usage

## Future Enhancements

Potential improvements:
- [ ] Database integration (SQLite/PostgreSQL)
- [ ] PDF report generation
- [ ] Email notifications
- [ ] Attendance tracking
- [ ] Schedule management
- [ ] Multi-user authentication
- [ ] Cloud synchronization
- [ ] Mobile companion app
- [ ] Advanced analytics with charts
- [ ] Export to Excel

## Troubleshooting

### Qt not found
- Ensure Qt is installed and added to PATH
- Verify qmake is accessible: `qmake --version`

### Build errors
- Check C++17 compiler support
- Verify all Qt modules are installed (Core, Widgets, Charts)
- Clean build: `make clean` then rebuild

### Runtime errors
- Ensure Qt runtime DLLs are in PATH or same directory as executable
- Check data file permissions

## Contributing

This is an educational project demonstrating OOP concepts. Feel free to:
- Study the code
- Suggest improvements
- Report issues
- Use as reference for learning

## License

This project is free to use for educational purposes.

## Author

Created as a comprehensive demonstration of Object-Oriented Programming principles using C++ and Qt framework.

---

**Built with ❤️ using Qt and C++**
