#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for a Transaction
typedef struct Transaction {
    int id;
    char sender[50];
    char receiver[50];
    float amount;
    struct Transaction* next;
} Transaction;

// Head pointer for the linked list
Transaction* head = NULL;

// Function to create a new transaction node
Transaction* createTransaction(int id, char sender[], char receiver[], float amount) {
    Transaction* newTx = (Transaction*)malloc(sizeof(Transaction));
    newTx->id = id;
    strcpy(newTx->sender, sender);
    strcpy(newTx->receiver, receiver);
    newTx->amount = amount;
    newTx->next = NULL;
    return newTx;
}

// Add a new transaction at the end of the list
void addTransaction(int id, char sender[], char receiver[], float amount) {
    Transaction* newTx = createTransaction(id, sender, receiver, amount);
    if (head == NULL) {
        head = newTx;
        return;
    }
    Transaction* temp = head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = newTx;
}

// Display all transactions
void displayTransactions() {
    Transaction* temp = head;
    if (temp == NULL) {
        printf("No transactions found.\\n");
        return;
    }
    printf("\\n--- Transaction History ---\\n");
    while (temp != NULL) {
        printf("ID: %d\\nSender: %s\\nReceiver: %s\\nAmount: %.2f\\n\\n",
               temp->id, temp->sender, temp->receiver, temp->amount);
        temp = temp->next;
    }
}

// Search transaction by ID
void searchTransaction(int id) {
    Transaction* temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            printf("\\nTransaction Found!\\n");
            printf("ID: %d\\nSender: %s\\nReceiver: %s\\nAmount: %.2f\\n",
                   temp->id, temp->sender, temp->receiver, temp->amount);
            return;
        }
        temp = temp->next;
    }
    printf("Transaction with ID %d not found.\\n", id);
}

// Delete transaction by ID
void deleteTransaction(int id) {
    Transaction* temp = head;
    Transaction* prev = NULL;

    if (temp != NULL && temp->id == id) {
        head = temp->next;
        free(temp);
        printf("Transaction %d deleted successfully.\\n", id);
        return;
    }

    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Transaction not found.\\n");
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf("Transaction %d deleted successfully.\\n", id);
}

// Main function
int main() {
    int choice, id;
    char sender[50], receiver[50];
    float amount;

    while (1) {
        printf("\\n=== Crypto Wallet Transaction Tracker ===\\n");
        printf("1. Add Transaction\\n");
        printf("2. Display All Transactions\\n");
        printf("3. Search Transaction\\n");
        printf("4. Delete Transaction\\n");
        printf("5. Exit\\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Transaction ID: ");
                scanf("%d", &id);
                printf("Enter Sender Name: ");
                scanf("%s", sender);
                printf("Enter Receiver Name: ");
                scanf("%s", receiver);
                printf("Enter Amount: ");
                scanf("%f", &amount);
                addTransaction(id, sender, receiver, amount);
                break;

            case 2:
                displayTransactions();
                break;

            case 3:
                printf("Enter Transaction ID to Search: ");
                scanf("%d", &id);
                searchTransaction(id);
                break;

            case 4:
                printf("Enter Transaction ID to Delete: ");
                scanf("%d", &id);
                deleteTransaction(id);
                break;

            case 5:
                printf("Exiting...\\n");
                exit(0);

            default:
                printf("Invalid choice! Try again.\\n");
        }
    }

    return 0;
}
