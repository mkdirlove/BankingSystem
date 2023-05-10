#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

const string FILENAME = "accounts.txt";

struct Account {
    int accountNumber;
    string accountType;
    double balance;
    string transactionHistory;
};

// Function prototypes
void displayMenu();
void createAccount(vector<Account>& accounts);
void displayAccounts(const vector<Account>& accounts);
void performTransaction(vector<Account>& accounts, int accountIndex, double amount, const string& transactionType);
void deposit(vector<Account>& accounts);
void withdraw(vector<Account>& accounts);
void transfer(vector<Account>& accounts);
void saveAccounts(const vector<Account>& accounts);
void loadAccounts(vector<Account>& accounts);
void displayTransactionHistory(const vector<Account>& accounts);

int main() {
    vector<Account> accounts;
    loadAccounts(accounts);

    char choice;
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                createAccount(accounts);
                break;
            case '2':
                displayAccounts(accounts);
                break;
            case '3':
                deposit(accounts);
                break;
            case '4':
                withdraw(accounts);
                break;
            case '5':
                transfer(accounts);
                break;
            case '6':
                displayTransactionHistory(accounts);
                break;
            case '7':
                saveAccounts(accounts);
                break;
            case '8':
                cout << "Exiting the program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
        cout << endl;
    } while (choice != '8');

    return 0;
}

void displayMenu() {
    cout << "----- Bank Transactions -----\n";
    cout << "1. Create Account\n";
    cout << "2. Display Accounts\n";
    cout << "3. Deposit\n";
    cout << "4. Withdraw\n";
    cout << "5. Transfer\n";
    cout << "6. Display Transaction History\n";
    cout << "7. Save Accounts\n";
    cout << "8. Exit\n";
}

void createAccount(vector<Account>& accounts) {
    Account newAccount;

    cout << "Enter account number: ";
    cin >> newAccount.accountNumber;

    auto it = find_if(accounts.begin(), accounts.end(),[&](const Account& acc) {
            return acc.accountNumber == newAccount.accountNumber;
        }
    );

    if (it != accounts.end()) {
        cout << "Account number already exists. Please try again.\n";
        return;
    }

    cout << "Enter account type: ";
    cin >> newAccount.accountType;
    cout << "Enter initial balance: ";
    cin >> newAccount.balance;
    newAccount.transactionHistory = "";

    accounts.push_back(newAccount);
    cout << "Account created successfully.\n";
}

void displayAccounts(const vector<Account>& accounts) {
    if (accounts.empty()) {
        cout << "No accounts to display. Create an account first.\n";
        return;
    }

    cout << "----- Account Details -----\n";
    for (const Account& acc : accounts) {
        cout << "Account Number: " << acc.accountNumber << endl;
        cout << "Account Type: " << acc.accountType << endl;
cout << "Balance: P" << fixed << setprecision(2) << acc.balance << endl;
cout << "Transaction History:\n" << acc.transactionHistory << endl;
cout << endl;
}
}

void performTransaction(vector<Account>& accounts, int accountIndex, double amount, const string& transactionType) {
accounts[accountIndex].balance += amount;
accounts[accountIndex].transactionHistory += transactionType + ": P" + to_string(amount) + "\n";
}

void deposit(vector<Account>& accounts) {
if (accounts.empty()) {
cout << "No accounts to deposit into. Create an account first.\n";
return;
}

int accountNumber;
double amount;

cout << "Enter account number: ";
cin >> accountNumber;

auto it = find_if(accounts.begin(), accounts.end(),
    [&](const Account& acc) {
        return acc.accountNumber == accountNumber;
    }
);

if (it == accounts.end()) {
    cout << "Account number not found. Please try again.\n";
    return;
}

cout << "Enter deposit amount: ";
cin >> amount;

if (amount <= 0) {
    cout << "Invalid deposit amount. Please try again.\n";
    return;
}

performTransaction(accounts, distance(accounts.begin(), it), amount, "Deposit");
cout << "Deposit successful.\n";
}

void withdraw(vector<Account>& accounts) {
if (accounts.empty()) {
cout << "No accounts to withdraw from. Create an account first.\n";
return;
}

int accountNumber;
double amount;

cout << "Enter account number: ";
cin >> accountNumber;

auto it = find_if(accounts.begin(), accounts.end(),
    [&](const Account& acc) {
        return acc.accountNumber == accountNumber;
    }
);

if (it == accounts.end()) {
    cout << "Account number not found. Please try again.\n";
    return;
}

cout << "Enter withdrawal amount: ";
cin >> amount;

if (amount <= 0 || amount > it->balance) {
    cout << "Invalid withdrawal amount. Please try again.\n";
    return;
}

performTransaction(accounts, distance(accounts.begin(), it), -amount, "Withdrawal");
cout << "Withdrawal successful.\n";
}

void transfer(vector<Account>& accounts) {
if (accounts.size() < 2) {
cout << "Insufficient number of accounts to perform a transfer. Create at least two accounts first.\n";
return;
}

int fromAccountNumber, toAccountNumber;
double amount;

cout << "Enter account number to transfer from: ";
cin >> fromAccountNumber;

auto fromAccountIt = find_if(accounts.begin(), accounts.end(),
    [&](const Account& acc) {
        return acc.accountNumber == fromAccountNumber;
    }
);

if (fromAccountIt == accounts.end()) {
    cout << "Account number not found. Please try again.\n";
    return;
}

cout << "Enter account number to transfer to: ";
cin >> toAccountNumber;

auto toAccountIt = find_if(accounts.begin(), accounts.end(),
[&](const Account& acc) {
return acc.accountNumber == toAccountNumber;
}
);

if (toAccountIt == accounts.end()) {
    cout << "Account number not found. Please try again.\n";
    return;
}

cout << "Enter transfer amount: ";
cin >> amount;

if (amount <= 0 || amount > fromAccountIt->balance) {
    cout << "Invalid transfer amount. Please try again.\n";
    return;
}

performTransaction(accounts, distance(accounts.begin(), fromAccountIt), -amount, "Transfer to " + to_string(toAccountNumber));
performTransaction(accounts, distance(accounts.begin(), toAccountIt), amount, "Transfer from " + to_string(fromAccountNumber));
cout << "Transfer successful.\n";
}

void saveAccounts(const vector<Account>& accounts) {
ofstream outFile(FILENAME);
}

void saveAccountsToFile(const vector<Account>& accounts) {
    ofstream outFile(FILENAME);
    if (!outFile) {
        cout << "Error opening file for writing.\n";
        return;
    }

    for (const Account& acc : accounts) {
        outFile << acc.accountNumber << "\n";
        outFile << acc.accountType << "\n";
        outFile << acc.balance << "\n";
        outFile << acc.transactionHistory << "\n";
        outFile << "\n";
    }

    outFile.close();
    cout << "Accounts saved to file.\n";
}


void loadAccounts(vector<Account>& accounts) {
ifstream inFile(FILENAME);
if (!inFile) {
    cout << "No existing account file found.\n";
    return;
}

accounts.clear();
Account account;

while (inFile >> account.accountNumber >> account.accountType >> account.balance) {
    getline(inFile, account.transactionHistory);
    accounts.push_back(account);
}

inFile.close();
cout << "Accounts loaded from file.\n";
}

void displayTransactionHistory(const vector<Account>& accounts) {
if (accounts.empty()) {
cout << "No accounts to display transaction history. Create an account first.\n";
return;
}

int accountNumber;
cout << "Enter account number: ";
cin >> accountNumber;

auto it = find_if(accounts.begin(), accounts.end(),
    [&](const Account& acc) {
        return acc.accountNumber == accountNumber;
    }
);

if (it == accounts.end()) {
    cout << "Account number not found. Please try again.\n";
    return;
}

cout << "----- Transaction History -----\n";
cout << it->transactionHistory << endl;
}
