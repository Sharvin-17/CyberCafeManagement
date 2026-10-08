#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>
#include <sstream>

using namespace std;

/**
 * ============================================================================
 * OOP Concept 1: Encapsulation & Classes/Objects
 * Class: Customer
 * Description: Keeps customer details private and provides public accessors.
 * ============================================================================
 */
class Customer {
private:
    int id;
    string name;
    string phone;

public:
    // Constructor
    Customer(int id, string name, string phone) {
        this->id = id;
        this->name = name;
        this->phone = phone;
    }

    // Getters (Encapsulation)
    int getId() const { return id; }
    string getName() const { return name; }
    string getPhone() const { return phone; }

    // Display customer details
    void display() const {
        cout << left << setw(10) << id
             << setw(25) << name
             << setw(15) << phone << "\n";
    }
};

/**
 * ============================================================================
 * OOP Concept 2: Abstraction & Runtime Polymorphism (Abstract Base Class)
 * Class: Computer
 * Description: Base class representing a seat/computer in the cyber cafe.
 *              Contains pure virtual functions getRate() and getType().
 * ============================================================================
 */
class Computer {
protected:
    int id;
    bool available;

public:
    // Constructor
    Computer(int id) {
        this->id = id;
        this->available = true;
    }

    // Virtual Destructor
    virtual ~Computer() {}

    // Getters and Setters
    int getId() const { return id; }
    bool isAvailable() const { return available; }
    void setAvailability(bool status) { available = status; }

    // Pure Virtual Functions (Abstraction & Polymorphism)
    virtual double getRate() const = 0;
    virtual string getType() const = 0;

    // Display computer information
    virtual void display() const {
        cout << left << setw(10) << id
             << setw(16) << getType()
             << "₹" << setw(10) << fixed << setprecision(2) << getRate()
             << setw(12) << (available ? "Available" : "Occupied") << "\n";
    }
};

/**
 * ============================================================================
 * OOP Concept 3: Inheritance & Polymorphism
 * Class: StandardPC (Derived from Computer)
 * Description: Standard PC with hourly rate of ₹30.00/hour.
 * ============================================================================
 */
class StandardPC : public Computer {
public:
    StandardPC(int id) : Computer(id) {}

    double getRate() const override {
        return 30.0;
    }

    string getType() const override {
        return "Standard PC";
    }
};

/**
 * ============================================================================
 * OOP Concept 3: Inheritance & Polymorphism
 * Class: GamingPC (Derived from Computer)
 * Description: High-performance Gaming PC with hourly rate of ₹60.00/hour.
 * ============================================================================
 */
class GamingPC : public Computer {
public:
    GamingPC(int id) : Computer(id) {}

    double getRate() const override {
        return 60.0;
    }

    string getType() const override {
        return "Gaming PC";
    }
};

/**
 * ============================================================================
 * OOP Concept 4: Encapsulation & Classes/Objects
 * Class: Session
 * Description: Tracks a customer's computer usage session and calculates bill.
 * ============================================================================
 */
class Session {
private:
    int sessionId;
    int customerId;
    int computerId;
    string startTime;
    string endTime;
    double durationHours;
    double bill;
    bool active;
    time_t startTimestamp;
    time_t endTimestamp;

    // Helper to format timestamp to string (HH:MM:SS)
    static string formatTime(time_t t) {
        tm* ltm = localtime(&t);
        if (!ltm) return "N/A";
        char buf[32];
        strftime(buf, sizeof(buf), "%H:%M:%S", ltm);
        return string(buf);
    }

public:
    // Constructor to start a new active session
    Session(int sessId, int custId, int compId) {
        sessionId = sessId;
        customerId = custId;
        computerId = compId;
        startTimestamp = time(nullptr);
        startTime = formatTime(startTimestamp);
        endTime = "N/A";
        durationHours = 0.0;
        bill = 0.0;
        active = true;
        endTimestamp = 0;
    }

    // Getters
    int getSessionId() const { return sessionId; }
    int getCustomerId() const { return customerId; }
    int getComputerId() const { return computerId; }
    string getStartTime() const { return startTime; }
    string getEndTime() const { return endTime; }
    double getDurationHours() const { return durationHours; }
    double getBill() const { return bill; }
    bool isActive() const { return active; }

    // End session and calculate bill using the computer's hourly rate
    void end(double rate) {
        endTimestamp = time(nullptr);
        endTime = formatTime(endTimestamp);
        active = false;

        double elapsedSeconds = difftime(endTimestamp, startTimestamp);
        if (elapsedSeconds < 0) elapsedSeconds = 0;

        // Convert seconds to hours
        durationHours = elapsedSeconds / 3600.0;

        // Minimum duration unit of 0.01 hours (~36 seconds) for quick demonstration
        if (durationHours < 0.01) {
            durationHours = 0.01;
        }

        // Bill formula: duration in hours * hourly rate
        bill = durationHours * rate;
    }
};

/**
 * ============================================================================
 * OOP Concept 5: Composition & Function Overloading
 * Class: CyberCafe
 * Description: Central class managing collections of customers, computers,
 *              and active/completed sessions.
 * ============================================================================
 */
class CyberCafe {
private:
    vector<Customer> customers;
    vector<Computer*> computers; // Polymorphic collection of Computer pointers
    vector<Session> sessions;
    int nextSessionId;

    // Helper: Find computer by ID
    Computer* findComputer(int compId) {
        for (auto comp : computers) {
            if (comp->getId() == compId) return comp;
        }
        return nullptr;
    }

    // Helper: Find active session of a specific customer
    Session* findActiveSessionByCustomer(int custId) {
        for (auto& s : sessions) {
            if (s.getCustomerId() == custId && s.isActive()) return &s;
        }
        return nullptr;
    }

    // Helper: Find session by session ID
    Session* findSession(int sessId) {
        for (auto& s : sessions) {
            if (s.getSessionId() == sessId) return &s;
        }
        return nullptr;
    }

public:
    // Constructor: Automatically initializes the 8 computers
    CyberCafe() {
        nextSessionId = 1001;

        // 5 Standard PCs (IDs: 101 to 105)
        for (int i = 101; i <= 105; i++) {
            computers.push_back(new StandardPC(i));
        }

        // 3 Gaming PCs (IDs: 201 to 203)
        for (int i = 201; i <= 203; i++) {
            computers.push_back(new GamingPC(i));
        }
    }

    // Destructor: Clean up dynamically allocated memory
    ~CyberCafe() {
        for (auto comp : computers) {
            delete comp;
        }
        computers.clear();
    }

    /**
     * ========================================================================
     * OOP Concept 6: Function Overloading (Compile-Time Polymorphism)
     * ========================================================================
     */
    // Overload 1: Search customer by integer ID
    Customer* searchCustomer(int id) {
        for (auto& c : customers) {
            if (c.getId() == id) return &c;
        }
        return nullptr;
    }

    // Overload 2: Search customer by string Name
    Customer* searchCustomer(string name) {
        for (auto& c : customers) {
            if (c.getName() == name) return &c;
        }
        return nullptr;
    }

    // Static Utility: Safe integer input reading
    static int getIntInput(const string& prompt) {
        int val;
        while (true) {
            cout << prompt;
            string line;
            if (!getline(cin, line)) return -1;
            stringstream ss(line);
            if (ss >> val) {
                string extra;
                if (!(ss >> extra)) return val;
            }
            cout << "Invalid input! Please enter a valid number.\n";
        }
    }

    // Static Utility: Safe non-empty string input reading
    static string getStringInput(const string& prompt) {
        string val;
        while (true) {
            cout << prompt;
            if (!getline(cin, val)) return "";
            size_t start = val.find_first_not_of(" \t\r\n");
            if (start == string::npos) {
                cout << "Input cannot be empty. Please enter valid text.\n";
                continue;
            }
            size_t end = val.find_last_not_of(" \t\r\n");
            return val.substr(start, end - start + 1);
        }
    }

    // 1. Add Customer
    void addCustomer() {
        cout << "\n----------------------------------------\n";
        cout << "              ADD CUSTOMER              \n";
        cout << "----------------------------------------\n";

        int id = getIntInput("Enter Customer ID: ");
        if (id <= 0) {
            cout << "Customer ID must be a positive number.\n";
            return;
        }

        if (searchCustomer(id) != nullptr) {
            cout << "Error: Customer ID already exists!\n";
            return;
        }

        string name = getStringInput("Enter Customer Name: ");
        string phone = getStringInput("Enter Phone Number: ");

        customers.push_back(Customer(id, name, phone));
        cout << "\nCustomer added successfully.\n";
    }

    // 2. View Customers
    void displayCustomers() const {
        cout << "\n--------------------------------------------------\n";
        cout << "                 ALL CUSTOMERS                    \n";
        cout << "--------------------------------------------------\n";
        if (customers.empty()) {
            cout << "No customers registered yet.\n";
            return;
        }

        cout << left << setw(10) << "ID"
             << setw(25) << "Name"
             << setw(15) << "Phone" << "\n";
        cout << "--------------------------------------------------\n";
        for (const auto& c : customers) {
            c.display();
        }
    }

    // 3. View Computers (Demonstrates Polymorphism via base pointers)
    void displayComputers() const {
        cout << "\n--------------------------------------------------\n";
        cout << "                 ALL COMPUTERS                    \n";
        cout << "--------------------------------------------------\n";
        cout << left << setw(10) << "ID"
             << setw(16) << "Type"
             << setw(11) << "Rate"
             << setw(12) << "Status" << "\n";
        cout << "--------------------------------------------------\n";
        for (const auto comp : computers) {
            comp->display();
        }
    }

    // 4. Start Session
    void startSession() {
        cout << "\n----------------------------------------\n";
        cout << "             START SESSION              \n";
        cout << "----------------------------------------\n";

        if (customers.empty()) {
            cout << "No customers registered. Please add a customer first.\n";
            return;
        }

        int custId = getIntInput("Enter Customer ID: ");
        Customer* cust = searchCustomer(custId);
        if (!cust) {
            cout << "Error: Customer not found.\n";
            return;
        }

        // Prevent duplicate active session for the same customer
        if (findActiveSessionByCustomer(custId) != nullptr) {
            cout << "Error: Customer '" << cust->getName() << "' already has an active session.\n";
            return;
        }

        // Show available computers
        cout << "\nAvailable Computers:\n";
        cout << left << setw(10) << "ID"
             << setw(16) << "Type"
             << setw(11) << "Rate"
             << setw(12) << "Status" << "\n";
        cout << "--------------------------------------------------\n";
        int availCount = 0;
        for (auto comp : computers) {
            if (comp->isAvailable()) {
                comp->display();
                availCount++;
            }
        }

        if (availCount == 0) {
            cout << "No computers are currently available.\n";
            return;
        }

        int compId = getIntInput("Enter Computer ID to assign: ");
        Computer* comp = findComputer(compId);
        if (!comp) {
            cout << "Error: Computer not found.\n";
            return;
        }

        if (!comp->isAvailable()) {
            cout << "Error: Computer is currently occupied.\n";
            return;
        }

        // Start session
        int sessId = nextSessionId++;
        Session newSession(sessId, custId, compId);
        comp->setAvailability(false);
        sessions.push_back(newSession);

        cout << "\nSession started successfully.\n\n";
        cout << "Session ID : " << sessId << "\n";
        cout << "Customer   : " << cust->getName() << "\n";
        cout << "Computer   : " << compId << "\n";
        cout << "Type       : " << comp->getType() << "\n";
        cout << "Rate       : ₹" << fixed << setprecision(2) << comp->getRate() << "/hour\n";
        cout << "Start Time : " << newSession.getStartTime() << "\n";
    }

    // 5. End Session
    void endSession() {
        cout << "\n----------------------------------------\n";
        cout << "              END SESSION               \n";
        cout << "----------------------------------------\n";

        int sessId = getIntInput("Enter Session ID to end: ");
        Session* sess = findSession(sessId);
        if (!sess) {
            cout << "Error: Session not found.\n";
            return;
        }

        if (!sess->isActive()) {
            cout << "Error: Session is already completed.\n";
            return;
        }

        Computer* comp = findComputer(sess->getComputerId());
        Customer* cust = searchCustomer(sess->getCustomerId());

        if (!comp) {
            cout << "Error: Associated computer not found.\n";
            return;
        }

        // Polymorphic rate calculation
        double rate = comp->getRate();

        // End session and calculate bill
        sess->end(rate);

        // Make computer available again
        comp->setAvailability(true);

        string custName = cust ? cust->getName() : "Unknown";

        // Display formatted bill receipt
        cout << "\n========================================\n";
        cout << "             SESSION BILL               \n";
        cout << "========================================\n\n";
        cout << "Session ID : " << sess->getSessionId() << "\n";
        cout << "Customer   : " << custName << "\n";
        cout << "Computer   : " << comp->getId() << "\n";
        cout << "Type       : " << comp->getType() << "\n\n";
        cout << "Start Time : " << sess->getStartTime() << "\n";
        cout << "End Time   : " << sess->getEndTime() << "\n\n";
        cout << "Duration   : " << fixed << setprecision(2) << sess->getDurationHours() << " hours\n";
        cout << "Rate       : ₹" << fixed << setprecision(2) << rate << "/hour\n\n";
        cout << "Total Bill : ₹" << fixed << setprecision(2) << sess->getBill() << "\n\n";
        cout << "========================================\n";
    }

    // 6. View Active Sessions
    void displayActiveSessions() const {
        cout << "\n----------------------------------------------------------------------\n";
        cout << "                           ACTIVE SESSIONS                            \n";
        cout << "----------------------------------------------------------------------\n";

        int count = 0;
        for (const auto& s : sessions) {
            if (s.isActive()) {
                if (count == 0) {
                    cout << left << setw(12) << "Session ID"
                         << setw(20) << "Customer"
                         << setw(12) << "Computer"
                         << setw(16) << "Type"
                         << setw(12) << "Start Time" << "\n";
                    cout << "----------------------------------------------------------------------\n";
                }

                string custName = "Unknown";
                for (const auto& c : customers) {
                    if (c.getId() == s.getCustomerId()) {
                        custName = c.getName();
                        break;
                    }
                }

                string compType = "Unknown";
                for (const auto comp : computers) {
                    if (comp->getId() == s.getComputerId()) {
                        compType = comp->getType();
                        break;
                    }
                }

                cout << left << setw(12) << s.getSessionId()
                     << setw(20) << custName
                     << setw(12) << s.getComputerId()
                     << setw(16) << compType
                     << setw(12) << s.getStartTime() << "\n";
                count++;
            }
        }

        if (count == 0) {
            cout << "No active sessions.\n";
        }
    }

    // 7. View Session History
    void displaySessionHistory() const {
        cout << "\n------------------------------------------------------------------------------------------\n";
        cout << "                                     SESSION HISTORY                                      \n";
        cout << "------------------------------------------------------------------------------------------\n";

        int count = 0;
        for (const auto& s : sessions) {
            if (!s.isActive()) {
                if (count == 0) {
                    cout << left << setw(10) << "Sess ID"
                         << setw(10) << "Cust ID"
                         << setw(10) << "Comp ID"
                         << setw(14) << "Start Time"
                         << setw(14) << "End Time"
                         << setw(14) << "Duration(h)"
                         << setw(10) << "Bill" << "\n";
                    cout << "------------------------------------------------------------------------------------------\n";
                }

                cout << left << setw(10) << s.getSessionId()
                     << setw(10) << s.getCustomerId()
                     << setw(10) << s.getComputerId()
                     << setw(14) << s.getStartTime()
                     << setw(14) << s.getEndTime()
                     << setw(14) << fixed << setprecision(2) << s.getDurationHours()
                     << "₹" << setw(9) << fixed << setprecision(2) << s.getBill() << "\n";
                count++;
            }
        }

        if (count == 0) {
            cout << "No completed sessions found.\n";
        }
    }
};

/**
 * ============================================================================
 * Main Function & Simple Console Menu
 * ============================================================================
 */
int main() {
    CyberCafe cafe;
    int choice;

    while (true) {
        cout << "\n========================================\n";
        cout << "       CYBER CAFE MANAGEMENT SYSTEM     \n";
        cout << "========================================\n\n";
        cout << "1. Add Customer\n";
        cout << "2. View Customers\n";
        cout << "3. View Computers\n";
        cout << "4. Start Session\n";
        cout << "5. End Session\n";
        cout << "6. View Active Sessions\n";
        cout << "7. View Session History\n";
        cout << "8. Exit\n\n";
        cout << "========================================\n";

        choice = CyberCafe::getIntInput("Enter your choice: ");

        switch (choice) {
            case 1:
                cafe.addCustomer();
                break;
            case 2:
                cafe.displayCustomers();
                break;
            case 3:
                cafe.displayComputers();
                break;
            case 4:
                cafe.startSession();
                break;
            case 5:
                cafe.endSession();
                break;
            case 6:
                cafe.displayActiveSessions();
                break;
            case 7:
                cafe.displaySessionHistory();
                break;
            case 8:
                cout << "\nThank you for using Cyber Cafe Management System. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice! Please enter a number between 1 and 8.\n";
                break;
        }
    }

    return 0;
}
