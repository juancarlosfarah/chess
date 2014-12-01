// ==========================================
// File:    Pawn.cpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#include <iostream>
using namespace std;

#include "Pawn.hpp"

Pawn::Pawn() : ChessPiece() {}

Pawn::Pawn(Color color) : ChessPiece(color) {
    this->initSymbol(color);
}
Pawn::Pawn(Color c, ChessSquare* cs) : ChessPiece(c, cs) {
    this->initSymbol(c);
}


// Destructor:
// ===========
Pawn::~Pawn() {}

// Public Method: isValidMove
// ==========================
bool Pawn::isValidMove(ChessSquare& square) {
    return true;
}

// Private Method: initSymbol
// ==========================
void Pawn::initSymbol(Color color) {
    this->symbol = (color == White) ? "\u2659" : "\u265F";
}

//// Public Method: getSymbol
//// ========================
//string Pawn::getSymbol() {
//    return this->symbol;
//}

// Friend Operator: <<
// ===================
ostream& operator<<(ostream& os, Pawn pawn) { 
    os << pawn.symbol;
    return os; 
}
