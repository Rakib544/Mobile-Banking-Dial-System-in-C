#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// =====================
// Constants and Structs
// =====================

#define MAX_USERS 100
#define MAX_TRANSACTIONS 100

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

    printf("Enter your number: ");
    scanf("%s", number);
    printf("Enter your pin: ");
    scanf("%d", &pin);

    if (login(number, pin)) {
        printf("\n\nYou have logged in successfully.\n\n");
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
                printf("\n--- Add Money ---\n");
                break;
            case 3:
                printf("\n--- Mobile Recharge ---\n");
                break;
            case 4:
                printf("\n--- Payment ---\n");
                break;
            case 5:
                printf("\n--- Cash Out ---\n");
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

    printf("\n--- Send Money ---\n");
    printf("Enter receiver bKash account no: ");
    scanf("%s", receiver);
    printf("Enter amount: ");
    scanf("%f", &amount);
    printf("Enter reference: ");
    scanf("%s", reference);
    printf("Enter PIN to confirm: ");
    scanf("%d", &pin);
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