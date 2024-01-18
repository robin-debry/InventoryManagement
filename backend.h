#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>


// Define a preprocessor directive for Windows
#ifdef _WIN32
#include <windows.h>
#define PATH_SEPARATOR "\\"
#else
// For non-Windows platforms, assume macOS/Linux
#include <glob.h>
#define PATH_SEPARATOR "/"
#endif

void list_files(char *directory);
void create_file(char *filename, char *content);
void delete_file(char *filename);
void search_files(char *directory, char *criteria);

char directory[256];
char filename[256];
char content[256];
char criteria[256];

// Function to list files in a directory
void list_files(char *directory) {
    printf("Enter the directory path: ");
    scanf("%s", directory);
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
void create_file(char *filename, char *content) {
    printf("Enter the file name: ");
    scanf("%255s", filename);
    printf("Enter the file content: ");
    scanf("%255s", content);
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
void delete_file(char *filename) {
    printf("Enter the file name to delete: ");
    scanf("%255s", filename);
    if (remove(filename) == 0) {
        printf("File '%s' deleted successfully.\n", filename);
    } else {
        perror("Error deleting file");
    }
}

// Function to search for files based on criteria
#ifdef _WIN32
void search_files(char *directory, char *criteria) {
    char search_pattern[MAX_PATH];
    snprintf(search_pattern, sizeof(search_pattern), "%s\\%s", directory, criteria);

    printf("Enter the directory path: ");
    scanf("%255s", directory);
    printf("Enter the search criteria: ");
    scanf("%255s", criteria);

    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile(search_pattern, &findFileData);

    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            printf("%s\n", findFileData.cFileName);
        } while (FindNextFile(hFind, &findFileData) != 0);
        
        FindClose(hFind);
    } else {
        printf("No files found matching the criteria '%s'.\n", criteria);
    }
}

#else
    // Non-Windows (macOS/Linux) specific code for file search
    void search_files(char *directory, char *criteria) {
    char search_pattern[256];
    snprintf(search_pattern, sizeof(search_pattern), "%s/%s", directory, criteria);
    printf("Enter the directory path: ");
    scanf("%255s", directory);
    printf("Enter the search criteria: ");
    scanf("%255s", criteria);

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
#endif
