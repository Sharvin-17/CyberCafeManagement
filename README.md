# CYBER CAFÉ SEAT ALLOCATION, SESSION TRACKING & BILLING MANAGEMENT SYSTEM

> **A Beginner-Friendly C++ Object-Oriented Programming (OOP) Microproject**  
> *Designed for College Viva Voce, Practical Demonstrations, and OOP Coursework.*

---

## 1. Project Title
**Cyber Café Seat Allocation, Session Tracking & Billing Management System**

---

## 2. Project Objective
To build a simple, easy-to-understand console application in standard C++17 that automates cyber café daily operations—including customer registration, workstation assignment, usage session tracking, and automatic duration-based billing calculation using Object-Oriented Programming principles.

---

## 3. Problem Statement
Traditional cyber cafés face challenges in tracking active workstation allocations, preventing duplicate seat bookings, and manually calculating usage bills based on varying hourly computer rates. This system solves these issues through a centralized computer and session management workflow.

---

## 4. Key Features
- **Customer Registration:** Add and view customers with unique IDs, names, and contact details.
- **Pre-configured Workstations (8 Computers):**
  - `101 - 105`: **Standard PCs** (₹30.00 / hour)
  - `201 - 203`: **Gaming PCs** (₹60.00 / hour)
- **Session Allocation:** Assign an available workstation to a registered customer. Prevents duplicate active sessions for the same customer or assigning occupied PCs.
- **Automated Billing:** Automatically calculates elapsed usage time using `<ctime>` and generates the final bill ($\text{Duration in Hours} \times \text{Hourly Rate}$).
- **Active Sessions & History Log:** Real-time visibility into currently occupied seats and completed session history.
- **Robust Input Handling:** Safe line-based integer and text inputs preventing crashes on invalid user entries.

---

## 5. Classes Used

| Class | Description |
| :--- | :--- |
| `Customer` | Encapsulates customer attributes (`id`, `name`, `phone`) and display logic. |
| `Computer` | **Abstract Base Class** representing a workstation with pure virtual methods `getRate()` and `getType()`. |
| `StandardPC` | Inherits from `Computer` and overrides `getRate()` (₹30/hr) and `getType()` ("Standard PC"). |
| `GamingPC` | Inherits from `Computer` and overrides `getRate()` (₹60/hr) and `getType()` ("Gaming PC"). |
| `Session` | Encapsulates usage session details, start/end timestamps, elapsed duration, and bill computation. |
| `CyberCafe` | Central manager class using composition to manage collections of `Customer`, `Computer*`, and `Session` objects. |

---

## 6. OOP Concepts Demonstrated (Viva Guide)

1. **Encapsulation:**
   - Class member variables (e.g., `id`, `name`, `bill`, `available`) are `private` or `protected`.
   - Access and modifications are done through public member functions and getters (`getId()`, `isAvailable()`, `getRate()`).

2. **Inheritance:**
   - `StandardPC` and `GamingPC` inherit common attributes and behaviors from the base class `Computer`.

3. **Runtime Polymorphism:**
   - The base class `Computer` defines pure virtual functions:
     ```cpp
     virtual double getRate() const = 0;
     virtual string getType() const = 0;
     ```
   - When ending a session, the bill rate is retrieved polymorphically (`computer->getRate()`) without checking the concrete derived type with `if-else`.

4. **Abstraction:**
   - The abstract base class `Computer` hides specific hardware rate differences behind a simple unified interface.

5. **Function Overloading (Compile-Time Polymorphism):**
   - The `CyberCafe` class provides overloaded customer search functions:
     - `Customer* searchCustomer(int id);` (Search by ID)
     - `Customer* searchCustomer(string name);` (Search by Name)

6. **Composition:**
   - The `CyberCafe` class manages vectors of `Customer`, `Computer*`, and `Session` objects.

7. **Memory Management:**
   - The destructor `~CyberCafe()` cleans up dynamically allocated `Computer*` objects to prevent memory leaks.

---

## 7. Software Requirements
- **Language:** Standard C++ (C++17)
- **Compiler:** `g++` (Ubuntu/Linux, MinGW on Windows, or Clang on macOS)
- **Operating System:** Linux, Windows, or macOS

---

## 8. How to Compile

Run the following command in the project directory:

```bash
g++ -std=c++17 main.cpp -o cybercafe
```

---

## 9. How to Run

Execute the compiled binary:

```bash
./cybercafe
```

*(On Windows PowerShell / CMD: `cybercafe.exe`)*

---

## 10. Sample Workflow

### Main Menu
```text
========================================
       CYBER CAFE MANAGEMENT SYSTEM     
========================================

1. Add Customer
2. View Customers
3. View Computers
4. Start Session
5. End Session
6. View Active Sessions
7. View Session History
8. Exit

========================================
Enter your choice: 
```

### 1. Adding a Customer
```text
----------------------------------------
              ADD CUSTOMER              
----------------------------------------
Enter Customer ID: 101
Enter Customer Name: Rahul Sharma
Enter Phone Number: 9876543210

Customer added successfully.
```

### 2. Starting a Session
```text
----------------------------------------
             START SESSION              
----------------------------------------
Enter Customer ID: 101

Available Computers:
ID        Type            Rate       Status      
--------------------------------------------------
101       Standard PC     ₹30.00     Available   
102       Standard PC     ₹30.00     Available   
201       Gaming PC       ₹60.00     Available   
...
Enter Computer ID to assign: 201

Session started successfully.

Session ID : 1001
Customer   : Rahul Sharma
Computer   : 201
Type       : Gaming PC
Rate       : ₹60.00/hour
Start Time : 15:30:12
```

### 3. Ending a Session & Bill Receipt
```text
----------------------------------------
              END SESSION               
----------------------------------------
Enter Session ID to end: 1001

========================================
             SESSION BILL               
========================================

Session ID : 1001
Customer   : Rahul Sharma
Computer   : 201
Type       : Gaming PC

Start Time : 15:30:12
End Time   : 17:00:12

Duration   : 1.50 hours
Rate       : ₹60.00/hour

Total Bill : ₹90.00

========================================
```

---

## 11. Future Enhancements
- Member loyalty discount cards.
- Add-on snack/beverage order billing.
- GUI dashboard using Qt or WinForms.
