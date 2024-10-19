#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

#define MAX_SIZE 2048
#define SIZE 100
#define URL_SIZE 512
#define COMMAND_SIZE 1024

// Function to create a GitHub repository using the GitHub API
void create_github_repo(char *repo_name, char *username, char *token)
{
    char command[SIZE * 5]; // Buffer for the curl command

    // Construct the curl command for GitHub API to create a new repository
    sprintf(command,
            "curl -u \"%s:%s\" "
            "-X POST "
            "-H \"Accept: application/vnd.github.v3+json\" "
            "https://api.github.com/user/repos "
            "-d '{\"name\":\"%s\", \"private\":false}' "
            " > /dev/null 2>&1",
            username, token, repo_name);

    // Execute the command to create the repository
    system(command);
}

// Function to retrieve the Git remote URL from .git/config
char *get_git_remote_url()
{
    FILE *fp;
    char buffer[MAX_SIZE];
    char *url = NULL;

    fp = fopen(".git/config", "r");
    if (fp == NULL)
    {
        return strdup("Nincs_git_repo");
    }

    while (fgets(buffer, MAX_SIZE, fp) != NULL)
    {
        if (strstr(buffer, "url =") != NULL)
        {
            // Find the URL part and copy it into a new string
            char *url_start = strstr(buffer, "url =") + strlen("url = https://");
            url = strdup(url_start);
            // Remove trailing newline characters
            url[strcspn(url, "\r\n")] = '\0';
            break;
        }
    }

    fclose(fp);
    return url;
}

// Function to push to an existing Git repository
// Function to push to an existing Git repository
void normal_git_push(char *git_url, char *token, char *username)
{
    system("git add -A");

    printf("Your git repo: %s\n", git_url);
    printf("Add the commit message: ");

    char szoveg[SIZE];
    fgets(szoveg, SIZE, stdin);

    char gitcommit[COMMAND_SIZE];
    snprintf(gitcommit, sizeof(gitcommit), "git commit -m \"%s\"", szoveg);
    system(gitcommit);

    // Create the gitUrl with safety checks
    char gitUrl[URL_SIZE];
    snprintf(gitUrl, sizeof(gitUrl), "https://%s:%s@%s", username, token, git_url);

    // Create the git command with safety checks
    char gitCommand[COMMAND_SIZE];
    snprintf(gitCommand, sizeof(gitCommand), "git push -u %s main", gitUrl);
    system(gitCommand);
}

// Function to create a new local Git repository and link it to GitHub
void first_git_create(char *username, char *token)
{
    system("git branch -m main");

    printf("You don't have a git repo\n");
    printf("Write the name of the repository: ");

    char repo_name[SIZE];
    fgets(repo_name, SIZE, stdin);
    repo_name[strlen(repo_name) - 1] = '\0'; // Remove trailing newline

    // Create the repository on GitHub via the API
    create_github_repo(repo_name, username, token);

    // Initialize a local Git repository
    system("git init");

    char remoteadd[200];
    sprintf(remoteadd, "git remote add origin https://github.com/%s/%s", username, repo_name);
    system(remoteadd);
}