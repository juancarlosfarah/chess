// ==========================================
// File:    Knight.cpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#include <iostream>
using namespace std;

#include "Knight.hpp"

Knight::Knight() : ChessPiece() {}

Knight::Knight(Color color) : ChessPiece(color) {}
Knight::Knight(Color color, ChessSquare* position) :
           ChessPiece(color, position) {}

// Public Method: print
// ====================
void Knight::print() {
    cout << *this;
}

// Friend Operator: <<
// ===================
ostream& operator<<(ostream& os, Knight knight) { 
    if (knight.color == White) {
        os << "\u2658";
    } else {
        os << "\u265E";
    }
    return os;
}
