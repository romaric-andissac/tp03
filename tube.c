/*****************************************************************************
 Excerpt from "Linux Programmer's Guide - Chapter 6"
 (C)opyright 1994-1995, Scott Burkett
 ***************************************************************************** 
 MODULE: pipe.c
 *****************************************************************************/
#include <unistd.h> 
#include <stdio.h> 
#include <string.h> 
#include <errno.h> 
#include <stdlib.h>

int main(void)
{
        int     fd[2], s, p;
        pid_t   childpid;
        char    readbuffer[80];
        
        int rayon = 10; //cm

        pipe(fd);
        childpid = fork();
        
        if(childpid == -1)
        {
                perror("fork");
                exit(1);
        }

        if(childpid == 0 )
        {   
                printf("-- Processus fils 1 (%d) -- \n", getpid());
                s = (rayon * rayon) * 3.14;
                char    string1[] = "surface";
                close(fd[0]);
                
                write(fd[1], string1, strlen(string1)+1);
                printf("-- fils 1 a ecrit %s \n", string1);
                exit(0);
        }
        else
        {
                printf("** Processus pere (%d) ** \n", getpid());
                close(fd[1]);
                
        }
        
        childpid = fork(); 
        
        if(childpid == -1)
        {
                perror("fork");
                
                exit(1);
        }
        
        if(childpid == 0 )
        {   
                printf("-- Processus fils 2 (%d) -- \n", getpid());
                p = 2 * 3.14 * rayon;
                char    string2[] = "", p;
                close(fd[0]);
                
                write(fd[1], string2, strlen(string2)+1);
                printf("-- fils 2 a ecrit %s \n", string2);
                
                exit(0);
        }
        
        return(0);
}
