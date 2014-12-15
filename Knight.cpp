// ==========================================
// File:    Knight.cpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#include <iostream>
using namespace std;

#include "Knight.hpp"
#include "Settings.hpp"

// Constructor: Default
// ====================
Knight::Knight() : ChessPiece() {}

// Constructor:
// ============
// This constructor takes a Color and creates a Knight of that Color.
Knight::Knight(Color color) : ChessPiece(color) {
    this->name = KNIGHT_NAME;
    this->initSymbol(color);
}

// Constructor:
// ============
// This constructor takes a Color and a ChessSquare and
// constructs a Knight of that Color, setting its square
// property to point to the given ChessSquare.
Knight::Knight(Color c, const ChessSquare& cs) : ChessPiece(c, cs) {
    this->name = KNIGHT_NAME;
    this->initSymbol(c);
}

// Destructor:
// ===========
Knight::~Knight() {}

// Private Method: initSymbol
// ==========================
// This method initialises the symbol
// property of the Knight given its Color.
void Knight::initSymbol(Color color) {
    this->symbol = (color == White) ? WHITE_KNIGHT : BLACK_KNIGHT;
}

// Public Method: isPossibleMove
// =============================
// This method takes a ChessSquare and a pointer to the ChessPiece
// in that ChessSquare (or nullptr if its empty), and returns a
// pair of booleans. The first bool indicates if the move is
// possible given the rules of movement of the Knight. The second
// bool is used to indicate if a piece might be blocking the path
// of the Knight. Because a Knight hops over squares, it cannot
// be blocked along the way. Hence that bool is always false.
// This method is inherited from the ChessPiece superclass.
pair<bool, bool> Knight::isPossibleMove(ChessSquare& square,
                                        ChessPiece* piece) const {

    // Initialise return value.
    pair<bool, bool> rvalue(false, false);

    // Ensure validity at the ChessPiece level.
    if (!ChessPiece::isPossibleMove(square, piece).first) return rvalue;

    // A Knight can only move by "hopping" so it does not require the
    // extra validation for potential blocks in the way, thus leaving
    // the second bool in rvalue as false.
    if (this->square->isKnightHopFrom(square)) {
        rvalue.first = true;
    }

    return rvalue;
}

// Friend Operator: <<
// ===================
// Outputs the symbol property of the Knight operand.
ostream& operator<<(ostream& os, Knight knight) { 
    os << knight.symbol;
    return os;
}
