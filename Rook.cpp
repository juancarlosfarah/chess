// ==========================================
// File:    Rook.cpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#include <iostream>
using namespace std;

#include "Rook.hpp"

Rook::Rook() : ChessPiece() {}

Rook::Rook(Color color) : ChessPiece(color) {
    this->name = "Rook";
    this->initSymbol(color);
}

Rook::Rook(Color c, ChessSquare* cs) : ChessPiece(c, cs) {
    this->name = "Rook";
    this->initSymbol(c);
}

// Destructor:
// ===========
Rook::~Rook() {}

// Private Method: initSymbol
// ==========================
void Rook::initSymbol(Color color) {
    this->symbol = (color == White) ? "\u2656" : "\u265C";
}

// Public Method: isValidMove
// ==========================
bool Rook::isValidMove(const ChessSquare& square,
                       ChessPiece* piece) const {

    // Ensure validity at the ChessPiece level.
    if (!ChessPiece::isValidMove(square, piece)) return false;

    // Rooks can move to any square on the same rank or file.
    if (this->square->getRank() == square.getRank() ||
        this->square->getFile() == square.getFile()) {
        return true;
    }
    return false;
}

//// Public Method: getSymbol
//// ========================
//string Rook::getSymbol() {
//  return this->symbol;
//}

// Friend Operator: <<
// ===================
ostream& operator<<(ostream& os, Rook rook) {
    os << rook.symbol;
    return os;
}
