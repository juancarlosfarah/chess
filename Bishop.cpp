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
    this->name = "Bishop";
    this->initSymbol(color);
}
Bishop::Bishop(Color c, ChessSquare* cs) : ChessPiece(c, cs) {
    this->name = "Bishop";
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

// Public Method: isValidMove
// ==========================
bool Bishop::isValidMove(const ChessSquare& square,
                         ChessPiece* piece) const {

    // Ensure validity at the ChessPiece level.
    if (!ChessPiece::isValidMove(square, piece)) return false;

    // A Bishop can move on both of its diagonals.
    return square.isDiagonalFrom(*(this->square));
}

// Friend Operator: <<
// ===================
ostream& operator<<(ostream& os, Bishop bishop) {
    os << bishop.symbol;
    return os;
}
