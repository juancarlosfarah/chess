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
Bishop::Bishop(Color c, const ChessSquare& cs) : ChessPiece(c, cs) {
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

// Public Method: isPossibleMove
// =============================
pair<bool, bool> Bishop::isPossibleMove(ChessSquare& square,
                                        ChessPiece* piece) const {

    // Initialise return value.
    pair<bool, bool> rvalue(false, false);

    // Ensure validity at the ChessPiece level.
    if (!ChessPiece::isPossibleMove(square, piece).first) return rvalue;

    // A Bishop can move on both of its diagonals.
    if (this->square->isDiagonalFrom(square)) {

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

// Friend Operator: <<
// ===================
ostream& operator<<(ostream& os, Bishop bishop) {
    os << bishop.symbol;
    return os;
}
