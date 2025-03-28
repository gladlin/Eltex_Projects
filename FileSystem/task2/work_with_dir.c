#include "mc.h"

void list_dir(Panel *panel) {
    DIR *dir = opendir(panel->path);
    if (!dir) return;

    for (int i = 0; i < panel->count; i++)
        free(panel->files[i]);

    panel->count = 0;

    struct dirent *entry;
    while ((entry = readdir(dir)) && panel->count < MAX_FILES)
        panel->files[panel->count++] = strdup(entry->d_name);

    closedir(dir);
    panel->current = 0;
}

void change_dir(Panel *panel) {
    char new_path[1024];
    strncpy(new_path, panel->path, sizeof(new_path) - 1);
    new_path[sizeof(new_path) - 1] = '\0';

    if (strlen(new_path) + strlen(panel->files[panel->current]) + 2 < sizeof(new_path)) {
        if (strcmp(panel->files[panel->current], "..") == 0) {
            char *last_slash = strrchr(new_path, '/');
            if (last_slash && last_slash != new_path)
                *last_slash = '\0';

        } else if (strcmp(panel->files[panel->current], ".") != 0) {
            strcat(new_path, "/");
            strcat(new_path, panel->files[panel->current]);
        }
    } else
        return;

    if (chdir(new_path) == 0) {
        getcwd(panel->path, sizeof(panel->path));
        list_dir(panel);
    }
}