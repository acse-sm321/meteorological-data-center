#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if(argc<3)
    {
        // TODO: choose another proper example
        printf("[INFO] Using: ./procctl timetvl program argvs...\n");
        printf("[INFO] Example: /root/meteorological-data-center/tools1/bin/procctl 5 "\
               "/root/meteorological-data-center/idc1/bin/crtsurfdata /root/meteorological-data-center/idc1/ini/stcode.ini"\
               "/root/meteorological-data-center/tmp/surfdata /root/meteorological-data-center/log/idc/crtsurfdata.log xml,json,csv\n");
        
        printf("[INFO] This is a scheduler program that run services or shell script periodically. \n");
        printf("[INFO] timetvl -> the time interval \n");
        printf("[INFO] program -> executable program that is being called \n");
        printf("[INFO] argvs -> Further arguments for the executable program\n");

        return -1;
    }

    // ignoring disturbing signal, need to be killed by kill -9
    for(int ii=0;ii<64;ii++)
    {
       signal(ii,SIG_IGN);
       close(ii); 
    }

    if(fork()!=0) exit(0);
    
    // let the Parent process wait for child process's return status
    signal(SIGCHLD,SIG_DFL);
    char *pargv[argc];
    for(int ii=2;ii<argc;ii++)
    {
        pargv[ii-2] = argv[ii];
    }

    pargv[argc-2] = NULL;

    // ./procctl 5 /usr/bin/ls -lt /tmp/
    // execute 'ls' in /tmp per 5 sec
    while(true)
    {
        if(fork()==0)
        {
            // execl("/usr/bin/ls","/usr/bin/ls","-lt","/tmp/",(char*)NULL);
            // execl(argv[2],argv[2],argv[3],argv[4],(char*)NULL);
            execv(argv[2],pargv);
            exit(0);
        }
        else
        {
            int status;
            wait(&status);
            sleep(atoi(argv[1]));
        }
    }

    return 0;
}