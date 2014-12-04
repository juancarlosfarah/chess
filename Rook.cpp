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

// Public Method: isPossibleMove
// ==========================
pair<bool, bool> Rook::isPossibleMove(const ChessSquare& square,
                                   ChessPiece* piece) const {

    // Initialise return value.
    pair<bool, bool> rvalue(false, false);

    // Ensure validity at the ChessPiece level.
    if (!ChessPiece::isPossibleMove(square, piece).first) return rvalue;

    // A Rook can move to any square on the same rank or file. If its
    if (this->square->getRank() == square.getRank() ||
        this->square->getFile() == square.getFile()) {

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
