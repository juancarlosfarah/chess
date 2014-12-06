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
    this->name = "Knight";
    this->initSymbol(color);
}
Knight::Knight(Color c, const ChessSquare& cs) : ChessPiece(c, cs) {
    this->name = "Knight";
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

// Public Method: isPossibleMove
// =============================
pair<bool, bool> Knight::isPossibleMove(ChessSquare& square,
                                        ChessPiece* piece) const {

    // Initialise return value.
    pair<bool, bool> rvalue(false, false);

    // Ensure validity at the ChessPiece level.
    if (!ChessPiece::isPossibleMove(square, piece).first) return rvalue;

    // A Knight can only move by "hopping" so it does not require the
    // extra validation for potential blocks in the way, thus leaving
    // the second bool in rvalue as false.
    if (this->square->isKnightHopFrom(square)) {
        rvalue.first = true;
    }

    return rvalue;
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
