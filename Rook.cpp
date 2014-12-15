// ==========================================
// File:    Rook.cpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#include <iostream>
using namespace std;

#include "Rook.hpp"
#include "Settings.hpp"

// Constructor: Default
// ====================
Rook::Rook() : ChessPiece() {}

// Constructor:
// ============
// This constructor takes a Color and creates a Rook of that Color.
Rook::Rook(Color color) : ChessPiece(color) {
    this->name = ROOK_NAME;
    this->initSymbol(color);
}

// Constructor:
// ============
// This constructor takes a Color and a ChessSquare and
// constructs a Rook of that Color, setting its square
// property to point to the given ChessSquare.
Rook::Rook(Color c, const ChessSquare& cs) : ChessPiece(c, cs) {
    this->name = ROOK_NAME;
    this->initSymbol(c);
}

// Destructor:
// ===========
Rook::~Rook() {}

// Private Method: initSymbol
// ==========================
// This method initialises the symbol
// property of the Rook given its Color.
void Rook::initSymbol(Color color) {
    this->symbol = (color == White) ? WHITE_ROOK : BLACK_ROOK;
}

// Public Method: isPossibleMove
// =============================
// This method takes a ChessSquare and a pointer to the ChessPiece
// in that ChessSquare (or nullptr if its empty), and returns a
// pair of booleans. The first bool indicates if the move is
// possible given the rules of movement of the Rook. The second
// bool is true if the move requires the Rook to go through one
// or more squares. This indicates if the move needs to be checked
// further by the ChessBoard for any potential obstructions.
// This method is inherited from the ChessPiece superclass.
pair<bool, bool> Rook::isPossibleMove(ChessSquare& square,
                                      ChessPiece* piece) const {

    // Initialise return value.
    pair<bool, bool> rvalue(false, false);

    // Ensure validity at the ChessPiece level.
    if (!ChessPiece::isPossibleMove(square, piece).first) return rvalue;

    // A Rook can move to any square on the same rank or file. If its
    if (this->square->getRank() == square.getRank() ||
        this->square->getFile() == square.getFile()) {

        // If its source and destination squares are not adjacent, this
        // move needs to be validated for potential blocks. Set the
        // second bool in the rvalue to true.
        if (!this->square->isAdjacent(square)) {
            rvalue.second = true;
        }
        rvalue.first = true;
    }
    return rvalue;
}

// Friend Operator: <<
// ===================
// Outputs the symbol property of the Rook operand.
ostream& operator<<(ostream& os, Rook rook) {
    os << rook.symbol;
    return os;
}
