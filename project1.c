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
    double txns[MAX_TXN]; 
    int txn_count;
    double monthly_expense; // NEW: total withdrawals for graph
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
void monthlyExpenseGraph(Account *acc);   // NEW FEATURE
void cashbackReward(Account *acc, double amt); // NEW FEATURE

int main() {
    Account accounts[MAX_ACCOUNTS];
    int n = 0;
    initAccounts(accounts, &n);

    int acc_no;
    printf("Welcome to ATM Simulator (C)\n");
    while (1) {
        printf("\nEnter account number (0 to exit): ");
        if (scanf("%d", &acc_no) != 1) {
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
            printf("Authentication failed.\n");
            continue;
        }

        int choice;
        do {
            showMenu();
            printf("Choose option: ");
            if (scanf("%d", &choice) != 1) {
                while (getchar() != '\n');
                printf("Invalid input.\n");
                choice = -1;
                continue;
            }

            switch(choice) {
                case 1: balanceInquiry(&accounts[idx]); break;
                case 2: withdrawAmt(&accounts[idx]); break;
                case 3: deposit(&accounts[idx]); break;
                case 4: miniStatement(&accounts[idx]); break;
                case 5: changePin(&accounts[idx]); break;
                case 6: monthlyExpenseGraph(&accounts[idx]); break; // NEW
                case 7: printf("Logging out...\n"); break;
                default: printf("Invalid option.\n");
            }
        } while (choice != 7);
    }

    return 0;
}

/* Initialize accounts */
void initAccounts(Account accounts[], int *n) {
    *n = 3;

    accounts[0].acc_no = 1001;
    strcpy(accounts[0].name, "Anwarul");
    accounts[0].pin = 1234;
    accounts[0].balance = 5000;
    accounts[0].txn_count = 0;
    accounts[0].monthly_expense = 0;

    accounts[1].acc_no = 1002;
    strcpy(accounts[1].name, "Deva");
    accounts[1].pin = 1111;
    accounts[1].balance = 15000;
    accounts[1].txn_count = 0;
    accounts[1].monthly_expense = 0;

    accounts[2].acc_no = 1003;
    strcpy(accounts[2].name, "Priyansu");
    accounts[2].pin = 2222;
    accounts[2].balance = 750;
    accounts[2].txn_count = 0;
    accounts[2].monthly_expense = 0;
}

int findAccountIndex(Account accounts[], int n, int acc_no) {
    for (int i = 0; i < n; ++i)
        if (accounts[i].acc_no == acc_no)
            return i;
    return -1;
}

int authenticate(Account *acc) {
    int pin, attempts = 0;
    while (attempts < MAX_PIN_ATTEMPTS) {
        printf("Enter PIN for account %d: ", acc->acc_no);
        if (scanf("%d", &pin) != 1) {
            while (getchar() != '\n');
            attempts++;
            continue;
        }
        if (pin == acc->pin) {
            printf("Welcome, %s!\n", acc->name);
            return 1;
        }
        attempts++;
        printf("Incorrect PIN. Attempts left: %d\n", MAX_PIN_ATTEMPTS - attempts);
    }
    return 0;
}

void showMenu() {
    printf("\n--- ATM Menu ---\n");
    printf("1. Balance Inquiry\n");
    printf("2. Withdraw Cash\n");
    printf("3. Deposit Cash\n");
    printf("4. Mini Statement\n");
    printf("5. Change PIN\n");
    printf("6. Monthly Expense Graph\n"); // NEW
    printf("7. Logout\n");
}

void balanceInquiry(Account *acc) {
    printf("Account: %d | %s\n", acc->acc_no, acc->name);
    printf("Balance: Rs %.2f\n", acc->balance);
}

void deposit(Account *acc) {
    double amt;
    printf("Enter amount to deposit: ");
    if (scanf("%lf", &amt) != 1 || amt <= 0) {
        while (getchar() != '\n');
        printf("Invalid amount.\n");
        return;
    }

    acc->balance += amt;
    recordTxn(acc, amt);

    cashbackReward(acc, amt); // NEW FEATURE

    printf("Deposited Rs %.2f\n", amt);
    printf("New Balance: Rs %.2f\n", acc->balance);
}

void withdrawAmt(Account *acc) {
    double amt;
    printf("Enter amount to withdraw: ");
    if (scanf("%lf", &amt) != 1 || amt <= 0) {
        while (getchar() != '\n');
        printf("Invalid amount.\n");
        return;
    }

    if (amt > acc->balance) {
        printf("Insufficient funds.\n");
        return;
    }

    if (((int)amt) % 100 != 0) {
        printf("Enter amount in multiples of 100.\n");
        return;
    }

    acc->balance -= amt;
    acc->monthly_expense += amt; // Track withdrawals
    recordTxn(acc, -amt);

    printf("Withdrawn Rs %.2f\n", amt);
    printf("New Balance: Rs %.2f\n", acc->balance);
}

void recordTxn(Account *acc, double amount) {
    if (acc->txn_count < MAX_TXN)
        acc->txns[acc->txn_count++] = amount;
    else {
        for (int i = 1; i < MAX_TXN; i++)
            acc->txns[i-1] = acc->txns[i];
        acc->txns[MAX_TXN - 1] = amount;
    }
}

void miniStatement(Account *acc) {
    printf("\n--- Mini Statement ---\n");
    if (acc->txn_count == 0) {
        printf("No transactions.\n");
        return;
    }
    for (int i = 0; i < acc->txn_count; i++) {
        if (acc->txns[i] >= 0)
            printf("%d. Deposit: +Rs %.2f\n", i+1, acc->txns[i]);
        else
            printf("%d. Withdrawal: -Rs %.2f\n", i+1, -acc->txns[i]);
    }
}

/* ---------------- NEW FEATURE: CASHBACK ---------------- */
void cashbackReward(Account *acc, double amt) {
    if (amt >= 1000) {
        double cb = amt * 0.01;  // 1% cashback
        acc->balance += cb;
        recordTxn(acc, cb);

        printf("\n🎁 Cashback Earned: Rs %.2f\n", cb);
    }
}

/* ---------------- NEW FEATURE: GRAPH ---------------- */
void monthlyExpenseGraph(Account *acc) {
    printf("\n--- Monthly Expense Graph (Withdrawals) ---\n");

    int bars = acc->monthly_expense / 100; // 1 bar = ₹100

    printf("Total Expense: Rs %.2f\n", acc->monthly_expense);
    printf("Graph:\n");

    for (int i = 0; i < bars; i++)
        printf("|");

    printf("\nEach '|' = Rs 100 spent\n");
}

/* Change PIN */
void changePin(Account *acc) {
    int oldpin, newpin, confirm;
    printf("Enter current PIN: ");
    scanf("%d", &oldpin);

    if (oldpin != acc->pin) {
        printf("Incorrect PIN.\n");
        return;
    }

    printf("Enter new 4-digit PIN: ");
    scanf("%d", &newpin);

    printf("Confirm PIN: ");
    scanf("%d", &confirm);

    if (newpin != confirm || newpin < 1000 || newpin > 9999) {
        printf("PIN mismatch or invalid.\n");
        return;
    }

    acc->pin = newpin;
    printf("PIN changed successfully!\n");
}
