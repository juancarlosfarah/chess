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
    this->initSymbol(color);
}
Queen::Queen(Color c, ChessSquare* cs) : ChessPiece(c, cs) {
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

//// Public Method: getSymbol
//// ========================
//string Queen::getSymbol() {
//    return this->symbol;
//}

// Public Method: isValidMove
// ==========================
bool Queen::isValidMove(const ChessSquare& square,
                        ChessPiece* piece) const {

    // Ensure validity at the ChessPiece level.
    if (!ChessPiece::isValidMove(square, piece)) return false;

    // Queens can move to any square on the same rank, file or diagonal.
    if (this->square->getRank() == square.getRank() ||
        this->square->getFile() == square.getFile() ||
        this->square->isDiagonalFrom(square)) {
        return true;
    }

    return false;
}


// Friend Operator: <<
// ===================
ostream& operator<<(ostream& os, Queen queen) { 
    os << queen.symbol;
    return os;
}
