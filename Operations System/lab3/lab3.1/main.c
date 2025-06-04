#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

void reverse_string(char *str) {
    int length = strlen(str);
    for (int i = 0; i < length / 2; i++) {
        char temp = str[i];
        str[i] = str[length - i - 1];
        str[length - i - 1] = temp;
    }
}

void reverse_file(const char* file1, const char* file2) {
    FILE* original = fopen(file1, "rb");
    if (!original) {
        return;
    }
    FILE* copy = fopen(file2, "wb");
    if (!copy) {
        fclose(original);
        return;
    }

    fseek(original, 0, SEEK_END);
    long file_size = ftell(original);

    for (long i = 1; i <= file_size; i++) {
        fseek(original, -i, SEEK_END);
        fputc(fgetc(original), copy);
    }

    fclose(original);
    fclose(copy);
}

int main(int argc, char** argv) {
    char path[256];
    char dir1[256];
    char dir2[256];
    strcpy(path, argv[1]);
    char *lastSlash = strrchr(path, '/');
    if (lastSlash) {
        strcpy(dir1, lastSlash + 1);
    } else {
        strcpy(dir1, path);
    }
    strcpy(dir2, dir1);
    reverse_string(dir2);
    mkdir(dir2, 0755);
    DIR *dir = opendir(path);
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') {
            continue;
        }
        char file1[512];
        char file2[512];
        snprintf(file1, sizeof(file1), "%s/%s", path, entry->d_name);
        struct stat statbuf;
        if (stat(file1, &statbuf) == 0 && S_ISREG(statbuf.st_mode)) {
            char reversed_name[256];
            strcpy(reversed_name, entry->d_name);
            reverse_string(reversed_name);
            snprintf(file2, sizeof(file2), "%s/%s", dir2, reversed_name);

            reverse_file(file1, file2);
        }
    }

    closedir(dir);
    printf("Копирование завершено.\n");
    return 0;
}
