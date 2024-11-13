#pragma once

class ITest {

    public:
        //to be overridden in subclasses
        virtual bool doTests() = 0;
        
        //virtual destructor
        virtual ~ITest() {}

};