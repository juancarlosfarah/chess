// ==========================================
// File:    Queen.cpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#include <iostream>
using namespace std;

#include "Queen.hpp"

Queen::Queen() : ChessPiece() {}

Queen::Queen(Color color) : ChessPiece(color) {}
Queen::Queen(Color color, ChessSquare* position) :
           ChessPiece(color, position) {}

// Public Method: print
// ====================
void Queen::print() {
    cout << *this;
}

// Friend Operator: <<
// ===================
ostream& operator<<(ostream& os, Queen queen) { 
    if (queen.color == White) {
        os << "\u2655";
    } else {
        os << "\u265B";
    }
    return os;
}
