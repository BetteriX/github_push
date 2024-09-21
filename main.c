#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"


// Main function to handle Git repo creation or normal push
int main() {
    char* username = getenv("GITHUB_USERNAME");
    char* token = getenv("GITHUB_TOKEN");

    if (username == NULL || token == NULL) {
        printf("A felhasználónév vagy a token nincs megadva\n");
        return 1;
    }

    char* git_url = get_git_remote_url();

    if(strcmp(git_url, "Nincs_git_repo") == 0){
        // No existing repository found, create one
        first_git_create(username, token);
        free(git_url);
        git_url = get_git_remote_url();  // Get the URL after creating the repo
    }

    // Push to the repo
    normal_git_push(git_url, token, username);
    free(git_url);

    return 0;
}
