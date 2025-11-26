ATM Simulator in C

This project is a simple ATM Simulation System written in the C programming language.
It supports multiple user accounts and includes essential ATM functionalities along with two special features: Monthly Expense Graph and Cashback Rewards.

⭐ Features Included
🔹 1. Balance Inquiry

Displays the current available balance of the user's account.

🔹 2. Cash Withdrawal

Allows users to withdraw money:

Must be in multiples of 100

Checks for insufficient balance

Tracks monthly expenses

🔹 3. Cash Deposit

Users can deposit money into their account.
Also includes:

🎁 Cashback Reward (New Feature)

If the deposit amount ≥ ₹1000, the user receives 1% cashback.

Cashback is automatically added and stored as a transaction.

🔹 4. Mini Statement

Shows the last 10 transactions (deposit, withdrawal, cashback).

🔹 5. Change ATM PIN

Securely update the ATM PIN with confirmation and validation.

🔹 6. Monthly Expense Graph (New Feature)

Visual bar-graph based on total withdrawal amount for the month:

Every '|' bar = ₹100 spent

Helps user track spending visually.

🔹 7. Logout

Ends the session and returns to account selection.

📌 Data Stored Per Account

Each account stores:

Account Number

User Name

PIN

Balance

Last 10 Transactions

Monthly Expense

Cashback Rewards

🗂 Project Structure
ATM-Simulator (C)
│
├── main.c
└── README.md

🏗 How It Works
🔑 1. Account Login

User enters:

Account Number

PIN (Up to 3 attempts allowed)

🧾 2. ATM Menu Options

After login, user can select from:

1. Balance Inquiry
2. Withdraw
3. Deposit
4. Mini Statement
5. Change PIN
6. Monthly Expense Graph
7. Logout

🔄 3. Transaction Recording

All transactions (deposit, withdrawal, cashback) are saved in a circular array of size 10.

📊 Monthly Expense Graph Example

If total withdrawal is ₹650:

|||||||
Each '|' = Rs 100 spent

🎁 Cashback Logic
If Deposit Amount >= 1000:
    Cashback = 1% of deposit
    Cashback added to account balance


Example:

Deposit = ₹2000

Cashback = ₹20

🚀 How to Compile & Run
Compile:
gcc atm.c -o atm

Run:
./atm

👤 Sample Accounts
Account No	Name	PIN	Balance
1001	Anwarul	1234	5000
1002	Deva	1111	15000
1003	Priyansu	2222	750
