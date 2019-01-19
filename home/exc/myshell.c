/*
 * James Robertson
 */
 
/* This program:
 * Provides basic shell functionality of reading a command and parameters and then executing them.
 * Detects and reports errors.
 * Detects and continues if no command is entered.
 * Provides a command to exit the shell, "q".
 * Provides a command to change the prompt, "prompt [new prompt]".
 * (Also provides a command to change the prompt to follow the current working directory, "prompt cwd".)
 * Provides a help command listing internal commands, "help".
 * Does not require the user to type /bin/ for every common command as it uses execvp instead of execve.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define ERROR -1

char *prmt = "> "; //The string shown to the user prompting them to enter a command.

/*
 * Prompt the user to enter a command.
 */
void prompt(char *prmt) {
	printf("%s", prmt);
}

/*
 * Fork the program and execute the command using parameters "params".
 */
int execute(char *params[]) {
  int stat;
  
  if (fork() != 0) { //Parent process, so wait for the child to terminate before continuing.
    waitpid(-1, &stat, 0);
  }
  else { //Child process, execute the program or if there's an error return with an error.
    if (execvp(params[0], &params[0]) == ERROR) {
      return ERROR;
    }
  }
  return 0;
}

/*
 * Check if the user has entered the command to exit the shell, "q".
 */
int checkForHelp(char *params[]) {
  if (strncmp(params[0], "help", 5) == 0) { //If the command is "help"...
    return TRUE;
  }
  return FALSE;
}

/*
 * Check if the user has entered the command to exit the shell, "q".
 */
int checkForCd(char *params[]) {
  if (strncmp(params[0], "cd", 3) == 0) { //If the command is "cd"...
    return TRUE;
  }
  return FALSE;
}

/*
 * Check if the user has entered the command to exit the shell, "q".
 */
int checkForExit(char *params[]) {
  if (strncmp(params[0], "q", 2) == 0) { //If the command is "q"...
    return TRUE;
  }
  return FALSE;
}

/*
 * Check if the user wants to change the prompt.
 */
int checkForPrompt(char *params[]) {
  if (strncmp(params[0], "prompt", 7) == 0) { //If the command is "prompt"...
    return TRUE;
  }
  return FALSE;
}

/*
 * Update the prompt as per user request, or on change of directory when required.
 */
int updatePrompt(char *params[], int p, int isWd) {
  /* Reset the previous prompt */
  memset(prmt, 0, 1);
  prmt = "\0";
  /* Special case: If the user's prompt is "cwd", or the prompt is following the directory and the directory has changed, then replace the prompt with the current working directory. */
  if (strcmp(params[1], "cwd") == 0 || isWd == 1) {
    getcwd(prmt, PATH_MAX + 3);
    strcat(prmt, ">");
    strcat(prmt, " ");
    return TRUE; //The prompt needs to follow the current working directory.
  }
  /* Otherwise, for each argument, add it to the new prompt. */
  else {
    for (int i = 1; i < p; i++) {
      strcat(prmt, params[i]);
      strcat(prmt, " ");
    }
    return FALSE; //The prompt does not need to follow the current working directory.
  }
}

/*
 * Main method to prompt the user to enter a command, parse the command and execute it.
 */
int main(int argc, char *argv[], char *envp[]) {
	char in[256];      //User input command and arguments as a string.
  char *line;        //The line "in", with the newline character removed."
  char *tparams[10]; //Temporary parameters to be inserted into a correctly sized array for the execve function.
  char *tok;         //Used to iterate through each 'word' in the input so that they can be parsed into an array.
  char *cmd;         //The command to execute.
  int  p;            //The number of parameters.
  int  wd = FALSE;   //Whether the prompt should follow the current working directory or not.
  
  printf("\n[Shell by James Robertson]\n");

	while (1) {
    p = 0;

    /* Prompt the user to input a command and arguments. */
		prompt(prmt);
    
		if (fgets(in, sizeof(in), stdin)) {
      /* Ignore commands that begin with spaces and newlines. */
      if (in[0] == 32) {
        printf("An error occured: character ' ' not allowed at the start of a command\n");
      }
      else if (in[0] != 10) {
        /* Parse the data into the correct format. */
        line = strtok(in, "\n"); //Remove the newline character from the input.
        tok = strtok(line, " "); //Get the first word, the command, from the input.
        cmd = tok;
        tparams[p] = cmd; //Add the command as the first argument.
        p++;
        while( tok != NULL ) { //Loop through all the other words, adding them to the array of arguments.
          tok = strtok(NULL, " ");
          if (tok != NULL) {
            tparams[p] = tok;
            p++; 
          }
        }
        tparams[p] = 0;
        char *params[p + 1]; //Create an array of arguments of the correct size, copying the arguments from tparams into it.
        for (int i = 0; i < p; i++) {
          params[i] = tparams[i];
        }
        params[p] = NULL;
        
        /* Check if the user has requested help. */
        if (checkForHelp(params) == TRUE) {
          printf("[Help]\nWhen prompted (default '> ') enter a command to execute it.\n[Internal Commands]\n'help' Displays this help message.\n'prompt [new prompt]' allows you to specify a new prompt.\n('prompt cwd' displays the current working directory as the prompt.)\n'q' Exits this shell. Why would you want to do this?\n");
        }
        
        /* Check if the user has opted to change the prompt. */
        else if (checkForPrompt(params) == TRUE) {
          if (params[1] != NULL) {
            wd = updatePrompt(params, p, 0);
          }
          else {
            printf("An error occured: command 'prompt' requires at least one argument\n");
          }
        }
        
        /* Check if the user wants to change directory. */
        else if (checkForCd(params) == TRUE) {
          if (chdir(params[1]) == ERROR) {
            perror("An error occured");
          }
          else if (wd == 1) {
            wd = updatePrompt(params, p, 1);
          }
        }
        
        /* Check if the user has opted to exit the shell. */
        else if (checkForExit(params) == TRUE) {
          printf("...exiting shell...\n");
          return 0;
        }
        
        /* Execute the command the user has entered. */
        else if (execute(params) == ERROR) {
          perror("An error occured");
          return ERROR;
        }
      }
		}
	}
	return 0;
}