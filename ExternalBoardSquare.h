#include "BoardSquare.h"
#include "InternalBoardSquare.h"
#pragma once

class ExternalBoardSquare : public BoardSquare{
        
    public:
        //default constructor
        ExternalBoardSquare();
        //constructor
        ExternalBoardSquare(const InternalBoardSquare& internalSquare);

};