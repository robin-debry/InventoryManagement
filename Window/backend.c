#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <file_operations.h>

// Function to list files in a directory
void list_files(const char *directory) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(directory);

    if (dir != NULL) {
        while ((entry = readdir(dir)) != NULL) {
            printf("%s\n", entry->d_name);
        }
        closedir(dir);
    } else {
        perror("Error opening directory");
    }
}

// Function to create a new file
void create_file(const char *filename, const char *content) {
    FILE *file = fopen(filename, "w");
    
    if (file != NULL) {
        fprintf(file, "%s", content);
        fclose(file);
        printf("File '%s' created successfully.\n", filename);
    } else {
        perror("Error creating file");
    }
}

// Function to delete a file
void delete_file(const char *filename) {
    if (remove(filename) == 0) {
        printf("File '%s' deleted successfully.\n", filename);
    } else {
        perror("Error deleting file");
    }
}

// Function to search for files based on criteria
void search_files(const char *directory, const char *criteria) {
    char search_pattern[256];
    snprintf(search_pattern, sizeof(search_pattern), "%s/%s", directory, criteria);

    glob_t glob_result;
    if (glob(search_pattern, 0, NULL, &glob_result) == 0) {
        for (size_t i = 0; i < glob_result.gl_pathc; i++) {
            printf("%s\n", glob_result.gl_pathv[i]);
        }
        globfree(&glob_result);
    } else {
        printf("No files found matching the criteria '%s'.\n", criteria);
    }
}

int main() {
    while (1) {
        printf("\nFile Operations:\n");
        printf("1. List files in a directory\n");
        printf("2. Create a new file\n");
        printf("3. Delete a file\n");
        printf("4. Search for files based on criteria\n");
        printf("5. Exit\n");

        printf("Enter your choice (1-5): ");
        char choice[10];
        fgets(choice, sizeof(choice), stdin);

        switch (choice[0]) {
            case '1': {
                char directory[256];
                printf("Enter the directory path: ");
                fgets(directory, sizeof(directory), stdin);
                directory[strcspn(directory, "\n")] = '\0';  // Remove newline character
                list_files(directory);
                break;
            }
            case '2': {
                char filename[256];
                char content[256];
                printf("Enter the file name: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';  // Remove newline character
                printf("Enter the file content: ");
                fgets(content, sizeof(content), stdin);
                content[strcspn(content, "\n")] = '\0';  // Remove newline character
                create_file(filename, content);
                break;
            }
            case '3': {
                char filename[256];
                printf("Enter the file name to delete: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';  // Remove newline character
                delete_file(filename);
                break;
            }
            case '4': {
                char directory[256];
                char criteria[256];
                printf("Enter the directory path: ");
                fgets(directory, sizeof(directory), stdin);
                directory[strcspn(directory, "\n")] = '\0';  // Remove newline character
                printf("Enter the search criteria: ");
                fgets(criteria, sizeof(criteria), stdin);
                criteria[strcspn(criteria, "\n")] = '\0';  // Remove newline character
                search_files(directory, criteria);
                break;
            }
            case '5':
                printf("Exiting the program. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
        }
    }

    return 0;
}
