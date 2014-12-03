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

// Public Method: isValidMove
// ==========================
bool King::isValidMove(const ChessSquare& square,
                       ChessPiece* piece) const {

    // Ensure validity at the ChessPiece level.
    if (!ChessPiece::isValidMove(square, piece)) return false;
    return this->square->isAdjacent(square);
}

// Friend Operator: << 
// ===================
ostream& operator<<(ostream& os, King king) { 
    os << king.symbol;
    return os;
}
