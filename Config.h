#pragma once

class Config
{
    private:
        int hitDuration;
        int paintBlobLimit;
        int rockLowerBound;
        int rockUpperBound;
        int fogLowerBound;
        int fogUpperBound;
        int LongRangeLimit;

    public:
        //default constructor
        Config();

        //constructor from config file
        Config(const char* path);

        //getter methods
        int getHitDuration() const;
        int getPaintBlobLimit() const;
        int getRockLowerBound() const;
        int getRockUpperBound() const;
        int getFogLowerBound() const;
        int getFogUpperBound() const;
        int getLongRangeLimit() const;
};