#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <dirent.h>
#include <fileapi.h>

void list_files(const char *directory);
void create_file(const char *filename, const char *content);
void delete_file(const char *filename);
void search_files(const char *directory, const char *criteria);

#endif // FILE_OPERATIONS_H