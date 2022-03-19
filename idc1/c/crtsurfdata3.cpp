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
    char obtname[31];  // station name
    double lat;        // latitude
    double lon;        // longitude
    double height;     // height of station
};

// Store the observation data per minute
struct st_surfdata
{
    char obtid[11];     // station id
    char ddatetime[21]; // datetime: yyyymmddhh24miss
    int t;              // temprature
    int p;              // air pressure
    int u;              // humidity
    int wd;             // wind direction
    int wf;             // wind speed
    int r;              // rain: mm 
    int vis;            // visibility
};

vector<struct st_surfdata> vsurfdata; // container for obervation data per minute

// create synthetic observation data per minute
void CrtSurfData();

// define a container for the station data
vector<struct st_stcode> vstcode;

// load the file into the container defined above
bool LoadSTCode(const char *infile);

CLogFile logfile(10); // The maximum of log file is 10 M

int main(int argc, char *argv[])
{
    /* code */
    if (argc != 4)
    {
        printf("Using: ./crtsurfdata3 infile outpath logfile\n");
        printf("Example: /project/idc1/bin/crtsurfdata3 /project/idc1/ini/stcode.ini /tmp/surfdata /project/idc1/log/idc/crtsurfdata3.log\n");
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
    if (LoadSTCode(argv[1]) == false)
        return -1;


    CrtSurfData();

    logfile.Write("crtsurfdata2 has stopped ... \n");

    return 0;
}

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
        logfile.Write("File.Open(%s)");
    }

    while (true)
    {
        // read one line of the station data until the end of the file
        if (File.Fgets(strBuffer, 300, true) == false)
            break;

        // print out the data from file
        logfile.Write("=%s=\n", strBuffer);

        // split the line loaded
        CmdStr.SplitToCmd(strBuffer, ",",true);

        // if we encounter some invalid lines, just drop out
        if(CmdStr.CmdCount()!=6) continue;

        // pass the data to a struct
        CmdStr.GetValue(0, stcode.provname, 30);
        CmdStr.GetValue(1, stcode.obtid, 10);
        CmdStr.GetValue(2, stcode.obtname, 30);
        CmdStr.GetValue(3, &stcode.lat);
        CmdStr.GetValue(4, &stcode.lon);
        CmdStr.GetValue(5, &stcode.height);

        // pass it to container
        vstcode.push_back(stcode);
          
        //  Print out the data loaded from the file
        // for (int ii=0;ii<vstcode.size();ii++)
        // logfile.Write("provname=%s,obtid=%s,obtname=%s,lat=%.2f,lon=%.2f,height=%.2f\n",\
        //            vstcode[ii].provname,vstcode[ii].obtid,vstcode[ii].obtname,vstcode[ii].lat,\
        //            vstcode[ii].lon,vstcode[ii].height);
    }
    return true;
}

void CrtSurfData()
{
    // SEED
    srand(time(0));

    // Get current time and make it as synthetic obs data
    char strddatetime[21];
    memset(strddatetime,0,sizeof(strddatetime));
    LocalTime(strddatetime,"yyyymmddhh24miss");


    struct  st_surfdata stsurfdata;

    // loop through stcode container to get data
    for (int ii=0;ii<vstcode.size();ii++)
    {
        // generate synthetic observation data struct
        memset(&stsurfdata,0,sizeof(struct st_surfdata));

        strncpy(stsurfdata.obtid,vstcode[ii].obtid,10); // station id
        strncpy(stsurfdata.ddatetime,strddatetime,14);  // datetime: yyyymmddhh24miss
        stsurfdata.t=rand()%351;                        // 
        stsurfdata.p=rand()%265+10000;                  // 
        stsurfdata.u=rand()%100+1;                      // 
        stsurfdata.wd=rand()%360;                       // 
        stsurfdata.wf=rand()%150;                       // 
        stsurfdata.r=rand()%16;                         //
        stsurfdata.vis=rand()%5001+100000;              //

        // pass the observation data struct into vsurfdata container
        vsurfdata.push_back(stsurfdata);
    }
    // GDB
    // printf("aaa\n");
}