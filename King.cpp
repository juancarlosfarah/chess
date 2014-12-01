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
    this->initSymbol(color);
}
King::King(Color c, ChessSquare* cs) : ChessPiece(c, cs) {
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

// Friend Operator: << 
// ===================
ostream& operator<<(ostream& os, King king) { 
    os << king.symbol;
    return os;
}
