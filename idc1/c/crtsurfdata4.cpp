/**
 * @file crtsurfdata4.cpp
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

char strddatetime[21];  // observation datetime

vector<struct st_surfdata> vsurfdata; // container for obervation data per minute

vector<struct st_stcode> vstcode; // define a container for the station data

// load the file into the container defined above
bool LoadSTCode(const char *infile);

// create synthetic observation data per minute
void CrtSurfData();

// write the synthetic observation data into file
bool CrtSurfFile(const char *outpath, const char *datafmt);

CLogFile logfile(10); // The maximum of log file is 10 M

int main(int argc, char *argv[])
{
    /* code */
    if (argc != 5)
    {
        printf("Using: ./crtsurfdata4 infile outpath logfile datafmt\n");
        printf("Example: ../bin/crtsurfdata4 ../ini/stcode.ini ../tmp/surfdata ../log/idc/crtsurfdata4.log xml,json,csv\n");
        // remember to give access to ./log to user
        // chown -R mo:dba /log

        printf("infile -> input station data file\n");
        printf("outpath -> generated synthetic observation data file location\n");
        printf("logfile -> running log of current program\n");
        printf("datafmt -> file of the output data file, xml,json,csv supported and split by \',\' \n");

        return -1;
    }

    // open log file
    if (logfile.Open(argv[3], "a+", false) == false)
    {
        printf("logfile.Open(%s) failed.\n", argv[3]);
        return -1;
    }

    logfile.Write("crtsurfdata4 is running ... \n");

    // pass the data from files into vstcode container
    if (LoadSTCode(argv[1]) == false) return -1;

    // generate synthetic observation data
    CrtSurfData();

    // write the generated synthetic data into files: xml,csv,json
    if(strstr(argv[4],"xml")!=0) CrtSurfFile(argv[2],"xml");  
    if(strstr(argv[4],"json")!=0) CrtSurfFile(argv[2],"json");  
    if(strstr(argv[4],"csv")!=0) CrtSurfFile(argv[2],"csv");  

    logfile.Write("crtsurfdata4 has stopped ... \n");

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
        // logfile.Write("=%s=\n", strBuffer);

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

// write the synthetic data in container vsurfdata into file
bool CrtSurfFile(const char *outpath,const char *datafmt)
{
    CFile File;

    // generate file name: SURF_ZH_{datetime}.csv
    char strFileName[301];
    sprintf(strFileName,"%s/SURF_ZH_%s_%d.%s",outpath,strddatetime,getpid(),datafmt);

    // open file
    if(File.OpenForRename(strFileName,"w")==false)
    {
        logfile.Write("File.OpenForRename(%s) failed.\n",strFileName);
        return false;
    }

    // add title (CSV)
    if(strcmp(datafmt,"csv")==0)
    {
        File.Fprintf("Station ID,Time,Temperature,Relative Humidity,Wind Direction,Wind Speed,Rain Fall,Visibility\n");
    }

    // loop container to get/write the data
    for(int ii=0;ii<vsurfdata.size();ii++)
    {
        if(strcmp(datafmt,"csv") == 0)
        {
            File.Fprintf("%s,%s,%.1f,%.1f,%d,%d,%.1f,%.1f,%.1f\n",\
                vsurfdata[ii].obtid,vsurfdata[ii].ddatetime,vsurfdata[ii].t/10.0,vsurfdata[ii].p/10.0,\
                vsurfdata[ii].u,vsurfdata[ii].wd,vsurfdata[ii].wf/10.0,vsurfdata[ii].r/10.0,vsurfdata[ii].vis/10.0);
        }

    }

    // sleep(50); // test whether the tmp file works

    // close the file
    File.CloseAndRename();

    logfile.Write("Successfully generated synthetic observation data file %s, Time: %s, Entry number: %d.\n",strFileName,strddatetime,vsurfdata.size());

    return true;
}