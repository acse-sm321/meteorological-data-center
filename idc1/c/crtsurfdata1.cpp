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


CLogFile logfile(10);// The maximum of log file is 10 M


int main(int argc, char *argv[])
{
    /* code */
    if (argc!=4)
    {
        printf("Using: ./crtsurfdata1 infile outpath logfile\n");
        printf("Example: /project/idc1/bin/crtsurfdata1 /project/idc1/ini/stcode.ini /tmp/surfdata /project/idc1/log/idc/crtsurfdata1.log\n");
        // remember to give access to ./log to user 
        // chown -R mo:dba /log

        printf("infile -> input station data file\n");
        printf("outpath -> generated synthetic observation data file location\n");
        printf("logfile -> running log of current program\n");

        return -1;
    }

    // open log file
    if(logfile.Open(argv[3],"a+",false)==false)
    {
        printf("logfile.Open(%s) failed.\n",argv[3]);
        return -1;
    }

    logfile.Write("crtsurfdata1 is running ... \n");
    // work code
    for(int ii=0;ii<10000000;ii++)
    {
        logfile.Write("This is the %010d th log.\n",ii);
    }
    logfile.Write("crtsurfdata1 has stopped ... \n");
    
    return 0;
}
