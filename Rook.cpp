// ==========================================
// File:    Rook.cpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#include <iostream>
using namespace std;

#include "Rook.hpp"

Rook::Rook() : ChessPiece() {}

Rook::Rook(Color color) : ChessPiece(color) {}
Rook::Rook(Color color, ChessSquare* position) :
           ChessPiece(color, position) {}

// Public Method: print
// ====================
void Rook::print() {
    cout << *this;
}

// Friend Operator: <<
// ===================
ostream& operator<<(ostream& os, Rook rook) {
    if (rook.color == White) {
        os << "\u2656";
    } else {
        os << "\u265C";
    }
    return os;
}
