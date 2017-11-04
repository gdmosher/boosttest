#include <iostream>
//#include<conio.h>

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<bits/stdc++.h> // vector
#include "component.h"
#include "vector_container.h"

using namespace std;


/*
  Function Declarations for builtin shell commands:
 */
int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);

/*
  List of builtin commands, followed by their corresponding functions.
 */
char *builtin_str[] = {
        "cd",
        "help",
        "exit"
};

int (*builtin_func[]) (char **) = {
        &lsh_cd,
        &lsh_help,
        &lsh_exit
};

int lsh_num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}
/*
  Builtin function implementations.
*/
int lsh_cd(char **args)
{
    if (args[1] == NULL) {
        fprintf(stderr, "lsh: expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("lsh");
        }
    }
    return 1;
}

int lsh_help(char **args)
{
    int i;
    printf("Stephen Brennan's LSH\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    for (i = 0; i < lsh_num_builtins(); i++) {
        printf("  %s\n", builtin_str[i]);
    }

    printf("Use the man command for information on other programs.\n");
    return 1;
}

int lsh_exit(char **args)
{
    return 0;
}

// Class Declarations

class ShellComponent {
    //Access - Specifier
private:

public:

    //Variable Declaration
    int id;
    
int lsh_launch(char **args)
{
    pid_t pid, wpid;
    int status;
//args[2]=0;
//cout << "Ready to fork, " << args[0] << " with args " << args[1]  << "\n";
//cout << "Ready to fork, " << args[0] << " with args " << args[1] << args[2] << "\n";
    pid = fork();
    if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1) {
            perror("lsh");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // Error forking
        perror("lsh");
    } else {
        // Parent process
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return status;
}

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"
char **lsh_split_line(char *line)
{
    int bufsize = LSH_TOK_BUFSIZE, position = 0;
    char **tokens = (char **)malloc(bufsize * sizeof(char*));
    char *token;

    if (!tokens) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, LSH_TOK_DELIM);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += LSH_TOK_BUFSIZE;
            tokens = (char **)realloc(tokens, bufsize * sizeof(char*));
            if (!tokens) {
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, LSH_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

char *lsh_read_line(void)
{
    char *line = NULL;
    ssize_t bufsize = 0; // have getline allocate a buffer for us
    getline(&line, (size_t*)&bufsize, stdin);
    return line;
}

#define LSH_RL_BUFSIZE 1024
char *lsh_read_line2(void)
{
    int bufsize = LSH_RL_BUFSIZE;
    int position = 0;
    char *buffer = (char *)malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Read a character
        c = getchar();

        // If we hit EOF, replace it with a null character and return.
        if (c == EOF || c == '\n') {
            buffer[position] = '\0';
            return buffer;
        } else {
            buffer[position] = c;
        }
        position++;

        // If we have exceeded the buffer, reallocate.
        if (position >= bufsize) {
            bufsize += LSH_RL_BUFSIZE;
            buffer = (char *)realloc(buffer, bufsize);
            if (!buffer) {
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}


int lsh_execute(char **args)
{
    int i;

    if (args[0] == NULL) {
        // An empty command was entered.
        return 1;
    }

    if (strcmp(args[0], "exit") == 0) {
      exit(0);
    }

    for (i = 0; i < lsh_num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }

    return lsh_launch(args);
}
int my_execute(std::string str) {
  char * args[10];

  if (str == "") {
    return 1;
  }
  if (str.substr(1,4) == "exit") {
    exit(0);
  }
  args[0] = (char *)str.c_str(); //DDD Don't Do Dat? When does this string die?
  args[1] = 0;
  return lsh_launch(args);
}

void lsh_loop(void)
{
    char *line;
    char **args;
    vector <string> args2;
    int status;
    char line2[254];
    char con[254];
    Op2* con1;
    Op2* cmd1;
    int index;

    DoubleFactory* dblfact = new DoubleFactory();
    VectorContainer* vcmd = new VectorContainer(dblfact);
    VectorContainer* vcon = new VectorContainer(dblfact);

    do {
        printf("> ");
//      parse(); // readline and parse to container
      index = 0;
      int end_index = vcmd->size();
      do {      // loop until all parsed data is processed  
        // pop a simple command off of Nelson's queue
        cmd1 = new Op2("exit");
        if (index >= end_index) {
          break;
        }
//        cmd1 = vcmd->at(index);
        line = cmd1->get_line();
        strcpy(line2,line);
//        strcpy(line2,"ls -l");
        cout << "-----------------------------" << line2 << "------------------" << endl;
        args = lsh_split_line(line2);

        status = lsh_execute(args);
        cout << "Status: "<< status << endl;

        con1 = (Op2*)vcon->at(index);
        index++; // same index for cmd1 and con1
        strcpy(con, con1->get_line());
        if      (con1->cmd == ";" ) {
        }
        else if (con1->cmd == "&&") {
          if (status == 0) {
          }
          else {
            index++; // just trash the next command
          }
        } 
        else if (con1->cmd == "||") {
          if (status == 0) {
            index++; // just trash the next command
          }
          else {
          }
        }
        printf("> ");
        printf("> ");
        printf("> ");
        printf("> ");
        printf("> ");
        printf("> ");
        printf("> ");
        printf("> ");
        printf("> ");

//        free(line);
        free(args);

        // one command done, check connector to set flag to skip a command if neccessary
      } while (status);
   //     printf("> ");

  //      line = lsh_read_line();
/*
        strcpy(line2, string("exit").c_str());
        args = lsh_split_line(line2);
        status = lsh_execute(args);
*/
//        free(line);
     //   free(args);
    } while (status);
}

void rshell(void)
{
	lsh_loop();
}
};

//Main Function

int main() {
    // Object Creation For Class
    //ShellComponent	rshell;
    ShellComponent* rshell = new ShellComponent();

    //Get Input Values For Object Varibales
//    cout << "Enter the Number :";
//    cin >> rshell->id;

    //Show the Output
//    cout <<  rshell->id << endl;
    
    cout << "\nEntering shell - type exit to leave\n\n";
	rshell->rshell();
	
    //getch();
    //return 0;
    return EXIT_SUCCESS;
}
