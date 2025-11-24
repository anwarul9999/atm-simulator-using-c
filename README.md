# atm-simulator-using-c

# ATM Management System in C

A simple, menu-driven **ATM Simulation Project** built using **pure C
language**.\
This program runs in the terminal and simulates real ATM operations like
balance inquiry, withdrawals, deposits, money transfer, mini-statement,
and PIN change --- all in an interactive and user-friendly format.

------------------------------------------------------------------------

## 🚀 Features

### 🔐 **User Authentication**

-   Secure login using a 4-digit PIN\
-   Maximum **3 attempts** to prevent unauthorized access\
-   Multi-account support

### 🏦 **ATM Operations**

-   ✔ Balance Inquiry\
-   ✔ Cash Withdrawal (multiple of ₹100)\
-   ✔ Cash Deposit\
-   ✔ Mini Statement (last 10 transactions)\
-   ✔ Change ATM PIN\
-   ✔ Logout

### 🆕 **Newly Added Features**

-   ✔ **Money Transfer** between accounts\
-   ✔ **View Account Profile** (Account No., Name, Balance, Total
    Transactions)\
-   ✔ **Close Account** (Soft delete option)\
-   ✔ **Transaction History Storage**\
-   ✔ **Dynamic Balance Update**

------------------------------------------------------------------------

## 📌 Preloaded Sample Accounts

You can define initial accounts inside `initAccounts()`:

  Account No.   Name       PIN    Balance
  ------------- ---------- ------ ---------
  1001          Anwarul    1234   50,000
  1002          Deva       1111   40,000
  1003          Priyansu   2222   35,000

------------------------------------------------------------------------

## 🖼️ Screenshots

### 📌 ATM Login Screen

![Screenshot](https://raw.githubusercontent.com/anwarul9999/atm-simulator-using-c/72a2417831e02544de9e60e33c25c696bf538227/Screenshot%202025-11-24%20151255.png)

------------------------------------------------------------------------

### 📌 Account Selection / Menu

![Screenshot](https://raw.githubusercontent.com/anwarul9999/atm-simulator-using-c/72a2417831e02544de9e60e33c25c696bf538227/Screenshot%202025-11-24%20151350.png)

------------------------------------------------------------------------

### 📌 Balance Inquiry

![Screenshot](https://raw.githubusercontent.com/anwarul9999/atm-simulator-using-c/72a2417831e02544de9e60e33c25c696bf538227/Screenshot%202025-11-24%20151451.png)

------------------------------------------------------------------------

### 📌 Withdrawal Screen

![Screenshot](https://raw.githubusercontent.com/anwarul9999/atm-simulator-using-c/72a2417831e02544de9e60e33c25c696bf538227/Screenshot%202025-11-24%20151503.png)

------------------------------------------------------------------------

### 📌 Mini Statement

![Screenshot](https://raw.githubusercontent.com/anwarul9999/atm-simulator-using-c/72a2417831e02544de9e60e33c25c696bf538227/Screenshot%202025-11-24%20151513.png)

------------------------------------------------------------------------

### 📌 Change PIN

![Screenshot](https://raw.githubusercontent.com/anwarul9999/atm-simulator-using-c/72a2417831e02544de9e60e33c25c696bf538227/Screenshot%202025-11-24%20151526.png)

------------------------------------------------------------------------

## 📂 Project Structure

    atm-simulator-using-c/
    │
    ├── atm.c               # Main program file
    ├── accounts.h          # Header file for account structure & functions
    ├── transactions.h      # Header file for transaction handling
    ├── README.md           # Project documentation
    └── screenshots/        # Project screenshots (optional folder)

------------------------------------------------------------------------

## 🛠️ Technologies Used

-   **C Language** (Core implementation)
-   **Standard Library (stdio.h, string.h, stdlib.h)**
-   **Console-based UI**

------------------------------------------------------------------------

## 📥 Installation & Run Instructions

### **1. Clone this repository**

    git clone https://github.com/anwarul9999/atm-simulator-using-c.git

### **2. Navigate into the folder**

    cd atm-simulator-using-c

### **3. Compile the program**

    gcc atm.c -o atm

### **4. Run the program**

    ./atm

------------------------------------------------------------------------

## 🔮 Future Improvements

-   File handling for saving accounts permanently\
-   Admin control panel\
-   GUI version\
-   Export mini-statement to text file\
-   Add card number system

------------------------------------------------------------------------

## 🧑‍💻 Author

**Anwarul Haque**\
B.Tech CSE -- Centurion University\
GitHub: https://github.com/anwarul9999

------------------------------------------------------------------------
