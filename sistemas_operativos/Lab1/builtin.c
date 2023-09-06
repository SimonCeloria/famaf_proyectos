#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "builtin.h"
#include "command.h"
#include "strextra.h"
#include <unistd.h>
#include <libgen.h>
#include "tests/syscall_mock.h"

#define SIZE 1024

const char *internal_commands[] = {"cd", "help", "exit"};
const unsigned int NUM_INTERNAL_COMMANDS = 3;

bool builtin_is_internal(scommand cmd)
{
    assert(cmd != NULL);
    bool is_internal = false;
    for(unsigned int i = 0; i < NUM_INTERNAL_COMMANDS; i++){
        if(strcmp(scommand_front(cmd), internal_commands[i]) == 0){
            is_internal = true;
        }
    }

    return is_internal;
}

bool builtin_alone(pipeline p)
{
    assert(p != NULL);
    bool is_alone = pipeline_length(p) == 1 && builtin_is_internal(pipeline_front(p));
    assert(is_alone == ((pipeline_length(p)) == 1 && builtin_is_internal(pipeline_front(p))));
    return is_alone;
}

static bool only_space(char *path){
    unsigned int lenght = strlen(path);
    bool cond = true;
    unsigned int i = 0;
    
    while (i < lenght && cond){
        cond = cond && path[i] == ' ';
        i++;
    }
    return cond;
    
}

static bool path_special(unsigned int len_path, char *path)
{
    return (len_path == 2 && path[0] == path[1] && path[0] == '.') || 
                only_space(path) || (len_path == 1 && (path[0] == '.' || path[0] == '/' || path[0] == '~'));
}



void builtin_run_cd(scommand cmd)
{
    assert(cmd != NULL);
    char *cwd = NULL;
    char *path = NULL;
    cwd = getcwd(cwd, SIZE);
    char *final_path = dirname(cwd);
    bool is_root_file = false;

    scommand_pop_front(cmd);

    if (scommand_is_empty(cmd))
    {
        final_path = getenv("HOME");
    }
    else
    {
        path = scommand_front(cmd);
        unsigned int len_path = strlen(path);
        bool is_special = path_special(len_path, path);

        /*reviso si es un path especial*/
        if (path[0] != '/' && !is_special)
        {
            path = strmerge("/", path);
        }
        else
        {
            is_root_file = true;
        }

        /*ir al path que quiero ir*/
        if (is_special)
        {
            /*los path especiales son:
             * . --> no va a ningun lado
             * / --> va al root
             * ~  o (uno o mas espacios) --> va al home
             * .. --> ve a la carpeta padre
             */
            if ((len_path == 1 && path[0] == '.') || len_path == 0)
            {
                final_path = getcwd(cwd, SIZE); /*No va a ningun lado*/
            }
            else if (path[0] == '/')
            {
                final_path = "/";
            }
            else if (len_path == 2 && path[0] == path[1] && path[0] == '.')
            {
                ;
            }
            else
            {
                final_path = getenv("HOME");
            }
        }
        else
        { /*no es especial*/
            if (is_root_file)
            {
                final_path = path;
            }
            else
            {
                cwd = getcwd(cwd, SIZE);
                final_path = strcat(cwd, path);
            }
        }
    }
    int did_it_go = chdir(final_path);
    /*veo si salio bien*/
    if (did_it_go != 0)
    {
        perror("Mybash");
    }
}

void builtin_run_help(scommand cmd)
{
    fprintf(stdout, "Welcome to the custom command interpreter.\n"
                    "Available commands:\n"
                    "cd - Change the current directory.\n"
                    "help - Display this help.\n"
                    "exit - Exit the interpreter.\n");
}

void builtin_run(scommand cmd)
{
    assert(builtin_is_internal(cmd));
    char *command_name = scommand_front(cmd);
    if (strcmp(command_name, "cd") == 0)
    {
        builtin_run_cd(cmd);
    }
    else if (strcmp(command_name, "exit") == 0)
    {
        exit(0);
    }
    else
    {
        builtin_run_help(cmd);
    }
}