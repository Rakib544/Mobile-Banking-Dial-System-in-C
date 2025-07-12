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
};


struct Card {
    char cardNumber[20];
    int pin;
    float balance;
};

struct BankAccount {
    char accountNumber[20];
    int pin;
    float balance;
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
void showLoginForm();
int login(char *number, int pin);

// Main Logged-in Menu
void showLoggedInOptions();

// Feature Interfaces
void showSendMoneyInterface();

//Add money interface 

void showAddMoneyInterface();

// Marchent Payment system 

void showPaymentInterface();


//cashout Interface

void showCashOutInterface();


// =====================
// Function Definitions
// =====================

// ---------------------
// Authentication
// ---------------------

int login(char *number, int pin) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].number, number) == 0 && users[i].pin == pin) {
            loggedInUserIndex = i;
            return 1;
        }
    }
    return 0;
}

void showLoginForm() {
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
        printf("Number or PIN invalid.\n");
    }
}

// ---------------------
// Main Logged-in Menu
// ---------------------

void showLoggedInOptions() {
    int choice;
    while (1) {
        printf("\n=== Payment Management System ===\n");
        printf("1. Send Money\n");
        printf("2. Add Money\n");
        printf("3. Mobile Recharge\n");
        printf("4. Payment\n");
        printf("5. Cash Out\n");
        printf("6. My bKash\n");
        printf("7. Reset PIN\n");
        printf("8. Logout\n");
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
                printf("\n--- My bKash ---\n");
                break;
            case 7:
                printf("\n--- Reset PIN ---\n");
                break;
            case 8:
                printf("Logging out...\n");
                return;
            default:
                printf("Invalid choice. Try again.\n\n");
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

    printf("\n=== Send Money ===\n\n");
    printf("Enter receiver bKash account no: ");
    scanf("%s", receiver);
    printf("Enter amount: ");
    scanf("%f", &amount);
    printf("Enter reference: ");
    scanf("%s", reference);
    printf("Enter PIN to confirm: ");
    scanf("%d", &pin);
    printf("\n\nMoney sent successfully.\n\n");
}


// ---------------------
// Feature Interfaces Add Money
// ---------------------

void showAddMoneyInterface() {
    int sourceChoice;
    float amount;
    int pin;
    char inputNumber[20];
    int found = 0;

    printf("\n--- Add Money ---\n");
    printf("Select Source:\n");
    printf("1. Card to bKash\n");
    printf("2. Bank to bKash\n");
    printf("Enter choice: ");
    scanf("%d", &sourceChoice);

    printf("Enter account/card number: ");
    scanf("%s", inputNumber);
    printf("Enter PIN: ");
    scanf("%d", &pin);
    printf("Enter amount to add: ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("Invalid amount.\n");
        return;
    }

    if (sourceChoice == 1) {
        // Card to bKash
        for (int i = 0; i < cardCount; i++) {
            if (strcmp(cards[i].cardNumber, inputNumber) == 0 && cards[i].pin == pin) {
                found = 1;
                if (cards[i].balance >= amount) {
                    cards[i].balance -= amount;
                    users[loggedInUserIndex].balance += amount;

                    // Log transaction
                    if (transactionCount < MAX_TRANSACTIONS) {
                        strcpy(transactions[transactionCount].type, "Add from Card");
                        transactions[transactionCount].amount = amount;
                        strcpy(transactions[transactionCount].target, users[loggedInUserIndex].number);
                        transactionCount++;
                    }

                    printf("Amount added from card. New bKash balance: %.2f\n", users[loggedInUserIndex].balance);
                } else {
                    printf("Insufficient card balance.\n");
                }
                break;
            }
        }
        if (!found) {
            printf("Card number or PIN invalid.\n");
        }
    } else if (sourceChoice == 2) {
        // Bank to bKash
        for (int i = 0; i < bankCount; i++) {
            if (strcmp(banks[i].accountNumber, inputNumber) == 0 && banks[i].pin == pin) {
                found = 1;
                if (banks[i].balance >= amount) {
                    banks[i].balance -= amount;
                    users[loggedInUserIndex].balance += amount;

                    // Log transaction
                    if (transactionCount < MAX_TRANSACTIONS) {
                        strcpy(transactions[transactionCount].type, "Add from Bank");
                        transactions[transactionCount].amount = amount;
                        strcpy(transactions[transactionCount].target, users[loggedInUserIndex].number);
                        transactionCount++;
                    }

                    printf("Amount added from bank. New bKash balance: %.2f\n", users[loggedInUserIndex].balance);
                } else {
                    printf("Insufficient bank account balance.\n");
                }
                break;
            }
        }
        if (!found) {
            printf("Bank account number or PIN invalid.\n");
        }
    } else {
        printf("Invalid source choice.\n");
    }
}



// ---------------------
// Feature Interfaces Add Money
// ---------------------


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


//------------------------
//cashout Interface 
//------------------------

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


// =====================
// Main Function
// =====================

void initializeDummyUsers() {
    strcpy(users[0].number, "01786542643");
    users[0].pin = 1111;
    users[0].balance = 5000;
    userCount++;
}

// Dummy Cards & Banks
void initializeDummyAccounts() {
   
    strcpy(cards[0].cardNumber, "1234567890123456");
    cards[0].pin = 2242;
    cards[0].balance = 10000;
    cardCount++;
 
    strcpy(banks[0].accountNumber, "9876543210");
    banks[0].pin = 2250;
    banks[0].balance = 20000;
    bankCount++;
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
                showLoginForm();
                break;
            case 0:
                printf("Exiting program...\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n\n");
        }
    }
    return 0;
}