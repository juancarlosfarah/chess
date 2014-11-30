// ==========================================
// File:    Bishop.cpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#include <iostream>
using namespace std;

#include "Bishop.hpp"

Bishop::Bishop() : ChessPiece() {}

Bishop::Bishop(Color color) : ChessPiece(color) {}
Bishop::Bishop(Color color, ChessSquare* position) :
           ChessPiece(color, position) {}

// Public Method: print
// ====================
void Bishop::print() {
    cout << *this;
}

// Friend Operator: <<
// ===================
ostream& operator<<(ostream& os, Bishop bishop) {
    if (bishop.color == White) {
        os << "\u2657";
    } else {
        os << "\u265D";
    }
    return os;
}
