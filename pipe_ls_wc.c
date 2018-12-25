#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Define strings */
#define COMMAND1 "ls"
#define COMMAND2 "wc"
//#define ARG1 ".c"

int main()
{
    int Pipe[2];
    int origStdin, origStdout;
    int childPID;

    /*
     * Save our original stdin and stdout.. in case we need them later
     */
    origStdin = dup(0);
    origStdout = dup(1);

    /* Make our pipe */
    pipe(Pipe);

    /* Make a kid */
    if( (childPID = fork()) < 0 )
    {
        perror( "Fork Error" );
        exit(-1);
    }

    /* Child */
    if( !childPID )
    {
        /* Force our stdin to be the read side of the pipe we made */
        dup2( Pipe[0], 0 );

        /* Force our stdout to be the original standard out */
        dup2( origStdout, 1 );

        /*  Close off all the pipes we no longer need */
        close( origStdout );
       close( origStdin );
	   close( Pipe[0] );
        close( Pipe[1] );

        printf("\n");

        /* Execute our command */
       // execlp( COMMAND2, COMMAND2, ARG1, NULL );
        execlp( COMMAND2, COMMAND2,NULL );
        perror("Execl error");
        exit(-1);
    }

    /*
     * Force our stdout to be the write end of the Pipe we formed.
     * Remeber dup2() make a *copy* of the file descriptor.
     */
    dup2( Pipe[1], 1 );

    /* Close off all the pipes we no longer need */
    close( Pipe[0] );
    close( Pipe[1] );
    close( origStdout );
    close( origStdin );

    /* Execute our command */
    execlp( COMMAND1, COMMAND1, NULL );

    perror( "EXEC Error");

    return 0;
}
