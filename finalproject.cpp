#include <iostream>
#include <string>
using namespace std;

// Base class for common functionality
class Person {
private:
    string ID, name, phone; //three attributes for the class 'Person'

public:
    // Constructor to initialize member variables publicly, Polymorphism
    Person(string ID, string name, string phone) : ID(ID), name(name), phone(phone){}

    // Display information for a person
    void display() const {
        cout << "ID: " << getID() << endl;
        cout << "Name: " << getName() << endl;
        cout << "Phone Number: " << getPhone() << endl;
    }

    // Getter methods for accessing private member variables
    string getID() const
    { 
        return ID; 
    }
    string getName() const 
    {
        return name; 
    }
    string getPhone() const 
    {
        return phone;
    }

    // Setter methods for private member variables
    void setID(string newID)
    {
        ID = newID; 
    }
    void setName(string newName)
    {
        name = newName; 
    }
    void setPhone(string newPhone)
    {
        phone = newPhone;
    }
};

// Derived class from the base class Person
class BankCustomer : public Person { //Inheritance
private:
    int cash;
    int maxTransactions;
    int *transactionHistory;
    int numTransactions;
    double interestRate;

public:
    // Constructors
    BankCustomer() : Person("", "", ""), cash(0), maxTransactions(100), numTransactions(0), interestRate(0.098) 
    {
        transactionHistory = new int[maxTransactions]();//array
    }

    BankCustomer(string ID, string name, string phone, int cash):Person(ID, name, phone), cash(cash), maxTransactions(100), numTransactions(0), interestRate(0.098) 
    {
        transactionHistory = new int[maxTransactions]();
    }

    // Destructor for releasing allocated memory
    ~BankCustomer()
    {
        delete[] transactionHistory;
    }

    // Getter method for accessing private member variable
    int getCash() const 
    {
        return cash;
    }

    // Deposit and Withdrawal functions
    void performTransaction(int amount);
    void deposit(int amount);
    void withdraw(int amount);
    void showTransactionHistory() const;
    void calculateInterest();

    // Setter method for maxTransactions
    void setMaxTransactions(int maxTrans) 
    {
        maxTransactions = maxTrans;
    }
};

// Define member functions for the BankCustomer class (continued)
void BankCustomer::performTransaction(int amount) { // :: scope resolution operator
    if (amount >= 0) { //Condition
        deposit(amount);
    } else {
        withdraw(amount);
    }
}

void BankCustomer::deposit(int amount) {
    if (numTransactions < maxTransactions && amount > 0) {
        cash += amount;
        transactionHistory[numTransactions++] = amount;
        cout << "Transaction successful! New balance: " << getCash() << endl;
    } else {
        cout << "Invalid deposit amount or transaction history limit reached." << endl;
    }
}

void BankCustomer::withdraw(int amount) {
    if (numTransactions < maxTransactions && amount < 0) {
        if (cash >= -amount) {
            cash += amount;
            transactionHistory[numTransactions++] = amount;
            cout << "Transaction successful! New balance: " << getCash() << endl;
        } else {
            cout << "Insufficient funds for withdrawal! Current balance: " << getCash() << endl;
        }
    } else {
        cout << "Invalid withdrawal amount or transaction history limit reached." << endl;
    }
}

void BankCustomer::showTransactionHistory() const {
    cout << "Transaction History for Customer ID: " << getID() << endl;
    int currentBalance = 0;
    for (int i = 0; i < numTransactions; ++i) {
        currentBalance += transactionHistory[i];
        if (transactionHistory[i] > 0) {
            cout << "Deposit: " << transactionHistory[i] << endl;
        } else {
            cout << "Withdrawal: " << -transactionHistory[i] << endl;
        }
    }
}

void BankCustomer::calculateInterest() {
    double interest = getCash() * interestRate;
    cout << "Interest calculated for Customer ID: " << getID() << " is: " << interest << endl;
}

// Bank class for managing customer accounts

class Bank {
private:
    int maxCustomers;
    BankCustomer *customerList;
    int reccompleted;

public:
    Bank() : maxCustomers(100), reccompleted(0) {
        customerList = new BankCustomer[maxCustomers];
    }

    // Destructor for releasing allocated memory
    ~Bank() {
        delete[] customerList;
    }

    // Provide options for the user
    void options();

    // Create a new customer account
    void newAccount();

    // Display information for all customers
    void display() const;

    // Search for a specific customer and display their information
    void search() const;

    // Deposit and Withdrawal function
    void deposit();

    // Transaction History function
    void showTransactionHistory() const;

    // Calculate Interest function
    void calculateInterest() const;

    // Get Total Balance function
    void getTotalBalance() const;
};

// Entry point of the program
int main() {
    cout << "\t\t\t\t\tWelcome to AK Bank Nepal!\t\t\t\t\t\t" << endl;
    cout << "\t\t\t\tAK BANK, Where Your Journey to Financial Success Begins" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------------" << endl;

    Bank obj;
    obj.options(); //dot operators to access attributes of the class 
    return 0;
}

// Define member functions for the Bank class
void Bank::options() {
    char select;
    while (true) {
        cout << "\nPress 1 for Creating New Account." << endl;
        cout << "Press 2 for Displaying the Customer Information." << endl;
        cout << "Press 3 for Searching Specific Customer Details." << endl;
        cout << "Press 4 for Deposit and Withdrawal." << endl;
        cout << "Press 5 for Transaction History." << endl;
        cout << "Press 6 for Interest Calculation." << endl;
        cout << "Press 7 for Total Balance in the Bank." << endl;
        cout << "Press 8 to Exit.\n" << endl;
        cin >> select;

        switch (select) {
            case '1':
                newAccount();
                break;
            case '2':
                display();
                break;
            case '3':
                search();
                break;
            case '4':
                deposit();
                break;
            case '5':
                showTransactionHistory();
                break;
            case '6':
                calculateInterest();
                break;
            case '7':
                getTotalBalance();
                break;
            case '8':
                cout << "Exiting the program. Thank you for using AK Bank Nepal!" << endl;
                return;
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    }
}

// Define member functions for the Bank class (continued)
void Bank::newAccount() {
    cout << "\n\nNew Account is being created.\n" << endl;
    string ID, name, phone, idcard;
    int cash;

    cout << "Enter your ID: ";
    cin >> ID;

    cout << "Enter your Name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter your Phone Number: ";
    cin >> phone;
    cout << "Enter Initial Cash Amount: ";
    cin >> cash;

    customerList[reccompleted] = BankCustomer(ID, name, phone, cash);
    reccompleted++;
}

void Bank::display() const {
    for (int i = 0; i < reccompleted; i++) {
        customerList[i].display();
        cout << "Current Balance: " << customerList[i].getCash() << endl;
    }

    getTotalBalance();
}

void Bank::search() const {
    string id;
    cout << "Enter the id of the customer whose details are to be searched: ";
    cin >> id;

    for (int i = 0; i < reccompleted; i++) {
        if (id == customerList[i].getID()) {
            customerList[i].display();
            cout << "Current Balance: " << customerList[i].getCash() << endl;
            return;
        }
    }
    cout << "Customer not found with ID: " << id << endl;
}

void Bank::deposit() {
    string id;
    int amount;
    cout << "Enter the id of the customer for deposit/withdrawal: ";
    cin >> id;

    for (int i = 0; i < reccompleted; i++) {
        if (id == customerList[i].getID()) {
            cout << "Enter the amount for deposit (positive) or withdrawal (negative): ";
            cin >> amount;
            customerList[i].performTransaction(amount);
            return;
        }
    }

    cout << "Customer not found with ID: " << id << endl;
}

void Bank::showTransactionHistory() const {
    string id;
    cout << "Enter the id of the customer to view transaction history: ";
    cin >> id;

    for (int i = 0; i < reccompleted; i++) {
        if (id == customerList[i].getID()) {
            customerList[i].showTransactionHistory();
            return;
        }
    }

    cout << "Customer not found with ID: " << id << endl;
}

void Bank::calculateInterest() const {
    string id;
    cout << "Enter the id of the customer for interest calculation: ";
    cin >> id;

    for (int i = 0; i < reccompleted; i++) {
        if (id == customerList[i].getID()) {
            customerList[i].calculateInterest();
            return;
        }
    }

    cout << "Customer not found with ID: " << id << endl;
}

void Bank::getTotalBalance() const {
    int totalBalance = 0;
    for (int i = 0; i < reccompleted; i++) {
        totalBalance += customerList[i].getCash();
    }

    cout << "Total Balance in the Bank: " << totalBalance << endl;
}
