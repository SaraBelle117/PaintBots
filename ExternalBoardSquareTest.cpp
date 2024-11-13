#include "ExternalBoardSquareTest.h"
#include "ExternalBoardSquare.h"
#include <iostream>
using namespace std;

ExternalBoardSquareTest::ExternalBoardSquareTest() {}

bool ExternalBoardSquareTest::doTests()
{
    cout << "Testing ExternalBoard class......." << endl;
    return (testBase());
}

bool ExternalBoardSquareTest::testBase()
{
    if(std::is_base_of<BoardSquare, ExternalBoardSquare>::value){
        cout << "Testing base class: PASS" << endl;
        return true;
    }
    else{
        cout << "Testing bass class: FAIL" << endl;
        return false;
    }
}

int main()
{
    ExternalBoardSquareTest test;

    if(test.doTests()){
        cout << "ExternalBoardSquare tests: ALL PASSED" << endl;
    }
    else{
        cout << "ExternalBoardSquare tests: NOT ALL TESTS PASSED" << endl;
    }

    return 0;
}