#include <stdio.h>
#include <string.h>

#define MAX_ACCOUNTS 5
#define MAX_TXN 10
#define MAX_PIN_ATTEMPTS 3

typedef struct {
    int acc_no;
    char name[50];
    int pin;
    double balance;
    double txns[MAX_TXN]; // positive: deposit, negative: withdrawal
    int txn_count;
} Account;

/* Function prototypes */
void initAccounts(Account accounts[], int *n);
int findAccountIndex(Account accounts[], int n, int acc_no);
int authenticate(Account *acc);
void showMenu();
void balanceInquiry(Account *acc);
void deposit(Account *acc);
void withdrawAmt(Account *acc);
void miniStatement(Account *acc);
void changePin(Account *acc);
void recordTxn(Account *acc, double amount);

int main() {
    Account accounts[MAX_ACCOUNTS];
    int n = 0;
    initAccounts(accounts, &n);

    int acc_no;
    printf("Welcome to ATM Simulator (C)\n");
    while (1) {
        printf("\nEnter account number (0 to exit): ");
        if (scanf("%d", &acc_no) != 1) {
            // clear invalid input
            while (getchar() != '\n');
            printf("Invalid input. Try again.\n");
            continue;
        }
        if (acc_no == 0) {
            printf("Goodbye!\n");
            break;
        }

        int idx = findAccountIndex(accounts, n, acc_no);
        if (idx == -1) {
            printf("Account %d not found.\n", acc_no);
            continue;
        }

        if (!authenticate(&accounts[idx])) {
            printf("Authentication failed. Returning to account entry.\n");
            continue;
        }

        int choice;
        do {
            showMenu();
            printf("Choose option: ");
            if (scanf("%d", &choice) != 1) {
                while (getchar() != '\n');
                printf("Invalid input. Returning to menu.\n");
                choice = -1;
                continue;
            }

            switch(choice) {
                case 1: balanceInquiry(&accounts[idx]); break;
                case 2: withdrawAmt(&accounts[idx]); break;
                case 3: deposit(&accounts[idx]); break;
                case 4: miniStatement(&accounts[idx]); break;
                case 5: changePin(&accounts[idx]); break;
                case 6: printf("Logging out...\n"); break;
                default: printf("Invalid option. Try again.\n");
            }
        } while (choice != 6);
    }

    return 0;
}

/* Initialize a few sample accounts */
void initAccounts(Account accounts[], int *n) {
    *n = 3;
    accounts[0].acc_no = 1001;
    strcpy(accounts[0].name, "Anwarul");
    accounts[0].pin = 1234;
    accounts[0].balance = 5000.0;
    accounts[0].txn_count = 0;

    accounts[1].acc_no = 1002;
    strcpy(accounts[1].name, "Deva");
    accounts[1].pin = 1111;
    accounts[1].balance = 15000.50;
    accounts[1].txn_count = 0;

    accounts[2].acc_no = 1003;
    strcpy(accounts[2].name, "Priyansu");
    accounts[2].pin = 2222;
    accounts[2].balance = 750.75;
    accounts[2].txn_count = 0;
}

/* Find account index by account number */
int findAccountIndex(Account accounts[], int n, int acc_no) {
    for (int i = 0; i < n; ++i) {
        if (accounts[i].acc_no == acc_no) return i;
    }
    return -1;
}

/* Authenticate by PIN with limited attempts */
int authenticate(Account *acc) {
    int pin, attempts = 0;
    while (attempts < MAX_PIN_ATTEMPTS) {
        printf("Enter PIN for account %d: ", acc->acc_no);
        if (scanf("%d", &pin) != 1) {
            while (getchar() != '\n');
            printf("Invalid input. Try again.\n");
            attempts++;
            continue;
        }
        if (pin == acc->pin) {
            printf("Welcome, %s!\n", acc->name);
            return 1;
        } else {
            attempts++;
            printf("Incorrect PIN. Attempts left: %d\n", MAX_PIN_ATTEMPTS - attempts);
        }
    }
    return 0;
}

void showMenu() {
    printf("\n--- ATM Menu ---\n");
    printf("1. Balance Inquiry\n");
    printf("2. Withdraw Cash\n");
    printf("3. Deposit Cash\n");
    printf("4. Mini Statement (last %d txns)\n", MAX_TXN);
    printf("5. Change PIN\n");
    printf("6. Logout\n");
}

/* Show balance */
void balanceInquiry(Account *acc) {
    printf("Account: %d | Name: %s\n", acc->acc_no, acc->name);
    printf("Available Balance: Rs %.2f\n", acc->balance);
}

/* Deposit money */
void deposit(Account *acc) {
    double amt;
    printf("Enter amount to deposit: Rs ");
    if (scanf("%lf", &amt) != 1 || amt <= 0) {
        while (getchar() != '\n');
        printf("Invalid amount.\n");
        return;
    }
    acc->balance += amt;
    recordTxn(acc, amt);
    printf("Rs %.2f deposited successfully. New balance: Rs %.2f\n", amt, acc->balance);
}

/* Withdraw money */
void withdrawAmt(Account *acc) {
    double amt;
    printf("Enter amount to withdraw: Rs ");
    if (scanf("%lf", &amt) != 1 || amt <= 0) {
        while (getchar() != '\n');
        printf("Invalid amount.\n");
        return;
    }
    if (amt > acc->balance) {
        printf("Insufficient funds. Available: Rs %.2f\n", acc->balance);
        return;
    }
    /* Optional: restrict to multiples of 100 */
    if (((int)amt) % 100 != 0) {
        printf("Please enter amount in multiples of 100.\n");
        return;
    }
    acc->balance -= amt;
    recordTxn(acc, -amt);
    printf("Please collect Rs %.2f. New balance: Rs %.2f\n", amt, acc->balance);
}

/* Record transaction in circular manner (last MAX_TXN) */
void recordTxn(Account *acc, double amount) {
    if (acc->txn_count < MAX_TXN) {
        acc->txns[acc->txn_count++] = amount;
    } else {
        /* shift left and append */
        for (int i = 1; i < MAX_TXN; ++i) acc->txns[i-1] = acc->txns[i];
        acc->txns[MAX_TXN-1] = amount;
    }
}

/* Print mini statement */
void miniStatement(Account *acc) {
    printf("--- Mini Statement for %s (Acc: %d) ---\n", acc->name, acc->acc_no);
    if (acc->txn_count == 0) {
        printf("No transactions yet.\n");
        return;
    }
    for (int i = 0; i < acc->txn_count; ++i) {
        double v = acc->txns[i];
        if (v >= 0)
            printf("%2d. Deposit   : +Rs %.2f\n", i+1, v);
        else
            printf("%2d. Withdrawal: -Rs %.2f\n", i+1, -v);
    }
    printf("Current Balance: Rs %.2f\n", acc->balance);
}

/* Change PIN with simple validation */
void changePin(Account *acc) {
    int oldpin, newpin, confirm;
    printf("Enter current PIN: ");
    if (scanf("%d", &oldpin) != 1) {
        while (getchar() != '\n');
        printf("Invalid input.\n");
        return;
    }
    if (oldpin != acc->pin) {
        printf("Incorrect current PIN.\n");
        return;
    }
    printf("Enter new 4-digit PIN: ");
    if (scanf("%d", &newpin) != 1) {
        while (getchar() != '\n');
        printf("Invalid input.\n");
        return;
    }
    printf("Confirm new PIN: ");
    if (scanf("%d", &confirm) != 1) {
        while (getchar() != '\n');
        printf("Invalid input.\n");
        return;
    }
    if (newpin != confirm) {
        printf("PIN mismatch. Try again later.\n");
        return;
    }
    if (newpin < 1000 || newpin > 9999) {
        printf("PIN must be a 4-digit number.\n");
        return;
    }
    acc->pin = newpin;
    printf("PIN changed successfully.\n");
}


