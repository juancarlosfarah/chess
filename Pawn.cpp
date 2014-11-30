// ==========================================
// File:    Pawn.cpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#include <iostream>
using namespace std;

#include "Pawn.hpp"

Pawn::Pawn() : ChessPiece() {}

Pawn::Pawn(Color color) : ChessPiece(color) {}
Pawn::Pawn(Color color, ChessSquare* position) :
           ChessPiece(color, position) {}

// Public Method: print
// ====================
void Pawn::print() {
    cout << *this;
}

// Friend Operator: <<
// ===================
ostream& operator<<(ostream& os, Pawn pawn) { 
    if (pawn.color == White) {
        os << "\u2659";
    } else {
        os << "\u265F";
    }
    return os; 
}
