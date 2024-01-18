# include "front.h"
# include <assert.h>

int main()
{
    create_file(filename, content);
    assert(filename != NULL);
    assert(content != NULL);

    delete_file(filename);
    assert(filename != NULL);

    list_files(directory);
    assert(directory != NULL);

    search_files(directory, criteria);
    assert(directory != NULL);
    assert(criteria != NULL);

    return 0;
    
}