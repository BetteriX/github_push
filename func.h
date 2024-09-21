#ifndef FUNC_H
#define FUNC_H

// Function to create a GitHub repository using the GitHub API
void create_github_repo(char* repo_name, char* username, char* token);

// Function to retrieve the Git remote URL from .git/config
char* get_git_remote_url();

// Function to push to an existing Git repository
void normal_git_push(char* git_url, char* token, char* username);

// Function to create a new local Git repository and link it to GitHub
void first_git_create(char* username, char* token);


#endif