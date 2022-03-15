/**
 * @file crtsurfdata1.cpp
 * @author Shuheng Mo
 * @brief Generate synthetic station observation data (per minute)
 * @version 0.1
 * @date 2022-03-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "_public.h"


CLogFile logfile;


int main(int argc, char *argv[])
{
    /* code */
    if (argc!=4)
    {
        printf("Using: ./crtsurfdata1 infile outpath logfile\n");
        printf("Example:/project/idc1/bin/crtsurfdata1 /project/idc1/ini/stcode.ini /tmp/surfdata /log/idc\n");
        // remember to give access to ./log to user 
        // chown -R mo:dba /log

        printf("infile -> input station data file\n");
        printf("outpath -> generated synthetic observation data file location\n");
        printf("logfile -> running log of current program");

        return -1;
    }

    // open log file
    if(logfile.Open(argv[3]==false))
    {
        printf("logfile.Open(%s) failed.\n",argv[3]);
        return -1;
    }

    logfile.Write("crtsurfdata1 is running ... \n");
    // work code
    logfile.Write("crtsurfdata1 has stopped ... \n");
    
    return 0;
}
