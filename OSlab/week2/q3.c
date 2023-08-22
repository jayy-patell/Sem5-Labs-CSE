

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main() {
    const char *path = "/home/Student/Documents/osLab";  // Change this to the directory path you want to list
    DIR *dir = opendir(path);

    if (dir == NULL) {
        perror("Unable to open directory");
        return 1;
    }

    struct dirent *entry;
    char *subdirectories[100];  // Adjust the array size as needed

    int num_subdirectories = 0;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            subdirectories[num_subdirectories] = strdup(entry->d_name);
            num_subdirectories++;
        }
    }

    closedir(dir);

    qsort(subdirectories, num_subdirectories, sizeof(char *), compare);

    printf("Subdirectories in alphabetical order:\n");
    for (int i = 0; i < num_subdirectories; i++) {
        printf("%s\n", subdirectories[i]);
        free(subdirectories[i]);
    }

    return 0;
}
