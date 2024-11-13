#include "ConfigTest.h"
#include <iostream>
using namespace std;

ConfigTest::ConfigTest(){}

bool ConfigTest::doTests(){
    bool t1, t2;
    cout << "Testing Config class......." << endl;
    t1 = testDefaultConstructor();
    t2 = testConstructor();

    return (t1 && t2);

}

/**
 * Prints the values of each game variable for debugging
 * @param the configuration of the game to print values of
 */
void ConfigTest::printConfigVals(Config newConfig){
    cout << "Printing failed config values..." << endl;
    cout << "Hit duration: " << newConfig.getHitDuration() << endl;
    cout << "Paint blob limit: " << newConfig.getPaintBlobLimit() << endl;
    cout << "Rock lower bound: " << newConfig.getRockLowerBound() << endl;
    cout << "Rock upper bound: " << newConfig.getRockUpperBound() << endl;
    cout << "Fog lower bound: " << newConfig.getFogLowerBound() << endl;
    cout << "Fog upper bound: " << newConfig.getFogUpperBound() << endl;
    cout << "Long range limit: " << newConfig.getLongRangeLimit() << endl;
}

/**
 * helper method to test config values 
 */
bool ConfigTest::testConfigValues(const Config& config, const string& filename, int exp_hitDuration, 
                    int exp_paintBlobLimit, int exp_rockLowerBound, int exp_rockUpperBound, 
                    int exp_fogLowerBound, int exp_fogUpperBound, int exp_longRangeLimit ){
    if(config.getHitDuration() == exp_hitDuration && config.getPaintBlobLimit() ==  exp_paintBlobLimit &&
    config.getRockLowerBound() == exp_rockLowerBound && config.getRockUpperBound() == exp_rockUpperBound &&
    config.getFogLowerBound() == exp_fogLowerBound && config.getFogUpperBound() == exp_fogUpperBound && 
    config.getLongRangeLimit() == exp_longRangeLimit){
        cout << "Test " << filename << " constructor: PASS" << endl;

        //passed test
        return true;
    }
    else{
        cout << "Test " << filename << " constructor: FAIL" << endl;
        printConfigVals(config);

        //failed test
        return false;
    }

}

/**
 * Tests that the default constructor has expected values
 */
bool ConfigTest::testDefaultConstructor(){
    Config newConfig;
   
    if(newConfig.getHitDuration() == 20 && newConfig.getPaintBlobLimit() == 30
        && newConfig.getRockLowerBound() == 10 && newConfig.getRockUpperBound() == 20 
        && newConfig.getFogLowerBound() == 5 && newConfig.getFogUpperBound() == 10
        && newConfig.getLongRangeLimit() == 30){
        cout << "Test default constructor: PASS" << endl;

        //passed test
        return true;
    }
    else{
        cout << "Test default constructor: FAIL" << endl;

        //failed test
        return false;
    }
}

/**
 * Tests constructor (with path/file name)
 */
bool ConfigTest::testConstructor(){

    bool test1, test2, test3, test4, test5, test6, test7, test8, test9, test10, test11;

    test1 = testConfigValues(Config("Config1.txt"), "Config1.txt", 28, 30, 10, 12, 2, 8, 26);
    test2 = testConfigValues(Config("Config2.txt"), "config2.txt", 2, 30, 1, 10, 2, 10, 50);
    test3 = testConfigValues(Config("Config3.txt"), "Config3.txt", 20, 10, 2, 10, 5, 20, 20);
    test4 = testConfigValues(Config("Config4.txt"), "Config4.txt", 20, 30, 10, 20, 2, 30, 55);
    test5 = testConfigValues(Config("Config5.txt"), "Config5.txt", 2, 5, 10, 55, 1, 10, 30);
    test6 = testConfigValues(Config("Config6.txt"), "Config6.txt", 200, 11, 1, 62, 4, 5, 100);
    test7 = testConfigValues(Config("Config7.txt"), "Config7.txt", 10, 2, 2, 15, 7, 8, 30);
    test8 = testConfigValues(Config("Config8.txt"), "Config8.txt", 15, 1, 10, 100, 8, 12, 10);
    test9 = testConfigValues(Config("Config9.txt"), "Config9.txt", 300, 4, 5, 101, 5, 17, 15);
    test10 = testConfigValues(Config("Config10.txt"), "Config10.txt", 45, 35, 3, 25, 5, 10, 30);

    try{
        Config config("NotRealConfig.txt");
        cout << "Testing bad file name: FAIL" << endl;
        //failed test11
        test11 = false;

    } catch(const runtime_error& e){
        cout << "Testing bad file name: PASS" << endl;
        //passed test11
        test11 = true;
    }
    
    //true if all tests passed, false otherwise
    return(test1 && test2 && test3 && test4 && test5 && test6 && test7 && test8 && test9 && test10 && test11);

}

int main(){

    ConfigTest test;
    
    if(test.doTests()){
        cout << "Config tests: ALL PASSED" << endl;
    }
    else{
        cout << "Config tests: NOT ALL TESTS PASSED" << endl;
    }
    return 0;
}