#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the Account structure to hold account details
typedef struct {
    int accNo;          // Account number (unique identifier)
    char name[50];      // Account holder's name
    char pin[5];        // PIN (4 digits + null terminator)
    float balance;      // Account balance
    char contact[20];   // Contact information (e.g., phone number)
} Account;

// Global variables
#define MAX_ACCOUNTS 100  // Maximum number of accounts (fixed for simplicity)
Account accounts[MAX_ACCOUNTS];  // Array to hold accounts in memory
int accountCount = 0;            // Current number of accounts loaded
char adminUsername[20] = "admin";  // Fixed admin username
char adminPin[5] = "1234";         // Fixed admin PIN

// Function prototypes
void loadAccounts();              // Load accounts from binary file
void saveAccounts();              // Save accounts to binary file
void copyBinaryToText();         // Copy binary accounts.dat to text file for verification
void mainMenu();                  // Display and handle main menu
void adminLogin();                // Handle admin login
void adminMenu();                 // Display and handle admin menu
void createAccount();             // Create a new account
void viewAllAccounts();           // View all accounts
void searchAccount();             // Search for an account by ID
void deleteAccount();             // Delete an account
void transactionHistory();        // View transaction history from CSV
void customerLogin();             // Handle customer login
void customerMenu(int index);     // Display and handle customer menu for a specific account
void checkBalance(int index);     // Check balance for an account
void depositMoney(int index);     // Deposit money into an account
void withdrawMoney(int index);    // Withdraw money from an account
void fundTransfer(int index);     // Transfer funds between accounts
void changePin(int index);        // Change PIN for an account
void miniStatement(int index);    // Show mini statement for an account
void appendTransaction(int accNo, char* operation, float amount, int toAcc);  // Append to transactions.csv


// Main function: Entry point of the program
int main() {
    loadAccounts();  // Load existing accounts from file at startup
    mainMenu();      // Start the main menu loop
    saveAccounts();  // Save accounts to file before exiting
    return 0;
}

// Load accounts from binary file (accounts.dat)
// If file doesn't exist, it will be created later when saving
void loadAccounts() {
    FILE* file = fopen("accounts.dat", "rb");  // Open file in read binary mode 
    if (file == NULL) {
        printf("No existing accounts file found. Starting fresh.\n");
        return;  // If file doesn't exist, do nothing (accountCount remains 0)
    }
    accountCount = 0;  // Reset count
    while (fread(&accounts[accountCount], sizeof(Account), 1, file) == 1 && accountCount < MAX_ACCOUNTS) {
        accountCount++;  // Read each account struct and increment count
    }
    fclose(file);  // Close the file
    printf("Loaded %d accounts from file.\n", accountCount);
}

// Save accounts to binary file (accounts.dat)
// Overwrites the file with current accounts array
void saveAccounts() {
    FILE* file = fopen("accounts.dat", "wb");  // Open file in write binary mode
    if (file == NULL) {
        printf("Error: Could not open accounts.dat for writing.\n");
        return;
    }
    for (int i = 0; i < accountCount; i++) {
        fwrite(&accounts[i], sizeof(Account), 1, file);  // Write each account struct to file
    }
    fclose(file);  // Close the file
    printf("Accounts saved to file.\n");
}

void copyBinaryToText() {
    FILE *binFile = fopen("accounts.dat", "rb");
    FILE *txtFile = fopen("accounts_copy.txt", "w");
    if (binFile == NULL || txtFile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    Account acc; //Making vairable of data type Account to read 1 complete record struct
    while (fread(&acc, sizeof(Account), 1, binFile) == 1) {
        fprintf(txtFile, "AccNo: %d, Name: %s, PIN: %s, Balance: %.2f, Contact: %s\n",
                acc.accNo, acc.name, acc.pin, acc.balance, acc.contact);
    }

    fclose(binFile);
    fclose(txtFile);
    printf("Binary file copied to text file successfully.\n");
}


// Main menu: Displays options and handles user choice
void mainMenu() {
	int i;

/* LETTER DEFINITIONS */

char W[7][11] =
{
    "**      **",
    "**      **",
    "**      **",
    "**      **",
    "**  **  **",
    "**  **  **",
    "**********"
};

char E[7][9] =
{
    "********",
    "**",
    "**",
    "*******",
    "**",
    "**",
    "********"
};

char L[7][9] =
{
    "**",
    "**",
    "**",
    "**",
    "**",
    "**",
    "********"
};

char C[7][8] =
{
    "*******",
    "**",
    "**",
    "**",
    "**",
    "**",
    "*******"
};

char O[7][8] =
{
    "*******",
    "**   **",
    "**   **",
    "**   **",
    "**   **",
    "**   **",
    "*******"
};

char M[7][8] =
{
    "**   **",
    "*** ***",
    "*******",
    "** * **",
    "**   **",
    "**   **",
    "**   **"
};

char T[7][8] =
{
    "*******",
    "  **",
    "  **",
    "  **",
    "  **",
    "  **",
    "  **"
};

char V[7][9] =
{
    "**    **",
    "**    **",
    "**    **",
    "**    **",
    " **  **",
    " **  **",
    "  ****"
};

char A[7][9] =
{
    "  ****",
    " **  **",
    "**    **",
    "**    **",
    "********",
    "**    **",
    "**    **"
};

char U[7][9] =
{
    "**    **",
    "**    **",
    "**    **",
    "**    **",
    "**    **",
    "**    **",
    " ******"
};

char S[7][9] =
{
    " ******",
    "**",
    "**",
    " ******",
    "      **",
    "      **",
    " ******"
};

char Y[7][9] =
{
    "**    **",
    " **  **",
    "  ****",
    "   **",
    "   **",
    "   **",
    "   **"
};

/* PRINTING */

for (i = 0; i < 7; i++)
{
    /* WELCOME */
    printf("%-11s %-10s %-9s %-9s %-9s %-9s %-9s   ",
           W[i], E[i], L[i], C[i], O[i], M[i], E[i]);

    printf("    ");

    /* TO */
    printf("%-8s %-9s   ", T[i], O[i]);

    printf("    ");

    /* VAULTSYS */
    printf("%-9s %-9s %-9s %-9s %-8s %-8s %-8s %-8s",
           V[i], A[i], U[i], L[i], T[i], S[i], Y[i], S[i]);

    printf("\n");
}
    
    int choice;
    while (1) {  // Infinite loop until exit
        printf("\n=== VAULTSYS Banking Terminal ===\n");
        printf("1. Admin Login\n");
        printf("2. Customer Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                adminLogin();  // Call admin login function
                break;
            case 2:
                customerLogin();  // Call customer login function
                break;
            case 3:
                printf("Exiting program.\n");
                return;  // Exit the loop and function
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

// Admin login: Prompts for username and PIN, then proceeds to admin menu if correct
void adminLogin() {
    char username[20], pin[5];
    printf("Enter admin username: ");
    scanf("%s", username);
    printf("Enter admin PIN: ");
    scanf("%s", pin);
    if (strcmp(username, adminUsername) == 0 && strcmp(pin, adminPin) == 0) {  // Check if credentials match
        printf("Admin login successful.\n");
        adminMenu();  // Proceed to admin menu
    } else {
        printf("Invalid credentials.\n");
    }
}

// Admin menu: Displays admin options and handles user choice
void adminMenu() {
    int choice;
    while (1) {
        printf("\n=== Admin Menu ===\n");
        printf("1. Create New Account\n");
        printf("2. View All Accounts\n");
        printf("3. Search Account\n");
        printf("4. Delete Account\n");
        printf("5. Transaction History\n");
        printf("6. Copy Accounts to Text File\n");  
        printf("7. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                createAccount();  // Call create account function
                break;
            case 2:
                viewAllAccounts();  // Call view all accounts function
                break;
            case 3:
                searchAccount();  // Call search account function
                break;
            case 4:
                deleteAccount();  // Call delete account function
                break;
            case 5:
                transactionHistory();  // Call transaction history function
                break;
            case 6:
                copyBinaryToText();  // Call new function to copy binary to text
                break;
            case 7:
                return;  // Go back to main menu
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}


// Create a new account: Prompts for details, assigns auto-incremented account number, saves to array and file
void createAccount() {
    if (accountCount >= MAX_ACCOUNTS) {
        printf("Maximum accounts reached.\n");
        return;
    }
    Account newAcc;
    newAcc.accNo = (accountCount == 0) ? 101 : accounts[accountCount - 1].accNo + 1;  // Auto-assign account number
    printf("Enter name: ");
    scanf(" %[^\n]", newAcc.name);  // Read full line for name
    // PIN input with 4-digit restriction
    while (1) {
        printf("Enter PIN (4 digits): ");
        scanf("%s", newAcc.pin);
        // Check length of PIN
        if (strlen(newAcc.pin) == 4) {
            break;  // valid PIN, exit loop
        } else {
            printf("Invalid PIN! PIN must be exactly 4 digits. Try again.\n");
        }
    }
    newAcc.balance = 0.0;  // Initial balance
    printf("Enter contact info: ");
    scanf(" %[^\n]", newAcc.contact);
    accounts[accountCount++] = newAcc;  // Add to array and increment count
    saveAccounts();  // Auto-save to file
    printf("Account created successfully. Account Number: %d\n", newAcc.accNo);
}

// View all accounts: Displays all accounts from the array
void viewAllAccounts() {
    if (accountCount == 0) {
        printf("No accounts found.\n");
        return;
    }
    printf("\nAll Accounts:\n");
    for (int i = 0; i < accountCount; i++) {
        printf("Acc No: %d, Name: %s, Balance: %.2f\n", accounts[i].accNo, accounts[i].name, accounts[i].balance);
    }
}


void searchAccount() {
    if (accountCount <= 0) {
        printf("No accounts available to search.\n");
        return; 
    }

    int accNo;
    printf("Enter account number to search: ");
    if (scanf("%d", &accNo) != 1) {  
        printf("Invalid input. Please enter numbers only.\n");
        while(getchar() != '\n'); 
        return;
    }

    if (accNo <= 0) {  
        printf("Account number must be positive.\n");
        return;
    }

 
    int found = 0;
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accNo == accNo) {
            printf("Account found:\n");
            printf("Acc No: %d\nName: %s\nBalance: %.2f\nContact: %s\n",
                   accounts[i].accNo, accounts[i].name, accounts[i].balance, accounts[i].contact);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Account not found.\n");
    }
}


void deleteAccount() {
    int accNo;

    // User input with validation
    do {
        printf("Enter account number to delete (positive number): ");
        scanf("%d", &accNo);
        if (accNo <= 0) {
            printf("Invalid account number. Try again.\n");
        }
    } while (accNo <= 0);

    // Search for account
    int found = 0;  // Flag to check if account exists
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accNo == accNo) {
            // Shift elements left to remove account
            for (int j = i; j < accountCount - 1; j++) {
                accounts[j] = accounts[j + 1];
            }
            accountCount--;        // Update total accounts
            saveAccounts();        // Save changes to file
            printf("Account deleted successfully.\n");
            found = 1;
            break;                // Stop loop after deleting
        }
    }

    if (!found) {
        printf("Account not found.\n");
    }
}


// Transaction history: Reads and displays all lines from transactions.csv
void transactionHistory() {
    FILE* file = fopen("transactions.csv", "r");  // Open in read mode
    if (file == NULL) {
        printf("No transaction history found.\n");
        return;
    }
    char line[256];
    printf("\nTransaction History:\n");
    while (fgets(line, sizeof(line), file)) {  // Read each line
        printf("%s", line);  // Print the line
    }
    fclose(file);  // Close the file
}

// Customer login: Prompts for account number and PIN, then proceeds to customer menu if valid
void customerLogin() {
    int accNo;
    char pin[5];
    printf("Enter account number: ");
    scanf("%d", &accNo);
    printf("Enter PIN: ");
    scanf("%s", pin);
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accNo == accNo && strcmp(accounts[i].pin, pin) == 0) {  // Check credentials
            printf("Login successful.\n");
            customerMenu(i);  // Proceed to customer menu with account index
            return;
        }
    }
    printf("Invalid account number or PIN.\n");
}

// Customer menu: Displays customer options and handles user choice for the logged-in account
void customerMenu(int index) {
    int choice;
    while (1) {
        printf("\n=== Customer Menu ===\n");
        printf("1. Check Balance\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Fund Transfer\n");
        printf("5. Change PIN\n");
        printf("6. Mini Statement\n");
        printf("7. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                checkBalance(index);  // Call check balance function
                break;
            case 2:
                depositMoney(index);  // Call deposit function
                break;
            case 3:
                withdrawMoney(index);  // Call withdraw function
                break;
            case 4:
                fundTransfer(index);  // Call transfer function
                break;
            case 5:
                changePin(index);  // Call change PIN function
                break;
            case 6:
                miniStatement(index);  // Call mini statement function
                break;
            case 7:
                return;  // Logout to main menu
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

// Check balance: Displays the balance for the account
void checkBalance(int index) {
    printf("Your current balance: %.2f\n", accounts[index].balance);
}

// Deposit money: Prompts for amount, updates balance, appends to CSV, generates receipt, saves accounts
void depositMoney(int index) {
    float amount;
    printf("Enter amount to deposit: ");
    scanf("%f", &amount);
    if (amount <= 0) {
        printf("Invalid amount.\n");
        return;
    }
    accounts[index].balance += amount;  // Update balance
    appendTransaction(accounts[index].accNo, "Deposit", amount, -1);  // Append to CSV (no toAcc)
    saveAccounts();  // Save changes
    printf("Deposit successful. New balance: %.2f\n", accounts[index].balance);
}

// Withdraw money: Prompts for amount, checks balance, updates if sufficient, appends to CSV, generates receipt, saves
void withdrawMoney(int index) {
    float amount;
    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);
    if (amount <= 0 || amount > accounts[index].balance) {
        printf("Invalid amount or insufficient balance.\n");
        return;
    }
    accounts[index].balance -= amount;  // Update balance
    appendTransaction(accounts[index].accNo, "Withdraw", amount, -1);  // Append to CSV
    saveAccounts();  // Save changes
    printf("Withdrawal successful. New balance: %.2f\n", accounts[index].balance);
}

// Fund transfer: Prompts for target account and amount, checks validity, updates both accounts, appends to CSV, generates receipts, saves
void fundTransfer(int index) {
    int toAccNo;
    float amount;
    printf("Enter target account number: ");
    scanf("%d", &toAccNo);
    printf("Enter amount to transfer: ");
    scanf("%f", &amount);

    if(toAccNo == accounts[index].accNo){
        printf("Invalid target account number you cant send money to yourself.\n");
        return;
    }
    if (amount <= 0 || amount > accounts[index].balance) {
        printf("Invalid amount or insufficient balance.\n");
        return;
    }
    int toIndex = -1;
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accNo == toAccNo) {
            toIndex = i;  // Find target account index
            break;
        }
    }
    if (toIndex == -1) {
        printf("Target account not found.\n");
        return;
    }
    accounts[index].balance -= amount;  // Deduct from sender
    accounts[toIndex].balance += amount;  // Add to receiver
    appendTransaction(accounts[index].accNo, "Transfer", amount, toAccNo);  // Append to CSV
    saveAccounts();  // Save changes
    printf("Transfer successful. New balance: %.2f\n", accounts[index].balance);
}

// Change PIN: Prompts for new PIN and updates it, saves accounts
void changePin(int index) {
    char newPin[5];
    printf("Enter new PIN (4 digits): ");
    scanf("%s", newPin);
    strcpy(accounts[index].pin, newPin);  // Update PIN
    saveAccounts();  // Save changes
    printf("PIN changed successfully.\n");
}

// Mini statement: Reads transactions.csv and displays last 5 transactions for the account
void miniStatement(int index) {
    FILE* file = fopen("transactions.csv", "r");  // Open in read mode
    if (file == NULL) {
        printf("No transactions found.\n");
        return;
    }
    char lines[100][256];  // Array to hold lines (assuming not too many)
    int lineCount = 0;
    char line[256];
    while (fgets(line, sizeof(line), file) && lineCount < 100) {  // Read lines
        strcpy(lines[lineCount++], line);
    }
    fclose(file);
    printf("\nMini Statement (Last 5 Transactions):\n");
    int start = (lineCount > 5) ? lineCount - 5 : 0;  // Start from last 5
    for (int i = start; i < lineCount; i++) {
        int acc;
        sscanf(lines[i], "%d,", &acc);  // Parse account number from line
        if (acc == accounts[index].accNo) {  // If matches current account
            printf("%s", lines[i]);
        }
    }
}

// Append transaction to transactions.csv: Opens in append mode and writes a line
void appendTransaction(int accNo, char* operation, float amount, int toAcc) {
    FILE* file = fopen("transactions.csv", "a");  // Open in append mode
    if (file == NULL) {
        printf("Error opening transactions.csv\n");
        return;
    }
    if (toAcc == -1) {
        fprintf(file, "%d,%s,%.2f\n", accNo, operation, amount);  // Write line without toAcc
    } else {
        fprintf(file, "%d,%s,%.2f,%d\n", accNo, operation, amount, toAcc);  // Write line with toAcc
    }
    fclose(file);  // Close the file
}

