# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "backend.h"


struct Product
{
    int productId;
    char name[50];
    int quantity;
    float price;
};

// Function prototypes
void displayMenu();
void addRecord(FILE *file);
void viewRecord(FILE *file);
void searchRecord(FILE *file);
void updateRecord(FILE *file);
void deleteRecord(FILE *file);

int getValidIntForID()
{
    int value;
    while (1)
    {
        if (scanf("%d", &value) == 1)
        {
            // Valid integer entered
            break;
        }
        else
        {
            // Invalid input, clear input buffer
            while (getchar() != '\n')
                ;
            printf("Invalid input. Please enter an integer for the ID.\n");
        }
    }
    return value;
}

int getValidIntForQuantity()
{
    int value;
    while (1)
    {
        if (scanf("%d", &value) == 1)
        {
            // Valid integer entered
            break;
        }
        else
        {
            // Invalid input, clear input buffer
            while (getchar() != '\n')
                ;
            printf("Invalid input. Please enter an integer for the Quantity.\n");
        }
    }
    return value;
}

float getValidFloatForPrice()
{
    float value;
    while (1)
    {
        if (scanf("%f", &value) == 1)
        {
            // Valid integer entered
            break;
        }
        else
        {
            // Invalid input, clear input buffer
            while (getchar() != '\n')
                ;
            printf("Invalid input. Please enter an float for the Price.\n");
        }
    }
    return value;
}


void displayMenu()
{

    // Display the menu
    printf("\n===== Inventory Management System =====\n");
    printf("1. Add Record\n");
    printf("2. View Record\n");
    printf("3. Search Record\n");
    printf("4. Update Record\n");
    printf("5. Delete Record\n");
    printf("6. List files in a directory\n");
    printf("7. Create a new file\n");
    printf("8. Delete a file\n");
    printf("9. Search for files\n");
    printf("10. Exit\n");
}

void addRecord(FILE *file)
{
    struct Product newProduct;

    // Get input for the new product record
    printf("Enter Product ID: ");
    newProduct.productId = getValidIntForID();
    printf("Enter Product Name: ");
    scanf("%s", newProduct.name);
    printf("Enter Quantity: ");
    newProduct.quantity = getValidIntForQuantity();
    printf("Enter Price: ");
    newProduct.price = getValidFloatForPrice();

    // Write the new product record to the file
    fwrite(&newProduct, sizeof(struct Product), 1, file);

    printf("Record added successfully.\n");
}

void viewRecord(FILE *file)
{
    struct Product currentProduct;

    // Read and display all product records in the file
    rewind(file); // Move file pointer to the beginning

    while (fread(&currentProduct, sizeof(struct Product), 1, file) == 1)
    {
        printf("Product ID: %d\n", currentProduct.productId);
        printf("Product Name: %s\n", currentProduct.name);
        printf("Quantity: %d\n", currentProduct.quantity);
        printf("Price: %.2f\n", currentProduct.price);
        printf("-----------------------------\n");
    }
}

void searchRecord(FILE *file)
{
    int searchId;
    struct Product currentProduct;
    int found = 0;

    printf("Enter Product ID to search: ");
    scanf("%d", &searchId);

    // Search for the product with the given ID
    rewind(file);

    while (fread(&currentProduct, sizeof(struct Product), 1, file) == 1)
    {
        if (currentProduct.productId == searchId)
        {
            found = 1;
            printf("Product found:\n");
            printf("Product ID: %d\n", currentProduct.productId);
            printf("Product Name: %s\n", currentProduct.name);
            printf("Quantity: %d\n", currentProduct.quantity);
            printf("Price: %.2f\n", currentProduct.price);
            break; // Exit loop when the product is found
        }
    }

    if (!found)
    {
        printf("Product not found.\n");
    }
}

void updateRecord(FILE *file)
{
    int updateId;
    struct Product currentProduct;
    int found = 0;

    printf("Enter Product ID to update: ");
    scanf("%d", &updateId);

    // Search for the product with the given ID
    rewind(file);

    while (fread(&currentProduct, sizeof(struct Product), 1, file) == 1)
    {
        if (currentProduct.productId == updateId)
        {
            found = 1;
            printf("Enter new Product Name: ");
            scanf("%s", currentProduct.name);
            printf("Enter new Quantity: ");
            scanf("%d", &currentProduct.quantity);
            printf("Enter new Price: ");
            scanf("%f", &currentProduct.price);

            // Move the file pointer back by the size of a product record
            fseek(file, -sizeof(struct Product), SEEK_CUR);

            // Write the updated product record to the file
            fwrite(&currentProduct, sizeof(struct Product), 1, file);
            printf("Record updated successfully.\n");
            break; // Exit loop when the product is found and updated
        }
    }

    if (!found)
    {
        printf("Product not found.\n");
    }
}

void deleteRecord(FILE *file)
{
    int deleteId;
    struct Product currentProduct;
    FILE *tempFile;

    printf("Enter Product ID to delete: ");
    scanf("%d", &deleteId);

    // Create a temporary file for copying records excluding the one to be deleted
    tempFile = fopen("temp.dat", "wb");
    rewind(file);

    while (fread(&currentProduct, sizeof(struct Product), 1, file) == 1)
    {
        if (currentProduct.productId != deleteId)
        {
            fwrite(&currentProduct, sizeof(struct Product), 1, tempFile);
        }
    }

    fclose(tempFile);
    fclose(file);

    // Replace the original file with the temporary file
    remove("inventory.dat");
    rename("temp.dat", "inventory.dat");

    // Reopen the file for reading and writing
    file = fopen("inventory.dat", "rb+");
    printf("Record deleted successfully.\n");
}
