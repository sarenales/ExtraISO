#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define error(a){perror(a); _exit(-1);};


main() { 
    int pfd[2], pid;
 
    // se crea la tuberia (PIPE)
    if (pipe(pfd) == -1) error("pipe");

    // creacion del primer hijo (last)
    switch (pid = fork()) {
 	    case -1: error("fork");
  	    case 0:    
 		    if (close(1) == -1) error("close");
 		    if (dup(pfd[1]) != 1) error("dup");
 		    close(pfd[0]);
		    close(pfd[1]);
 		    execlp("last","last", "-10", NULL);
		    error("execlp");
    } 
  
    // creacion del segundo hijo (grep)
    switch (pid = fork()) {
  	    case -1: error("fork");
   	    case 0: 
 	        if (close(0) == -1) error("close");
	        if (dup(pfd[0]) != 0) error("dup");
 	        close(pfd[0]);
	        close(pfd[1]);
            execlp("grep", "grep", "acaf00", NULL);
 	        error("execlp");
    }

    close(pfd[0]);
    close(pfd[1]);
    
    while((pid=wait(NULL))!=-1)

    exit(0);
}