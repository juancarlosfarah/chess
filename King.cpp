// ==========================================
// File:    King.cpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#include <iostream>
using namespace std;

#include "King.hpp"

King::King() : ChessPiece() {}

King::King(Color color) : ChessPiece(color) {}
King::King(Color color, ChessSquare* position) :
           ChessPiece(color, position) {}

// Public Method: print
// ====================
void King::print() {
    cout << *this;
}

// Friend Operator: << 
// ===================
ostream& operator<<(ostream& os, King king) { 
    if (king.color == White) {
        os << "\u2654";
    } else {
        os << "\u265A";
    }
    return os;
}
