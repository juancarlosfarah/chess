// ==========================================
// File:    King.cpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#include <iostream>
using namespace std;

#include "King.hpp"

King::King() : ChessPiece() {}

King::King(Color color) : ChessPiece(color) {
    this->name = "King";
    this->initSymbol(color);
}
King::King(Color c, ChessSquare* cs) : ChessPiece(c, cs) {
    this->name = "King";
    this->initSymbol(c);
}

// Destructor:
// ===========
King::~King() {}

// Private Method: initSymbol
// ==========================
void King::initSymbol(Color color) {
    this->symbol = (color == White) ? "\u2654" : "\u265A";
}

//// Public Method: getSymbol
//// ========================
//string King::getSymbol() {
//    return this->symbol;
//}

// Public Method: isPossibleMove
// ==========================
pair<bool, bool> King::isPossibleMove(const ChessSquare& square,
                                   ChessPiece* piece) const {

    // Initialise return value.
    pair<bool, bool> rvalue(false, false);

    // Ensure validity at the ChessPiece level.
    if (!ChessPiece::isPossibleMove(square, piece).first) return rvalue;
    
    // A King can only move to any adjacent square and so does not
    // require the extra validation for potential blocks in the way,
    // thus leaving the second bool in rvalue as false.
    if (this->square->isAdjacent(square)) {
        rvalue.first = true;
    }

    return rvalue;
}

// Friend Operator: << 
// ===================
ostream& operator<<(ostream& os, King king) { 
    os << king.symbol;
    return os;
}
