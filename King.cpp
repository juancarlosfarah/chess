// ==========================================
// File:    King.cpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#include <iostream>
using namespace std;

#include "King.hpp"
#include "Settings.hpp"

// Constructor: Default
// ====================
King::King() : ChessPiece() {}

// Constructor:
// ============
// This constructor takes a Color and creates a King of that Color.
King::King(Color color) : ChessPiece(color) {
    this->name = KING_NAME;
    this->initSymbol(color);
}

// Constructor:
// ============
// This constructor takes a Color and a ChessSquare and
// constructs a King of that Color, setting its square
// property to point to the given ChessSquare.
King::King(Color c, const ChessSquare& cs) : ChessPiece(c, cs) {
    this->name = KING_NAME;
    this->initSymbol(c);
}

// Destructor:
// ===========
King::~King() {}

// Private Method: initSymbol
// ==========================
// This method initialises the symbol
// property of the King given its Color.
void King::initSymbol(Color color) {
    this->symbol = (color == White) ? WHITE_KING : BLACK_KING;
}

// Public Method: isPossibleMove
// =============================
// This method takes a ChessSquare and a pointer to the ChessPiece
// in that ChessSquare (or nullptr if its empty), and returns a
// pair of booleans. The first bool indicates if the move is
// possible given the rules of movement of the King. The second
// bool is true if the move requires the King to go through one
// or more squares. This indicates if the move needs to be checked
// further by the ChessBoard for any potential obstructions.
// This method is inherited from the ChessPiece superclass.
pair<bool, bool> King::isPossibleMove(ChessSquare& square,
                                      ChessPiece* piece) const {

    // Initialise return value.
    pair<bool, bool> rvalue(false, false);

    // Ensure validity at the ChessPiece level.
    if (!ChessPiece::isPossibleMove(square, piece).first) return rvalue;
    
    // A King can only move to any adjacent square and so does not
    // require the extra validation for potential blocks in the way,
    // thus leaving the second bool in rvalue as false.
    if (this->square->isAdjacent(square)) {
        rvalue.first = true;
    }

    return rvalue;
}

// Friend Operator: << 
// ===================
// Outputs the symbol property of the King operand.
ostream& operator<<(ostream& os, King king) { 
    os << king.symbol;
    return os;
}
