// ==========================================
// File:    Knight.cpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#include <iostream>
using namespace std;

#include "Knight.hpp"

Knight::Knight() : ChessPiece() {}

Knight::Knight(Color color) : ChessPiece(color) {
    this->initSymbol(color);
}
Knight::Knight(Color c, ChessSquare* cs) : ChessPiece(c, cs) {
    this->initSymbol(c);
}

// Destructor:
// ===========
Knight::~Knight() {}

// Private Method: initSymbol
// ==========================
void Knight::initSymbol(Color color) {
    this->symbol = (color == White) ? "\u2658" : "\u265E";
}

//// Public Method: getSymbol
//// ========================
//string Knight::getSymbol() {
//    return this->symbol;
//}

// Friend Operator: <<
// ===================
ostream& operator<<(ostream& os, Knight knight) { 
    os << knight.symbol;
    return os;
}
