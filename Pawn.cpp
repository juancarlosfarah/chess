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
    this->name = "Pawn";
    this->initSymbol(color);
}
Pawn::Pawn(Color c, ChessSquare* cs) : ChessPiece(c, cs) {
    this->name = "Pawn";
    this->initSymbol(c);
}


// Destructor:
// ===========
Pawn::~Pawn() {}

// Public Method: isValidMove
// ==========================
bool Pawn::isValidMove(const ChessSquare& square,
                       ChessPiece* piece) const {

    // Ensure validity at the ChessPiece level.
    if (!ChessPiece::isValidMove(square, piece)) return false;
    // TODO: Remove debugging code.
    cout << "Checking at the Pawn level." << endl;
    switch (this->color) {
        case White:
            // Destination square is directly above this square.
            if (square.getRank() - this->square->getRank() == 1) {
                return true;
            }
            // On white pawn's first move, two squares below is valid.
            if (this->square->getRank() == 2 && square.getRank() == 4) {
                return true;
            }
            // One step in superior diagonal is valid when attacking.
            if (square.isDirectlyAboveDiagonally(*(this->square)) &&
                (piece->getColor() == Black)) {
                return true;
            }
            break;
        case Black:
            // Destination square is directly below this square.
            if (square.getRank() - this->square->getRank() == -1) {
                return true;
            }
            // On black pawn's first move, two squares below is valid.
            if (this->square->getRank() == 7 && square.getRank() == 5) {
                return true;
            }
            // One step in inferior diagonal is valid when attacking.
            if (square.isDirectlyBelowDiagonally(*(this->square)) &&
                (piece->getColor() == White)) {
                return true;
            }
            break;
    }
    return false;
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
