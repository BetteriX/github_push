#ifndef FUNC_H
#define FUNC_H

// Create a GitHub repository using the GitHub API
void create_github_repo(char *repo_name, char *username, char *token);

// Retrieve the Git remote URL from .git/config
char *get_git_remote_url();

// Push to an existing Git repository
void normal_git_push(char *git_url, char *token, char *username);

// Create a new local Git repository and link it to GitHub
void first_git_create(char *username, char *token);

// Searches for special characters
int has_spec_character(char *str);

#endif