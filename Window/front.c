# include "front.h"



int main()
{
    FILE *file;
    int choice;

    file = fopen("inventory.dat", "rb+");

    if (file == NULL)
    {
        file = fopen("inventory.dat", "wb+");
    }

    do
    {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addRecord(file);
            break;
        case 2:
            viewRecord(file);
            break;
        case 3:
            searchRecord(file);
            break;
        case 4:
            updateRecord(file);
            break;
        case 5:
            deleteRecord(file);
            break;
        case 6:
        {
            list_files(directory);
            break;
        }
        case 7:
        {
            create_file(filename, content);
            break;
        }
        case 8:
        {   
            delete_file(filename);
            break;
        }
        case 9:
        {
            search_files(directory, criteria);
            break;
        }
        case 10:
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 10);

    fclose(file);

    return 0;
}

