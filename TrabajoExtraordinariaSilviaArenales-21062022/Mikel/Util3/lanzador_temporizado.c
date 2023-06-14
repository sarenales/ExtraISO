#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

#define error(a){perror(a); _exit(-1);};


int main(int argc, char *argv[]) { 

	int clockid, timer, i, childid, childp, id, cont, status;
	time_t t1,t2;
	char argv1[80];

	status = 0;
	cont = 0;
	
	// Control 1: Numero de parametros dentro de lo establecido.
	if (argc < 3 || argc > 7)
		error("Numero de parametros incorrectos. ");
	
	
	// Control 2: El segundo parametro debe de ser un numero.
	timer = atoi(argv[1]);
	if(timer <= 0 )
		error("No se ha introducido ningun numero en el segundo parametro.");	
	
	t1 = time(NULL);
	
	if((clockid = fork())== 0){
		execlp("./clock", "./clock", argv[1], NULL);
		perror("execlp clock.");
	}else if(clockid == -1)
		perror("Error fork clockid.");
	
	if((childid = fork()) == 0){
		for (i = 2; i < argc ; i++){			
			if((childp = fork()) == 0){
				execlp(argv[i], argv[i], NULL);
				error("Error execvp. ");
			}
			else if (childp == -1 )
				error ("Fork childp");
		}
		for (i = 2; i < argc ; i++){		
			id = wait(NULL);
			printf("proceso (%d) terminado. \n", id);
		}
	}else if(childid == -1)
		perror("Error fork childid.");
	

	
	id = wait(NULL);
	
	
	
    if(id == clockid) 		/* clock finishes first; force child to finish */
    { 
		kill(childid, SIGKILL);
		wait(NULL);
		
		printf("--overtime. Clock finishes first. \n");
		status = 1;
		
    }else if(id == childid){ /* child finishes first; stop clock */
    	
		kill(clockid, SIGKILL);
		wait(NULL);
		
		status = 0;
		t2 = time(NULL);
		printf("--TIME : (%d)s \n", t2-t1);
    }	
	
	exit(status);
	return (status);
	
}