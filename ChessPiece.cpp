// ==========================================
// File:    ChessPiece.cpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#include "ChessPiece.hpp"

// Constructor:
// ============
ChessPiece::ChessPiece() {};

ChessPiece::ChessPiece(Color c, ChessSquare* p) : color(c), position(p) {}

ChessPiece::ChessPiece(Color c) : color(c) {}

// Public Method: setPosition
// ==========================
// Takes a ChessSquare and sets it as the
// position attribute of this ChessPiece.
void ChessPiece::setPosition(ChessSquare* cs) {
    this->position = cs;
}

// Method: getPosition
// ===================
// Returns the position attribute of this ChessPiece.
ChessSquare* ChessPiece::getPosition() {
    return this->position;
}

// Public Method: print
// ====================
void ChessPiece::print() {
    cout << *this;
}

// Friend Operator: <<
// ===================
ostream& operator<<(ostream& os, ChessPiece cp) {
    if (cp.color == White) {
        os << "W";
    } else {
        os << "B";
    }
    return os;
}
