#pragma once
#include "ITest.h"
#include "Config.h"
#include <string>

class ConfigTest : public ITest {

    public:
        ConfigTest();
        virtual bool doTests() override;
    
    private:
        bool testDefaultConstructor();
        bool testConstructor();
        bool testConfigValues(const Config& config, const std::string& filename, int exp_hitDuration, 
                    int exp_paintBlobLimit, int exp_rockLowerBound, int exp_rockUpperBound, 
                    int exp_fogLowerBound, int exp_fogUpperBound, int exp_longRangeLimit);
        void printConfigVals(Config newConfig);
};

