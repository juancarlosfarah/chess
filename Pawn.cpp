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

// Public Method: isPossibleMove
// ==========================
pair<bool, bool> Pawn::isPossibleMove(const ChessSquare& square,
                                   ChessPiece* piece) const {

    // Initialise return value.
    pair<bool, bool> rvalue(false, false);

    // Ensure validity at the ChessPiece level.
    if (!ChessPiece::isPossibleMove(square, piece).first) return rvalue;

    // Ensure validity at the Pawn level.
    switch (this->color) {
        case White:
            // Destination square is directly above this square. Return
            // (true, false) pair indicating that the move is valid
            // and it does not require validation for potential blocks.
            if (this->square->isDirectlyAbove(square)) {
                rvalue.first = true;
                return rvalue;
            }
            // On white pawn's first move, two squares above is valid.
            // Return (true, true) pair indicating that the move is
            // valid, but it requires validation for potential blocks.
            if (this->square->getRank() == 2 && square.getRank() == 4 &&
                (this->square->getFile() == square.getFile())) {
                rvalue.first = true;
                rvalue.second = true;
                return rvalue;
            }
            // One step in superior diagonal is valid when attacking.
            // Return (true, false) pair indicating that the move is
            // valid and it doesn't require validation for blocks.
            if (square.isDirectlyAboveDiagonally(*(this->square)) &&
                (piece != nullptr && piece->getColor() == Black)) {
                rvalue.first = true;
                return rvalue;
            }
            break;
        case Black:
            // Destination square is directly below this square. Return
            // (true, false) pair indicating that the move is valid
            // and it does not require validation for potential blocks.
            if (this->square->isDirectlyBelow(square)) {
                rvalue.first = true;
                return rvalue;
            }
            // On black pawn's first move, two squares below is valid.
            // Return (true, true) pair indicating that the move is
            // valid, but it requires validation for potential blocks.
            if (this->square->getRank() == 7 && square.getRank() == 5 &&
                (this->square->getFile() == square.getFile())) {
                rvalue.first = true;
                rvalue.second = true;
                return rvalue;
            }
            // One step in inferior diagonal is valid when attacking.
            // Return (true, false) pair indicating that the move is
            // valid and it doesn't require validation for blocks.
            if (square.isDirectlyBelowDiagonally(*(this->square)) &&
                (piece != nullptr && piece->getColor() == White)) {
                rvalue.first = true;
                return rvalue;
            }
            break;
    }
    return rvalue;
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
