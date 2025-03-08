#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_SCRIPT_SIZE (1024 * 1024)
#define INJECT_COMMAND "!INJECT"
#define EXIT_COMMAND "!EXIT"
#define KILL_COMMAND "!KILL"

char *get_sirhurt_dat() {
    const auto file_path = (char *)malloc(MAX_PATH);
    char app_data_path[MAX_PATH];

    if (!GetEnvironmentVariable("APPDATA", app_data_path, MAX_PATH)) {
        fprintf(stderr, "Error getting %%APPDATA%%: %d\n", GetLastError());
        return nullptr;
    }

    snprintf(file_path, MAX_PATH, "%s\\sirhurt\\sirhui\\sirhurt.dat", app_data_path);
    return file_path;
}

void execute_script(const char *file_path, const char *script) {
    FILE *file = fopen(file_path, "w");

    if (!file) {
        fprintf(stderr, "Error opening %s\n", file_path);
        return;
    }

    fputs(script, file);
    fclose(file);
}

int main(void) {
    const char *file_path = get_sirhurt_dat();
    char script[MAX_SCRIPT_SIZE];
    bool can_execute = true;

    while (1) {
        printf("> ");
        fgets(script, sizeof(script), stdin);
        script[strcspn(script, "\n")] = 0;

        if (strcmp(script, INJECT_COMMAND) == 0) {
            system(".\\sirhurt.exe");
            can_execute = false;
        }

        if (strcmp(script, KILL_COMMAND) == 0) {
            system("taskkill /f /t /im RobloxPlayerBeta.exe");
            can_execute = false;
        }

        if (strcmp(script, EXIT_COMMAND) == 0) {
            break;
        }

        if (can_execute) {
            execute_script(file_path, script);
        }

        memset(script, 0, sizeof(script));
        can_execute = true;
    }

    return 0;
}
