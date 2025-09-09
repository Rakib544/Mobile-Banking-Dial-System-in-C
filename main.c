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
void showSendMoneyInterface();
void showAddMoneyInterface();
void showPaymentInterface();
void showCashOutInterface();
void showTransactionInterface();
void showLoginInterface();
int login(char *number, int pin);
void showLoggedInOptions();
void showMobileRechargeInterface();
void showResetPinInterface();
void showCrystalPayInterface();

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

void showLoggedInOptions() {
    int choice;
    while (1) {
        printf("\n============ Crystal Pay ============ \n");
        printf("1. Send Money\n");
        printf("2. Add Money\n");
        printf("3. Mobile Recharge\n");
        printf("4. Payment\n");
        printf("5. Cash Out\n");
        printf("6. My Crystal Pay\n");
        printf("7. Reset PIN\n");
        printf("8. Statement\n");
        printf("9. Logout\n");
        printf("\nEnter choice: \n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                showSendMoneyInterface();
                break;
            case 2:
                showAddMoneyInterface();
                break;
            case 3:
                showMobileRechargeInterface();
                break;
            case 4:
                showPaymentInterface();
                break;
            case 5:
                showCashOutInterface();
                break;
            case 6:
                showCrystalPayInterface();
                break;
            case 7:
                showResetPinInterface();
                break;
            case 8:
                showTransactionInterface();
                break;
            case 9:
                printf("\nLogging out...\n\n");
                return;
            default:
                printf("\nError: Invalid choice. Try again.\n\n");
        }
    }
}

void showLoginInterface() {
    char number[12];
    int pin;

    printf("\n============== Login ============== \n");
    printf("\nEnter your number: \n");
    scanf("%11s", number);

    printf("\nEnter your PIN: \n");
    scanf("%d", &pin);

    if (login(number, pin)) {
        printf("\nLogin successful!\n\n");
        showLoggedInOptions();
    } else {
        printf("\nError: Invalid number or PIN.\n\n");
    }
}

void showResetPinInterface() {
    int oldPin;
    printf("\n=========== Reset PIN ============ \n");
    printf("\nEnter your old PIN: \n");
    scanf("%d", &oldPin);

    if (oldPin == users[loggedInUserIndex].pin) {
        int newPin;
        printf("\nEnter your new 4-digit PIN: \n");
        scanf("%d", &newPin);
        users[loggedInUserIndex].pin = newPin;
        printf("\nPIN changed successfully!\n");
        printf("New PIN: %d\n\n", newPin);
    } else {
        printf("\nError: Incorrect old PIN. Contact customer support.\n\n");
    }
}

void showCrystalPayInterface() {
    printf("\n========= My Crystal Pay ========= \n");
    printf("\nRemaining Balance: %.2f TK\n", users[loggedInUserIndex].balance);
    printf("\nThank you for using Crystal Pay.\n");
    printf("Download our mobile app for a better experience.\n\n");
}

void showMobileRechargeInterface() {
    if (loggedInUserIndex == -1) {
        printf("\nError: You must log in first!\n\n");
        return;
    }

    char mobileNumber[12];
    float amount;
    int enteredPin;

    printf("\n======== Mobile Recharge ========= \n");
    printf("\nEnter mobile number (11 digits): \n");
    scanf("%s", mobileNumber);

    if (strlen(mobileNumber) != 11) {
        printf("\nError: Invalid mobile number! Must be 11 digits.\n\n");
        return;
    }

    printf("\nEnter recharge amount: \n");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("\nError: Invalid amount!\n\n");
        return;
    }

    if (users[loggedInUserIndex].balance < amount) {
        printf("\nError: Insufficient balance!\n\n");
        return;
    }

    printf("\nEnter your PIN to confirm: \n");
    scanf("%d", &enteredPin);

    if (enteredPin != users[loggedInUserIndex].pin) {
        printf("\nError: Invalid PIN! Recharge cancelled.\n\n");
        return;
    }

    users[loggedInUserIndex].balance -= amount;

    if (transactionCount < MAX_TRANSACTIONS) {
        strcpy(transactions[transactionCount].type, "Mobile Recharge");
        transactions[transactionCount].amount = amount;
        strcpy(transactions[transactionCount].target, mobileNumber);
        strcpy(transactions[transactionCount].reference, "Recharge successful");
        transactionCount++;
    }

    printf("\nTransaction successful!\n");
    printf("Receiver: %s\n", mobileNumber);
    printf("Amount: %.2f\n", amount);
    printf("New Balance: %.2f\n", users[loggedInUserIndex].balance);
    printf("--------------------------------------\n\n");
}

void showSendMoneyInterface() {
    char receiver[12];
    float amount;
    char reference[50];
    int pin;

    printf("\n========== Send Money ========== \n");
    printf("\nEnter receiver account number: \n");
    scanf("%s", receiver);

    printf("\nEnter amount: \n");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("\nError: Invalid amount. Enter a positive value.\n\n");
        return;
    }

    if (amount > users[loggedInUserIndex].balance) {
        printf("\nError: Insufficient balance.\n\n");
        return;
    }

    printf("\nEnter reference: \n");
    scanf("%s", reference);

    printf("\nEnter PIN to confirm: \n");
    scanf("%d", &pin);

    int receiverIndex = -1;
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].number, receiver) == 0) {
            receiverIndex = i;
            break;
        }
    }

    if (receiverIndex == -1) {
        printf("\nError: Invalid receiver account number.\n\n");
        return;
    }

    if (users[loggedInUserIndex].pin != pin) {
        printf("\nError: Incorrect PIN.\n\n");
        return;
    }

    users[receiverIndex].balance += amount;
    users[loggedInUserIndex].balance -= amount;

    strcpy(transactions[transactionCount].type, "Send Money");
    transactions[transactionCount].amount = amount;
    strcpy(transactions[transactionCount].target, receiver);
    strcpy(transactions[transactionCount].reference, reference);
    transactionCount++;

    printf("\nTransaction successful!\n");
    printf("Receiver: %s\n", receiver);
    printf("Amount: %.2f\n", amount);
    printf("Reference: %s\n", reference);
    printf("New Balance: %.2f\n", users[loggedInUserIndex].balance);
    printf("--------------------------------------\n\n");
}

void showAddMoneyInterface() {
    int sourceChoice;
    float amount;
    int pin;
    char inputNumber[20];

    printf("\n========== Add Money ========== \n");
    printf("\nSelect source:\n");
    printf("1. Card to Crystal Pay\n");
    printf("2. Bank to Crystal Pay\n");
    printf("\nEnter choice: \n");
    scanf("%d", &sourceChoice);

    if (sourceChoice < 1 || sourceChoice > 2) {
        printf("\nError: Invalid source choice.\n\n");
        return;
    }

    printf("\nEnter %s number: \n", sourceChoice == 1 ? "card" : "account");
    scanf("%s", inputNumber);

    printf("\nEnter amount to add: \n");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("\nError: Invalid amount.\n\n");
        return;
    }

    printf("\nEnter PIN to confirm: \n");
    scanf("%d", &pin);

    if (pin != users[loggedInUserIndex].pin) {
        printf("\nError: Incorrect PIN.\n\n");
        return;
    }

    users[loggedInUserIndex].balance += amount;
    strcpy(transactions[transactionCount].type, "Add Money");
    transactions[transactionCount].amount = amount;
    strcpy(transactions[transactionCount].target, inputNumber);
    transactionCount++;

    printf("\nTransaction successful!\n");
    printf("Source: %s\n", inputNumber);
    printf("Amount: %.2f\n", amount);
    printf("New Balance: %.2f\n", users[loggedInUserIndex].balance);
    printf("--------------------------------------\n\n");
}

void showPaymentInterface() {
    char merchantNumber[12];
    float amount;
    int pin;

    printf("\n======= Payment to Merchant ======= \n");
    printf("\nEnter merchant number: \n");
    scanf("%s", merchantNumber);

    printf("\nEnter amount: \n");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("\nError: Invalid amount.\n\n");
        return;
    }

    if (amount > users[loggedInUserIndex].balance) {
        printf("\nError: Insufficient balance.\n\n");
        return;
    }

    printf("\nEnter PIN to confirm: \n");
    scanf("%d", &pin);

    if (pin != users[loggedInUserIndex].pin) {
        printf("\nError: Incorrect PIN. Payment cancelled.\n\n");
        return;
    }

    users[loggedInUserIndex].balance -= amount;

    strcpy(transactions[transactionCount].type, "Payment");
    transactions[transactionCount].amount = amount;
    strcpy(transactions[transactionCount].target, merchantNumber);
    transactionCount++;

    printf("\nTransaction successful!\n");
    printf("Receiver: %s\n", merchantNumber);
    printf("Amount: %.2f\n", amount);
    printf("New Balance: %.2f\n", users[loggedInUserIndex].balance);
    printf("--------------------------------------\n\n");
}

void showCashOutInterface() {
    char agentNumber[12];
    float amount;
    int pin;

    printf("\n=========== Cash Out =========== \n");
    printf("\nEnter agent number: \n");
    scanf("%s", agentNumber);

    printf("\nEnter amount to cash out: \n");
    scanf("%f", &amount);

    if (amount <= 0 || amount > users[loggedInUserIndex].balance) {
        printf("\nError: Invalid amount or insufficient balance.\n\n");
        return;
    }

    printf("\nEnter PIN to confirm: \n");
    scanf("%d", &pin);

    if (pin != users[loggedInUserIndex].pin) {
        printf("\nError: Incorrect PIN. Cash out cancelled.\n\n");
        return;
    }

    users[loggedInUserIndex].balance -= amount;

    strcpy(transactions[transactionCount].type, "Cash Out");
    transactions[transactionCount].amount = amount;
    strcpy(transactions[transactionCount].target, agentNumber);
    transactionCount++;

    printf("\nTransaction successful!\n");
    printf("Receiver: %s\n", agentNumber);
    printf("Amount: %.2f\n", amount);
    printf("New Balance: %.2f\n", users[loggedInUserIndex].balance);
    printf("--------------------------------------\n\n");
}

void showTransactionInterface() {
    printf("\n======= Transaction History ======= \n");
    if (transactionCount <= 0) {
        printf("\nNo transaction history found.\n\n");
    } else {
        for (int i = 0; i < transactionCount; i++) {
            printf("\nTransaction #%d\n", i + 1);
            printf("Type: %s\n", transactions[i].type);
            printf("Receiver: %s\n", transactions[i].target);
            printf("Amount: %.2f\n", transactions[i].amount);
            printf("Reference: %s\n", transactions[i].reference);
            printf("--------------------------------------\n");
        }
    }
    printf("\n");
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
        printf("\n============ Crystal Pay ============ \n");
        printf("1. Login\n");
        printf("0. Exit\n");
        printf("\nEnter choice: \n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                showLoginInterface();
                break;
            case 0:
                printf("\nExiting program...\n\n");
                exit(0);
            default:
                printf("\nError: Invalid choice. Try again.\n\n");
        }
    }
    return 0;
}
