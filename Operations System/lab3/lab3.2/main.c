#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

void get_help() {
    char ch;
    FILE* file;
    file = fopen("help.txt", "rb");
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    fclose(file);
}

void create_dir(char* dir) {
    mkdir(dir, 0755);
    printf("Библиотека создана\n");
}


void get_contents_from_lib(char* dir) {
    DIR* directory;
    struct dirent *info;
    if (!(directory = opendir(dir))) {
        printf("Такого файла не существует\n");
        return;
    }
    while ((info = readdir(directory)) != NULL) {
        printf("%s\n", info->d_name);
    }
    closedir(directory);
}

void delete_dir(char* dir) {
    char command[512];
    snprintf(command, sizeof(command), "rm -rf %s", dir);
    if (system(command) == -1) {
        printf("Такой директории не существует\n");
    }
    else {
        printf("Директория %s успешно удалена\n", dir);
    }
}

void create_file(char* filename) {
    FILE* file = fopen(filename, "w");
    fclose(file);
    printf("Файл %s успешно создан\n", filename);
}

void get_contents_from_file(char* filename) {
    char ch;
    FILE* file;
    file = fopen(filename, "rb");
    while((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    fclose(file);
}

void delete_file(char* file) {
    char command[512];
    snprintf(command, sizeof(command), "rm %s", file);
    if (system(command) == -1) {
        printf("Такого файла не существует\n");
    }
    else {
        printf("Файл %s успешно удален\n", file);
    }
}

void create_symbolic_link(char* file) {
    char name[256];
    printf("Введите имя, которое хотите дать символьной ссылке\n");
    scanf("%s", name);
    if (symlink(file, name) == -1) {
        printf("Ошибка при создании символической ссылки");
        return;
    }
    printf("Символическая ссылка %s, указывающая на файл %s создана\n", name, file);
}

void get_symbolic_link(char* name) {
    char link[1024];
    ssize_t len = readlink(name, link, 1023);
    if (len == -1) {
        printf("Ошибка, такой ссылки не существует\n");
    }
    link[len] = '\0';
    printf("содержимое символической ссылки: %s\n", link);
}

void get_content_from_symbolic_link(char* name) {
    char link[1024];
    ssize_t len = readlink(name, link, 1023);
    if (len == -1) {
        printf("Ошибка, такой ссылки не существует\n");
    }
    link[len] = '\0';
    FILE* file = fopen(link, "rb");
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    fclose(file);
    printf("\n");
}

void delete_link(char* name) {
    if (unlink(name) == -1) {
        printf("ошибка, такой ссылки не существует\n");
        return;
    }
    printf("ссылка %s удалена\n", name);
}

void create_hard_link(char* file) {
    char name[256];
    printf("Введите имя, которое хотите дать жесткой ссылке\n");
    scanf("%s", name);
    if (link(file, name) == -1) {
        printf("Ошибка при создании жесткой ссылки");
        return;
    }
    printf("Жесткая ссылка %s, указывающая на файл %s создана\n", name, file);
}

void get_info(char* file) {
    char data[9];
    struct stat file_stat;
    if (stat(file, &file_stat) == -1) {
        printf("Ошибка, такого файла не существует\n");
        return;
    }
    printf("Права:\n");
    if (file_stat.st_mode & S_IRUSR) {
        printf("Владелец может читать этот файл\n");
        data[0] = 'r';
    }
    else {
        printf("Владелец не может читать этот файл\n");
        data[0] = '-';
    }
    if (file_stat.st_mode & S_IWUSR) {
        printf("Владелец может изменять этот файл\n");
        data[1] = 'w';
    }
    else {
        printf("Владелец не может изменять этот файл\n");
        data[1] = '-';
    }
    if (file_stat.st_mode & S_IXUSR) {
        printf("Владелец может исполнять этот файл\n");
        data[2] = 'x';
    }
    else {
        printf("Владелец не может исполнять этот файл\n");
        data[2] = '-';
    }
    if (file_stat.st_mode & S_IRGRP) {
        printf("Группа может читать этот файл\n");
        data[3] = 'r';
    }
    else {
        printf("Группа не может читать этот файл\n");
        data[3] = '-';
    }
    if (file_stat.st_mode & S_IWGRP) {
        printf("Группа может изменять этот файл\n");
        data[4] = 'w';
    }
    else {
        printf("Группа не может изменять этот файл\n");
        data[4] = '-';
    }
    if (file_stat.st_mode & S_IXGRP) {
        printf("Группа может исполнять этот файл\n");
        data[5] = 'x';
    }
    else {
        printf("Группа не может исполнять этот файл\n");
        data[5] = '-';
    }
    if (file_stat.st_mode & S_IROTH) {
        printf("Остальные могут читать этот файл\n");
        data[6] = 'r';
    }
    else {
        printf("Остальные не могут читать этот файл\n");
        data[6] = '-';
    }
    if (file_stat.st_mode & S_IWOTH) {
        printf("Остальные могут изменять этот файл\n");
        data[7] = 'w';
    }
    else {
        printf("Остальные не могут изменять этот файл\n");
        data[7] = '-';
    }
    if (file_stat.st_mode & S_IXOTH) {
        printf("Остальные могут исполнять этот файл\n");
        data[8] = 'x';
    }
    else {
        printf("Остальные не могут исполнять этот файл\n");
        data[8] = '-';
    }
    data[9] = '\0';
    printf("Эти же данные в стандартном виде: %s\n", data);
    printf("Количество жестких ссылок: %ld\n", (long) file_stat.st_nlink);
}

void change_info(char* file) {
    char data[10] = "--------";
    printf("Дальше вводите только да или нет\n");
    char ans[20];
    printf("хотите ли вы, чтобы файл мог читать владелец?\n");
    scanf("%s", ans);
    if (strcmp(ans, "да") == 0) {
        data[0] = 'r';
    }
    else if (strcmp(ans, "нет") == 0) {
        data[0] = '-';
    }
    else {
        printf("ошибка, нужно вводить только да или нет\n");
        return;
    }
    printf("хотите ли вы, чтобы файл мог изменять владелец?\n");
    scanf("%s", ans);
    if (strcmp(ans, "да") == 0) {
        data[1] = 'w';
    }
    else if (strcmp(ans, "нет") == 0) {
        data[1] = '-';
    }
    else {
        printf("ошибка, нужно вводить только да или нет\n");
        return;
    }
    printf("хотите ли вы, чтобы файл мог запускать владелец?\n");
    scanf("%s", ans);
    if (strcmp(ans, "да") == 0) {
        data[2] = 'x';
    }
    else if (strcmp(ans, "нет") == 0) {
        data[2] = '-';
    }
    else {
        printf("ошибка, нужно вводить только да или нет\n");
        return;
    }
    printf("хотите ли вы, чтобы файл могла читать группа?\n");
    scanf("%s", ans);
    if (strcmp(ans, "да") == 0) {
        data[3] = 'r';
    }
    else if (strcmp(ans, "нет") == 0) {
        data[3] = '-';
    }
    else {
        printf("ошибка, нужно вводить только да или нет\n");
        return;
    }
    printf("хотите ли вы, чтобы файл могла изменять группа?\n");
    scanf("%s", ans);
    if (strcmp(ans, "да") == 0) {
        data[4] = 'w';
    }
    else if (strcmp(ans, "нет") == 0) {
        data[4] = '-';
    }
    else {
        printf("ошибка, нужно вводить только да или нет\n");
        return;
    }
    printf("хотите ли вы, чтобы файл могла запускать группа?\n");
    scanf("%s", ans);
    if (strcmp(ans, "да") == 0) {
        data[5] = 'x';
    }
    else if (strcmp(ans, "нет") == 0) {
        data[5] = '-';
    }
    else {
        printf("ошибка, нужно вводить только да или нет\n");
        return;
    }
    printf("хотите ли вы, чтобы файл могли читать остальные?\n");
    scanf("%s", ans);
    if (strcmp(ans, "да") == 0) {
        data[6] = 'r';
    }
    else if (strcmp(ans, "нет") == 0) {
        data[6] = '-';
    }
    else {
        printf("ошибка, нужно вводить только да или нет\n");
        return;
    }
    printf("хотите ли вы, чтобы файл могли изменять другие?\n");
    scanf("%s", ans);
    if (strcmp(ans, "да") == 0) {
        data[7] = 'w';
    }
    else if (strcmp(ans, "нет") == 0) {
        data[7] = '-';
    }
    else {
        printf("ошибка, нужно вводить только да или нет\n");
        return;
    }
    printf("хотите ли вы, чтобы файл могли запускать другие?\n");
    scanf("%s", ans);
    if (strcmp(ans, "да") == 0) {
        data[8] = 'x';
    }
    else if (strcmp(ans, "нет") == 0) {
        data[8] = '-';
    }
    else {
        printf("ошибка, нужно вводить только да или нет\n");
        return;
    }
    data[9] = '\0';
    printf("data: %s\n", data);
    mode_t mode = 0;


    if (data[0] == 'r') {
        mode |= S_IRUSR;
    }
    if (data[1] == 'w') {
        mode |= S_IWUSR;
    }
    if (data[2] == 'x') {
        mode |= S_IXUSR;
    }

    if (data[3] == 'r') {
        mode |= S_IRGRP;
    }
    if (data[4] == 'w') {
        mode |= S_IWGRP;
    }
    if (data[5] == 'x') {
        mode |= S_IXGRP;
    }

    if (data[6] == 'r') {
        mode |= S_IROTH;
    }
    if (data[7] == 'w') {
        mode |= S_IWOTH;
    }
    if (data[8] == 'x') {
        mode |= S_IXOTH;
    }

    if (chmod(file, mode) == 0) {
        printf("Права доступа успешно изменены на %s\n", data);
    }
    else {
        printf("Ошибка, файла %s не существует\n", file);
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Ошибка: недостаточно аргументов.\n");
        return 1;
    }
    char* command = argv[0];
    char* nameOfFile = argv[1];
    if (strcmp(command, "./create_directory") == 0) {
        create_dir(nameOfFile);
    }
    else if (strcmp(command, "./print_directory") == 0) {
        get_contents_from_lib(nameOfFile);
    }
    else if (strcmp(command, "./delete_directory") == 0) {
        delete_dir(nameOfFile);
    }
    else if (strcmp(command, "./create_file") == 0) {
        create_file(nameOfFile);
    }
    else if (strcmp(command, "./print_file") == 0) {
        get_contents_from_file(nameOfFile);
    }
    else if (strcmp(command, "./delete_file") == 0) {
        delete_file(nameOfFile);
    }
    else if (strcmp(command, "./create_symlink") == 0) {
        create_symbolic_link(nameOfFile);
    }
    else if (strcmp(command, "./print_symlink") == 0) {
        get_symbolic_link(nameOfFile);
    }
    else if (strcmp(command, "./print_file_symlink") == 0) {
        get_content_from_symbolic_link(nameOfFile);
    }
    else if (strcmp(command, "./delete_symlink") == 0) {
        delete_link(nameOfFile);
    }
    else if (strcmp(command, "./create_hardlink") == 0) {
        create_hard_link(nameOfFile);
    }
    else if (strcmp(command, "./delete_hardlink") == 0) {
        delete_link(nameOfFile);
    }
    else if (strcmp(command, "./print_access_permissions") == 0) {
        get_info(nameOfFile);
    }
    else if (strcmp(command, "./change_access_permissions") == 0) {
        change_info(nameOfFile);
    }
    else {
        printf("Ошибка: неизвестная команда %s\n", command);
        return 1;
    }

    return 0;
}
