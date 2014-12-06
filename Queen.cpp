// ==========================================
// File:    Queen.cpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#include <iostream>
using namespace std;

#include "Queen.hpp"

Queen::Queen() : ChessPiece() {}

Queen::Queen(Color color) : ChessPiece(color) {
    this->name = "Queen";
    this->initSymbol(color);
}
Queen::Queen(Color c, const ChessSquare& cs) : ChessPiece(c, cs) {
    this->name = "Queen";
    this->initSymbol(c);
}

// Destructor:
// ===========
Queen::~Queen() {}

// Private Method: initSymbol
// ==========================
void Queen::initSymbol(Color color) {
    this->symbol = (color == White) ? "\u2655" : "\u265B";
}

// Public Method: isPossibleMove
// ==========================
pair<bool, bool> Queen::isPossibleMove(ChessSquare& square,
                                       ChessPiece* piece) const {

    // Initialise return value.
    pair<bool, bool> rvalue(false, false);

    // Ensure validity at the ChessPiece level.
    if (!ChessPiece::isPossibleMove(square, piece).first) return rvalue;

    // Queens can move to any square on the same rank, file or diagonal.
    if (this->square->getRank() == square.getRank() ||
        this->square->getFile() == square.getFile() ||
        this->square->isDiagonalFrom(square)) {

        // If its source and destination squares are not adjacent, this
        // move needs to be validated for potential blocks. Set the
        // second bool in the rvalue to true.
        if (!this->square->isAdjacent(square)) {
            rvalue.second = true;
        }
        rvalue.first = true;
    }

    return rvalue;
}


// Friend Operator: <<
// ===================
ostream& operator<<(ostream& os, Queen queen) { 
    os << queen.symbol;
    return os;
}
