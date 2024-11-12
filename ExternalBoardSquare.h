#include "BoardSquare.h"
#include "InternalBoardSquare.h"
#pragma once

class ExternalBoardSquare : public BoardSquare{
        
    public:
        //constructor
        ExternalBoardSquare(const InternalBoardSquare& internalSquare);

};