#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1. Structure
struct Book {
    int id;
    char title[50];
    char author[50];
};

// 2. Add Book
void addBook() {
    struct Book b;
    FILE *fp = fopen("books.dat", "ab");
    
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\n--- ADD A NEW BOOK ---\n");
    printf("Enter Book ID (e.g., 101): ");
    scanf("%d", &b.id);
    
    printf("Enter Book Title: ");
    scanf(" %[^\n]s", b.title);
    
    printf("Enter Author Name: ");
    scanf(" %[^\n]s", b.author);

    fwrite(&b, sizeof(struct Book), 1, fp);
    fclose(fp);
    printf(" Book Added Successfully!\n");
}

// 3. View All Books
void viewBooks() {
    struct Book b;
    FILE *fp = fopen("books.dat", "rb");
    
    if (fp == NULL) {
        printf("\n No books found! Please add some books first.\n");
        return;
    }

    printf("\n--- LIST OF ALL BOOKS ---\n");
    printf("%-10s %-30s %-20s\n", "BOOK ID", "TITLE", "AUTHOR");
    printf("------------------------------------------------------------\n");
    
    while (fread(&b, sizeof(struct Book), 1, fp) == 1) {
        printf("%-10d %-30s %-20s\n", b.id, b.title, b.author);
    }
    fclose(fp);
}

// 4. Search Book 
void searchBook() {
    struct Book b;
    int searchId, found = 0;
    FILE *fp = fopen("books.dat", "rb");

    if (fp == NULL) {
        printf("\n No records found!\n");
        return;
    }

    printf("\n--- SEARCH BOOK ---\n");
    printf("Enter Book ID to search: ");
    scanf("%d", &searchId);

    while (fread(&b, sizeof(struct Book), 1, fp) == 1) {
        if (b.id == searchId) {
            printf("\n Book Found!\n");
            printf("ID: %d\nTitle: %s\nAuthor: %s\n", b.id, b.title, b.author);
            found = 1;
            break;
        }
    }

    if (found == 0) {
        printf("\n? Book with ID %d not found.\n", searchId);
    }
    fclose(fp);
}

// 5. Delete Book 
void deleteBook() {
    struct Book b;
    int deleteId, found = 0;
    FILE *fp = fopen("books.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb"); 

    if (fp == NULL) {
        printf("\n No records found to delete!\n");
        return;
    }

    printf("\n--- DELETE BOOK ---\n");
    printf("Enter Book ID to delete: ");
    scanf("%d", &deleteId);

    // write in temp file
    while (fread(&b, sizeof(struct Book), 1, fp) == 1) {
        if (b.id == deleteId) {
            found = 1; 
        } else {
            fwrite(&b, sizeof(struct Book), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    // remove old file
    remove("books.dat");
    rename("temp.dat", "books.dat");

    if (found == 1) {
        printf("\n Book successfully deleted!\n");
    } else {
        printf("\n Book with ID %d not found.\n", deleteId);
    }
}

// 6. Main Menu
int main() {
    int choice;
    
    while(1) {
        printf("\n==================================\n");
        printf("    LIBRARY MANAGEMENT SYSTEM       ");
        printf("\n==================================\n");
        printf("1. Add a Book\n");
        printf("2. View All Books\n");
        printf("3. Search a Book\n");
        printf("4. Delete a Book\n");
        printf("5. Exit Program\n");
        printf("----------------------------------\n");
        printf("Enter your choice (1-5): ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addBook(); break;
            case 2: viewBooks(); break;
            case 3: searchBook(); break;
            case 4: deleteBook(); break;
            case 5: printf("\nExiting the system. Goodbye! \n"); exit(0);
            default: printf("\n Invalid choice! Please enter a number between 1 and 5.\n");
        }
    }
    return 0;
}
