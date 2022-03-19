/**
 * @file crtsurfdata2.cpp
 * @author Shuheng Mo
 * @brief Generate synthetic station observation data (per minute)
 * @version 0.1
 * @date 2022-03-19
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "_public.h"

// load the station observation code to code file
struct st_stcode
{
    char provname[31]; // province
    char obtid[11];    // station id
    char obname[31];   // station name
    double lat;        // latitude
    double lon;        // longitude
    double height;     // height of station
};

// define a container for the station data
vector<struct st_stcode> vstcode;

// load the file into the container defined above
bool LoadSTCode(const char *infile);

CLogFile logfile(10); // The maximum of log file is 10 M

// load station data file into container
bool LoadSTCode(const char *infile)
{
    CFile File;
    CCmdStr CmdStr;
    struct st_stcode stcode;

    // buffer to store string in each line
    char strBuffer[301];

    // read the file with read only mode
    if (File.Open(infile, "r") == false)
    {
        logfile.Write("File.Open(%s)")
    }

    while (true)
    {
        // read one line of the station data until the end of the file
        if (File.Fgets(strBuffer, 300, true) == false)
            break;

        // print out the data from file
        logfile.Write("=%s=\n", strBuffer)

        // split the line loaded
        CmdStr.SplitToCmd(strBuffer, ",");

        // pass the data to a struct
        CmdStr.GetValue(0, stcode.provname, 30);
        CmdStr.GetValue(1, stcode.obtid, 10);
        CmdStr.GetValue(2, stcode.obname, 30);
        CmdStr.GetValue(3, stcode.lat);
        CmdStr.GetValue(4, stcode.lon);
        CmdStr.GetValue(5, stcode.height);

        // pass it to container
        vstcode.push_back(st_stcode);
    }
    return true;
}

int main(int argc, char *argv[])
{
    /* code */
    if (argc != 4)
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
    if (logfile.Open(argv[3], "a+", false) == false)
    {
        printf("logfile.Open(%s) failed.\n", argv[3]);
        return -1;
    }

    logfile.Write("crtsurfdata2 is running ... \n");
    if (LoadSTCode(argv[1] == false))
        return -1;

    logfile.Write("crtsurfdata2 has stopped ... \n");

    return 0;
}
