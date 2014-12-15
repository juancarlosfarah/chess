// ==========================================
// File:    Bishop.cpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#include <iostream>
using namespace std;

#include "Bishop.hpp"
#include "Settings.hpp"

// Constructor: Default
// ====================
Bishop::Bishop() : ChessPiece() {}

// Constructor:
// ============
// This constructor takes a Color and creates a Bishop of that Color.
Bishop::Bishop(Color color) : ChessPiece(color) {
    this->name = BISHOP_NAME;
    this->initSymbol(color);
}

// Constructor:
// ============
// This constructor takes a Color and a ChessSquare and
// constructs a Bishop of that Color, setting its square
// property to point to the given ChessSquare.
Bishop::Bishop(Color c, const ChessSquare& cs) : ChessPiece(c, cs) {
    this->name = BISHOP_NAME;
    this->initSymbol(c);
}

// Destructor:
// ===========
Bishop::~Bishop() {}

// Private Method: initSymbol
// ==========================
// This method initialises the symbol
// property of the Bishop given its Color.
void Bishop::initSymbol(Color color) {
    this->symbol = (color == White) ? WHITE_BISHOP : BLACK_BISHOP;
}

// Public Method: isPossibleMove
// =============================
// This method takes a ChessSquare and a pointer to the ChessPiece
// in that ChessSquare (or nullptr if its empty), and returns a
// pair of booleans. The first bool indicates if the move is
// possible given the rules of movement of the Bishop. The second
// bool is true if the move requires the Bishop to go through one
// or more squares. This indicates if the move needs to be checked
// further by the ChessBoard for any potential obstructions.
// This method is inherited from the ChessPiece superclass.
pair<bool, bool> Bishop::isPossibleMove(ChessSquare& square,
                                        ChessPiece* piece) const {

    // Initialise return value.
    pair<bool, bool> rvalue(false, false);

    // Ensure validity at the ChessPiece level.
    if (!ChessPiece::isPossibleMove(square, piece).first) return rvalue;

    // A Bishop can move on both of its diagonals.
    if (this->square->isDiagonalFrom(square)) {

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
// Outputs the symbol property of the Bishop operand.
ostream& operator<<(ostream& os, Bishop bishop) {
    os << bishop.symbol;
    return os;
}
