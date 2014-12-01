// ==========================================
// File:    Bishop.cpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#include <iostream>
using namespace std;

#include "Bishop.hpp"

Bishop::Bishop() : ChessPiece() {}

Bishop::Bishop(Color color) : ChessPiece(color) {
    this->initSymbol(color);
}
Bishop::Bishop(Color c, ChessSquare* cs) : ChessPiece(c, cs) {
    this->initSymbol(c);
}

// Destructor:
// ===========
Bishop::~Bishop() {}

// Private Method: initSymbol
// ==========================
void Bishop::initSymbol(Color color) {
    this->symbol = (color == White) ? "\u2657" : "\u265D";
}

// Public Method: getSymbol
// ========================
//string Bishop::getSymbol() {
//    return this->symbol;
//}

// Friend Operator: <<
// ===================
ostream& operator<<(ostream& os, Bishop bishop) {
    os << bishop.symbol;
    return os;
}
