#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define INPUT_SIZE 1024
#define PATH_SIZE 4096

static void remove_newline(char *text)
{
    size_t length = strlen(text);
    if (length > 0 && text[length - 1] == '\n') {
        text[length - 1] = '\0';
    }
}

static char *skip_spaces(char *text)
{
    while (*text == ' ' || *text == '\t') {
        text++;
    }
    return text;
}

static void command_dir(void)
{
    DIR *directory = opendir(".");
    struct dirent *entry;

    if (directory == NULL) {
        perror("dir");
        return;
    }

    while ((entry = readdir(directory)) != NULL) {
        struct stat file_info;

        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        if (stat(entry->d_name, &file_info) == 0 && S_ISDIR(file_info.st_mode)) {
            printf("[DIR]  %s\n", entry->d_name);
        } else {
            printf("       %s\n", entry->d_name);
        }
    }

    closedir(directory);
}

static void command_create(const char *filename)
{
    FILE *file;

    if (filename == NULL) {
        printf("Usage: create <filename>\n");
        return;
    }

    file = fopen(filename, "wx");
    if (file == NULL) {
        if (errno == EEXIST) {
            printf("File already exists: %s\n", filename);
        } else {
            perror("create");
        }
        return;
    }

    fclose(file);
    printf("Created: %s\n", filename);
}

static void command_input(const char *filename, const char *data)
{
    FILE *file;

    if (filename == NULL || data == NULL || data[0] == '\0') {
        printf("Usage: input <filename> <data>\n");
        return;
    }

    file = fopen(filename, "a");
    if (file == NULL) {
        perror("input");
        return;
    }

    fprintf(file, "%s\n", data);
    fclose(file);
    printf("Data written to: %s\n", filename);
}

static void command_rename(const char *old_name, const char *new_name)
{
    if (old_name == NULL || new_name == NULL) {
        printf("Usage: rename <old_name> <new_name>\n");
        return;
    }

    if (rename(old_name, new_name) != 0) {
        perror("rename");
        return;
    }

    printf("Renamed: %s -> %s\n", old_name, new_name);
}

static void command_delete(const char *filename)
{
    if (filename == NULL) {
        printf("Usage: del <filename>\n");
        return;
    }

    if (unlink(filename) != 0) {
        perror("del");
        return;
    }

    printf("Deleted: %s\n", filename);
}

static void command_cd(const char *path)
{
    if (path == NULL) {
        printf("Usage: cd <directory>\n");
        return;
    }

    if (chdir(path) != 0) {
        perror("cd");
    }
}

static void command_pwd(void)
{
    char path[PATH_SIZE];

    if (getcwd(path, sizeof(path)) == NULL) {
        perror("pwd");
        return;
    }

    printf("%s\n", path);
}

static void print_help(void)
{
    printf("Available commands:\n");
    printf("  dir                         List current directory\n");
    printf("  create <filename>           Create a new empty file\n");
    printf("  input <filename> <data>     Append data to a file\n");
    printf("  rename <old> <new>          Rename a file\n");
    printf("  del <filename>              Delete a file\n");
    printf("  cd <directory>              Change current directory\n");
    printf("  pwd                         Show current directory\n");
    printf("  help                        Show this help\n");
    printf("  exit                        Exit the program\n");
}

int main(void)
{
    char line[INPUT_SIZE];

    printf("Simple OS Shell. Type 'help' to see commands.\n");

    while (1) {
        char *command;
        char *first_argument;
        char *second_argument;

        printf("os> ");
        fflush(stdout);

        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\n");
            break;
        }

        remove_newline(line);
        command = strtok(line, " \t");
        if (command == NULL) {
            continue;
        }

        if (strcmp(command, "dir") == 0) {
            command_dir();
        } else if (strcmp(command, "create") == 0) {
            command_create(strtok(NULL, " \t"));
        } else if (strcmp(command, "input") == 0) {
            first_argument = strtok(NULL, " \t");
            second_argument = strtok(NULL, "");
            if (second_argument != NULL) {
                second_argument = skip_spaces(second_argument);
            }
            command_input(first_argument, second_argument);
        } else if (strcmp(command, "rename") == 0) {
            first_argument = strtok(NULL, " \t");
            second_argument = strtok(NULL, " \t");
            command_rename(first_argument, second_argument);
        } else if (strcmp(command, "del") == 0) {
            command_delete(strtok(NULL, " \t"));
        } else if (strcmp(command, "cd") == 0) {
            command_cd(strtok(NULL, " \t"));
        } else if (strcmp(command, "pwd") == 0) {
            command_pwd();
        } else if (strcmp(command, "help") == 0) {
            print_help();
        } else if (strcmp(command, "exit") == 0) {
            break;
        } else {
            printf("Unknown command: %s\n", command);
        }
    }

    return 0;
}
