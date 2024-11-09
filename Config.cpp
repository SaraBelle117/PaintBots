#include <iostream>
#include <stdexcept>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <string>
#include "Config.h"
using namespace std;

//default constructor
Config::Config():
    hitDuration(20),
    paintBlobLimit(30),
    rockLowerBound(10),
    rockUpperBound(20),
    fogLowerBound(5),
    fogUpperBound(10),
    LongRangeLimit(30)
{}

//constructor from a config file
Config::Config(const char* path){
    ifstream configFile(path);

    //make sure file was opened 
    if(!configFile){
        throw runtime_error("Failed to open file. ");
    }

    //sets default values (just in case it is omitted from config file)
    hitDuration = 20;
    paintBlobLimit = 30;
    rockLowerBound = 10;
    rockUpperBound = 20;
    fogLowerBound = 5;
    fogUpperBound = 10;
    LongRangeLimit = 30;

    //parses the file line by line
    string line;
    while(getline(configFile, line)){

        //skips line if empty or begins with "#"
        if(!line.empty() && line[0] == '#' ) continue;

            //locates index of = 
            int eq_index = line.find('=');
            
            //check that = was found (skip if not found)
            if(eq_index == string::npos){
                continue;
            }
            
            //extracts the keyword from 0 to = index
            string keywordStr = line.substr(0, eq_index);

            //gets rid of spaces in keyword using a lambda function (see DEVELOPER.md for more info)
            keywordStr.erase(remove_if(keywordStr.begin(), keywordStr.end(),
            [](unsigned char c) {return isspace(c);}), keywordStr.end());

            //sets value to the remaining part of the string
            string valueStr  = line.substr(eq_index + 1);

            //removes all spaces in the value string
            valueStr.erase(remove_if(valueStr.begin(), valueStr.end(),
            [](unsigned char c) {return isspace(c);}), valueStr.end());

            int value; 
            //bug fix for invalid integer values 
            try{
                value = stoi(valueStr);
            } catch(const invalid_argument& e){
                cerr << "Invalid argument: " << e.what() << endl;
            }

            //converts to C-style string (for use of strcmp)
            const char* keyword = keywordStr.c_str();

            if(strcasecmp(keyword, "hit_duration") == 0){
                hitDuration = value;
            }
            else if(strcasecmp(keyword, "paintblob_limit") == 0){
                paintBlobLimit = value;
            }
            else if(strcasecmp(keyword, "rock_lower_bound") == 0){
                rockLowerBound = value;
            }
            else if(strcasecmp(keyword, "rock_upper_bound") == 0){
                rockUpperBound = value;
            }
            else if(strcasecmp(keyword, "fog_lower_bound") == 0){
                fogLowerBound = value;
            }
            else if(strcasecmp(keyword, "fog_upper_bound") == 0){
                fogUpperBound = value;
            }
            else if(strcasecmp(keyword, "long_range_limit") == 0){
                LongRangeLimit = value;
            }
    }

    //checks that rock upper + lower bound is valid
    if(rockLowerBound > rockUpperBound){
        cerr << "Invalid configuration -- cannot have rock lower bound > rock upper bound." << endl;
        exit(-1);
    }
    //checks that fog upper + lower bound is valud
    if(fogLowerBound > fogUpperBound){
        cerr << "Invalid configuration -- cannot have fog lower bound > fog upper bound." << endl;
        exit(-1);
    }

    configFile.close();
}

int Config::getHitDuration() const
{
    return hitDuration;
}

int Config::getPaintBlobLimit() const
{
    return paintBlobLimit;
}

int Config::getRockLowerBound() const
{
    return rockLowerBound;
}

int Config::getRockUpperBound() const
{
    return rockUpperBound;
}

int Config::getFogLowerBound() const
{
    return fogLowerBound;
}

int Config::getFogUpperBound() const
{
    return fogUpperBound;
}

int Config::getLongRangeLimit() const
{
    return LongRangeLimit;
}