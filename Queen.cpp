// ==========================================
// File:    Queen.cpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#include <iostream>
using namespace std;

#include "Queen.hpp"
#include "Settings.hpp"

// Constructor: Default
// ====================
Queen::Queen() : ChessPiece() {}

// Constructor:
// ============
// This constructor takes a Color and creates a Queen of that Color.
Queen::Queen(Color color) : ChessPiece(color) {
    this->name = QUEEN_NAME;
    this->initSymbol(color);
}

// Constructor:
// ============
// This constructor takes a Color and a ChessSquare and
// constructs a Queen of that Color, setting its square
// property to point to the given ChessSquare.
Queen::Queen(Color c, const ChessSquare& cs) : ChessPiece(c, cs) {
    this->name = QUEEN_NAME;
    this->initSymbol(c);
}

// Destructor:
// ===========
Queen::~Queen() {}

// Private Method: initSymbol
// ==========================
// This method initialises the symbol
// property of the Queen given its Color.
void Queen::initSymbol(Color color) {
    this->symbol = (color == White) ? WHITE_QUEEN : BLACK_QUEEN;
}

// Public Method: isPossibleMove
// =============================
// This method takes a ChessSquare and a pointer to the ChessPiece
// in that ChessSquare (or nullptr if its empty), and returns a
// pair of booleans. The first bool indicates if the move is
// possible given the rules of movement of the Queen. The second
// bool is true if the move requires the Queen to go through one
// or more squares. This indicates if the move needs to be checked
// further by the ChessBoard for any potential obstructions.
// This method is inherited from the ChessPiece superclass.
pair<bool, bool> Queen::isPossibleMove(ChessSquare& square,
                                       ChessPiece* piece) const {

    // Initialise return value.
    pair<bool, bool> rvalue(false, false);

    // Ensure validity at the ChessPiece level.
    if (!ChessPiece::isPossibleMove(square, piece).first) return rvalue;

    // Queens can move to any square on the same rank, file or diagonal.
    if (this->square->getRank() == square.getRank() ||
        this->square->getFile() == square.getFile() ||
        this->square->isDiagonalFrom(square)) {

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
// Outputs the symbol property of the Queen operand.
ostream& operator<<(ostream& os, Queen queen) { 
    os << queen.symbol;
    return os;
}
