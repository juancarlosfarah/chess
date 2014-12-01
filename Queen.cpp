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

// Friend Operator: <<
// ===================
ostream& operator<<(ostream& os, Queen queen) { 
    os << queen.symbol;
    return os;
}
