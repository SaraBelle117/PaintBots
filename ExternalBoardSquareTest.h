#include "ITest.h"
#include "ExternalBoardSquare.h"

class ExternalBoardSquareTest : public ITest {

    public:
        //constructor
        ExternalBoardSquareTest();
        virtual bool doTests() override;
    
    private:
        bool testBase();
};