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
        int     fd[2], nbytes;
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
                float surface = (rayon * rayon) * 3.14;
                char    string1[] = "surface";
                close(fd[0]);
                
                printf("-- Fils 1 a fermé le tube en lecture -- \n");
                nbytes = write(fd[1], &surface, sizeof(surface));
                printf("-- fils 1 a ecrit %d octets %f \n",nbytes , surface);

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
                float perimetre = 2 * 3.14 * rayon;
                char    string2[] = "", p;
                close(fd[0]);
                
                write(fd[1], &perimetre, sizeof(perimetre) );
                printf("-- fils 2 a ecrit %f \n", perimetre);
                
                exit(0);
        }
        
        return(0);
}
