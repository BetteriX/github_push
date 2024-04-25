#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 2048
#define SIZE 100

char* get_git_remote_url() {
    FILE *fp;
    char buffer[MAX_SIZE];
    char *url = NULL;

    fp = fopen(".git/config", "r");
    if (fp == NULL) {
        return "Nincs_git_repo";
    }

    while (fgets(buffer, MAX_SIZE, fp) != NULL) {
        if (strstr(buffer, "remote =") != NULL) {
            // Find the URL part and copy it into a new string
            char *url_start = strstr(buffer, "remote =") + strlen("remote =https:///");
            url = strdup(url_start);
            // Remove trailing newline characters
            url[strcspn(url, "\r\n")] = '\0';
            break;
        }
    }

    fclose(fp);
    return url;
}

void normal_git_push(char* git_url){
    system("git add -A"); 

    printf("Your git repo: %s\n", git_url);
    printf("Add meg a szöveget: ");

    char szoveg[SIZE];
    fgets(szoveg, SIZE, stdin);

    char gitcommit[200];
    sprintf(gitcommit, "git commit -m \"%s\"", szoveg);
    system(gitcommit);
    
    char gitUrl[200];
    sprintf(gitUrl, "https://%s", git_url);

    char gitCommand[200];
    sprintf(gitCommand, "git push -u %s main", gitUrl);
    system(gitCommand);
}   

void first_git_create(char* username){
    system("git branch -m main");

    printf("You don't have a git repo\n");
    printf("Write the name of it (test_git_repo): ");

    char repo_name[SIZE];
    fgets(repo_name, SIZE, stdin);
    repo_name[strlen(repo_name)-1] = '\0';

    system("git init");
    char remoteadd[200];
    sprintf(remoteadd, "git remote add origin https://github.com/%s/%s", username, repo_name);
    system(remoteadd);
}

int main() {
    char* username = getenv("GITHUB_USERNAME");

    if (username == NULL) {
        printf("A felhasználónév nincs megadva\n");
        return 1;
    }

    char* git_url = get_git_remote_url();
    if(git_url == "Nincs_git_repo"){
        first_git_create(username);
    }
    
    normal_git_push(git_url);


    return 0;
}