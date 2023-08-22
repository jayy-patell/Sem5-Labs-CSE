

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int main() {
    DIR *dir = opendir(".");
    
    if (dir == NULL) {
        perror("Unable to open directory");
        return 1;
    }

    struct dirent *entry;
    
    printf("Files in the current directory:\n");
    
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dir);

    printf("\nEnter the name of the file you want to remove (or 'all' to remove all files): ");
    char filename[256];
    scanf("%255s", filename);

    if (strcmp(filename, "all") == 0) {
        dir = opendir(".");
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_type == DT_REG) {
                remove(entry->d_name);
                printf("Removed: %s\n", entry->d_name);
            }
        }
        closedir(dir);
    } else {
        if (remove(filename) == 0) {
            printf("Removed: %s\n", filename);
        } else {
            perror("Unable to remove file");
        }
    }

    return 0;
}
