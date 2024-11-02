#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <string>
#include "Config.h"

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
    std::ifstream configFile(path);

    //make sure file was opened 
    if(!configFile){
        std::cerr << "Failed to open file." << std::endl;
        exit(-1);
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
    std::string line;
    while(std::getline(configFile, line)){
        //skips line if empty or begins with "#"
        if(!line.empty() && line[0] == '#' ) continue;
            //locates index of = 
            int eq_index = line.find('=');
            //TODO: Possible error checking if no = found
            
            //extracts the keyword from 0 to = index
            std::string keywordStr = line.substr(0, eq_index);

            //gets rid of spaces TODO: Remove or reformat?
            keywordStr.erase(std::remove_if(keywordStr.begin(), keywordStr.end(),
            [](unsigned char c) {return std::isspace(c);}), keywordStr.end());

            //sets value to the remaining part of the string
            std::string valueStr  = line.substr(eq_index + 1);

            //DITTO
            valueStr.erase(std::remove_if(valueStr.begin(), valueStr.end(),
            [](unsigned char c) {return std::isspace(c);}), valueStr.end());


            int value = std::stoi(valueStr);

            //converts to C-style string (for use of strcmp)
            const char* keyword = keywordStr.c_str();

            if(strcasecmp(keyword, "hit_duration") == 0){
                hitDuration = value;
            }
            else if(strcasecmp(keyword, "paintbob_limit") == 0){
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