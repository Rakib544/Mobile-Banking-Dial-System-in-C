#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// =====================
// Constants and Structs
// =====================

#define MAX_USERS 100
#define MAX_TRANSACTIONS 100
#define MAX_CARDS 10
#define MAX_BANKS 10

struct User {
    char number[12]; // 11-digit number + null terminator
    int pin;
    float balance;
};

struct Transaction {
    char type[20];
    float amount;
    char target[12]; // 11-digit number + null terminator
    char reference[50];
};

// =====================
// Global Variables
// =====================

struct User users[MAX_USERS];
int userCount = 0;

struct Transaction transactions[MAX_TRANSACTIONS];
int transactionCount = 0;

int loggedInUserIndex = -1;

// =====================
// Function Prototypes
// =====================

// Authentication
void showLoginInterface();
int login(char *number, int pin);

// Main Logged-in Menu
void showLoggedInOptions();
void showSendMoneyInterface();
void showAddMoneyInterface();
void showPaymentInterface();
void showCashOutInterface();
void showTransactionInterface();


// =====================
// Function Definitions
// =====================

int login(char *number, int pin) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].number, number) == 0 && users[i].pin == pin) {
            loggedInUserIndex = i;
            return 1;
        }
    }
    return 0;
}


// =====================
// Interfaces
// =====================

void showLoginInterface() {
    char number[12];
    int pin;

    printf("\n\n === Login to your account ===\n\n");
    printf("Enter your number: ");
    scanf("%s", number);
    printf("Enter your pin: ");
    scanf("%d", &pin);

    if (login(number, pin)) {
        printf("\nYou have logged in successfully.\n\n");
        showLoggedInOptions();
    } else {
        printf("\nNumber or PIN invalid.\n\n");
    }
}

void showLoggedInOptions() {
    int choice;
    while (1) {
        printf("\n=== Payment Management System ===\n");
        printf("1. Send Money\n");
        printf("2. Add Money\n");
        printf("3. Mobile Recharge\n");
        printf("4. Payment\n");
        printf("5. Cash Out\n");
        printf("6. My crystalPay\n");
        printf("7. Reset PIN\n");
        printf("8. Transactions\n");
        printf("9. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                showSendMoneyInterface();
                break;
            case 2:
                showAddMoneyInterface();
                break;
            case 3:
                printf("\n--- Mobile Recharge ---\n");
                break;
            case 4:
                showPaymentInterface();
                break;
            case 5:
                showCashOutInterface();
                break;
            case 6:
                printf("\n--- My crystalPay ---\n");
                break;
            case 7:
                printf("\n--- Reset PIN ---\n");
                break;
            case 8:
                showTransactionInterface();
                return;
            case 9:
                printf("\nLogging out...\n");
                return;
            default:
                printf("\nInvalid choice. Try again.\n\n");
        }
    }
}

// ---------------------
// Feature Interfaces
// ---------------------

void showSendMoneyInterface() {
    char receiver[12];
    float amount;
    char reference[50];
    int pin;

    printf("\n--- Send Money ---\n\n");

    printf("Enter receiver account number: ");
    scanf("%s", receiver);

    printf("Enter amount: ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("\nInvalid amount. Please enter a positive value.\n");
        return;
    }

    if (amount > users[loggedInUserIndex].balance) {
        printf("\nTransaction failed: Insufficient balance.\n");
        return;
    }

    printf("Enter reference: ");
    scanf("%s", reference);

    printf("Enter PIN to confirm: ");
    scanf("%d", &pin);

    int receiverIndex = -1;
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].number, receiver) == 0) {  
            receiverIndex = i;
            break;  
        }
    }

    if (receiverIndex == -1) {
        printf("\nTransaction failed: Invalid receiver account number.\n");
        return;
    }

    if (users[loggedInUserIndex].pin != pin) {
        printf("\nTransaction failed: Incorrect PIN.\n");
        return;
    }

    users[receiverIndex].balance += amount;
    users[loggedInUserIndex].balance -= amount;

    strcpy(transactions[transactionCount].type, "Sent Money");
    transactions[transactionCount].amount = amount;
    strcpy(transactions[transactionCount].target, receiver);
    strcpy(transactions[transactionCount].reference, reference);
    transactionCount++;

    printf("\nTransaction successful.\n");
    printf("Receiver: %s\n", receiver);
    printf("Amount Sent: %.2f\n", amount);
    printf("Reference: %s\n", reference);
    printf("Your New Balance: %.2f\n\n", users[loggedInUserIndex].balance);
}

void showAddMoneyInterface() {
    int sourceChoice;
    float amount;
    int pin;
    char inputNumber[20];
    int found = 0;

    printf("\n--- Add Money ---\n");
    printf("Select Source:\n");
    printf("1. Card to crystalPay\n");
    printf("2. Bank to crystalPay\n");
    printf("Enter choice: ");
    scanf("%d", &sourceChoice);

    if(sourceChoice == 1) {
        printf("Enter card number: ");
    }else {
        printf("Enter account number: ");
    }
    scanf("%s", inputNumber);
    printf("Enter amount to add: ");
    scanf("%f", &amount);
    printf("Enter PIN: ");
    scanf("%d", &pin);

    if (amount <= 0) {
        printf("Invalid amount.\n");
        return;
    }

    if(sourceChoice > 2 || sourceChoice < 1) {
        printf("Invalid source choice.\n");
        return;
    }
    users[loggedInUserIndex].balance += amount;
    printf("\n\n");
    printf("Successfully added amount - %f from account - %s \n", amount, inputNumber);
    printf("Current balance is - %f \n\n", users[loggedInUserIndex].balance);
}

void showPaymentInterface() {
    char merchantNumber[12];
    float amount;
    int pin;

    printf("\n--- Payment to Merchant ---\n");
    printf("Enter merchant number: ");
    scanf("%s", merchantNumber);

    printf("Enter amount: ");
    scanf("%f", &amount);
    printf("Enter PIN to confirm: ");
    scanf("%d", &pin);

    if (pin != users[loggedInUserIndex].pin) {
        printf("Incorrect PIN. Payment cancelled.\n");
        return;
    }

    if (amount <= 0 || amount > users[loggedInUserIndex].balance) {
        printf("Invalid amount or insufficient balance.\n");
        return;
    }

    users[loggedInUserIndex].balance -= amount;

    // Log transaction
    if (transactionCount < MAX_TRANSACTIONS) {
        strcpy(transactions[transactionCount].type, "Payment");
        transactions[transactionCount].amount = amount;
        strcpy(transactions[transactionCount].target, merchantNumber);
        transactionCount++;
    }

    printf("Payment successful to merchant %s. New Balance: %.2f\n", merchantNumber, users[loggedInUserIndex].balance);
}

void showCashOutInterface() {
    char agentNumber[12];
    float amount;
    int pin;

    printf("\n--- Cash Out ---\n");
    printf("Enter agent number: ");
    scanf("%s", agentNumber);
    printf("Enter amount to cash out: ");
    scanf("%f", &amount);
    printf("Enter PIN to confirm: ");
    scanf("%d", &pin);

    if (pin != users[loggedInUserIndex].pin) {
        printf("Incorrect PIN. Cash out cancelled.\n");
        return;
    }

    if (amount <= 0 || amount > users[loggedInUserIndex].balance) {
        printf("Invalid amount or insufficient balance.\n");
        return;
    }

    users[loggedInUserIndex].balance -= amount;

    // Log the transaction
    if (transactionCount < MAX_TRANSACTIONS) {
        strcpy(transactions[transactionCount].type, "Cash Out");
        transactions[transactionCount].amount = amount;
        strcpy(transactions[transactionCount].target, agentNumber);
        transactionCount++;
    }

    printf("Cash out successful to agent %s. New Balance: %.2f\n", agentNumber, users[loggedInUserIndex].balance);
}

void showTransactionInterface() {
    if (transactionCount <= 0) {
        printf("\nNo transaction history found.\n");
    } else {
        printf("\n=========== Transaction History ===========\n\n");

        for (int i = 0; i < transactionCount; i++) {
            printf("Transaction #%d\n", i + 1);
            printf("Type      : %s\n", transactions[i].type);
            printf("Receiver  : %s\n", transactions[i].target);
            printf("Amount    : %.2f\n", transactions[i].amount);
            printf("Reference : %s\n", transactions[i].reference);
            printf("-------------------------------------------\n");
        }
    }

    showLoggedInOptions();
}

// =====================
// Main Function
// =====================

void initializeDummyUsers() {
    struct User dummy[] = {
        {"01786542643", 1111, 5000},
        {"01857376609", 2222, 7000},
        {"01309179368", 3333, 10000},
        {"01792456904", 4444, 6000}
    };

    int n = sizeof(dummy) / sizeof(dummy[0]);
    for(int i = 0; i < n; i++) {
        strcpy(users[i].number, dummy[i].number);
        users[i].pin = dummy[i].pin;
        users[i].balance = dummy[i].balance;
        userCount++;
    }
}

int main() {
    int choice;

    initializeDummyUsers();

    while (1) {
        printf("\n=== Payment Management System ===\n");
        printf("1. Login\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                showLoginInterface();
                break;
            case 0:
                printf("\nExiting program...\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n\n");
        }
    }
    return 0;
}