// ==========================================
// File:    Pawn.cpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#include <iostream>
using namespace std;

#include "Pawn.hpp"
#include "Settings.hpp"

// Constructor: Default
// ====================
Pawn::Pawn() : ChessPiece() {}

// Constructor:
// ============
// This constructor takes a Color and creates a Pawn of that Color.
Pawn::Pawn(Color color) : ChessPiece(color) {
    this->name = PAWN_NAME;
    this->initSymbol(color);
}

// Constructor:
// ============
// This constructor takes a Color and a ChessSquare and
// constructs a Pawn of that Color, setting its square
// property to point to the given ChessSquare.
Pawn::Pawn(Color c, const ChessSquare& cs) : ChessPiece(c, cs) {
    this->name = PAWN_NAME;
    this->initSymbol(c);
}

// Destructor:
// ===========
Pawn::~Pawn() {}

// Public Method: isPossibleMove
// =============================
// This method takes a ChessSquare and a pointer to the ChessPiece
// in that ChessSquare (or nullptr if its empty), and returns a
// pair of booleans. The first bool indicates if the move is
// possible given the rules of movement of the Pawn. The second
// bool is true if the move requires the Pawn to go through one
// or more squares. This indicates if the move needs to be checked
// further by the ChessBoard for any potential obstructions.
// This method is inherited from the ChessPiece superclass.
pair<bool, bool> Pawn::isPossibleMove(ChessSquare& square,
                                      ChessPiece* piece) const {

    // Initialise return value.
    pair<bool, bool> rvalue(false, false);

    // Ensure validity at the ChessPiece level.
    if (!ChessPiece::isPossibleMove(square, piece).first) return rvalue;

    // Ensure validity at the Pawn level.
    switch (this->color) {

        case White:

            // These moves require that the destination square is empty.
            if (piece == nullptr) {

                // Destination is directly above this square. Return
                // (true, false) pair indicating that the move is valid
                // and it doesn't require validation for potential block.
                if (this->square->isDirectlyAbove(square)) {
                    rvalue.first = true;
                    return rvalue;
                }

                // On white pawn's first move, two squares above is valid.
                // Return (true, true) pair indicating that the move is
                // valid, but it requires validation for potential block.
                if ((this->square->getRank() == WHITE_PAWNS) &&
                    (square.getRank() == WHITE_PAWNS + 2) &&
                    (this->square->getFile() == square.getFile())) {
                    rvalue.first = true;
                    rvalue.second = true;
                    return rvalue;
                }

            } else {

                // One step in superior diagonal is valid when attacking.
                // Return (true, false) pair indicating that the move is
                // valid and it doesn't require validation for blocks.
                if (this->square->isDirectlyAboveDiagonally(square)) {
                    rvalue.first = true;
                    return rvalue;
                }
            }
            break;

        case Black:

            // These moves require that the destination square is empty.
            if (piece == nullptr) {

                // Destination is directly below this square. Return
                // (true, false) pair indicating that the move is valid
                // and it doesn't require validation for potential block.
                if (this->square->isDirectlyBelow(square)) {
                    rvalue.first = true;
                    return rvalue;
                }

                // On black pawn's first move, two squares below is valid.
                // Return (true, true) pair indicating that the move is
                // valid, but it requires validation for potential block.
                if ((this->square->getRank() == BLACK_PAWNS) &&
                    (square.getRank() == BLACK_PAWNS - 2) &&
                    (this->square->getFile() == square.getFile())) {
                    rvalue.first = true;
                    rvalue.second = true;
                    return rvalue;
                }

            } else {

                // One step in inferior diagonal is valid when attacking.
                // Return (true, false) pair indicating that the move is
                // valid and it doesn't require validation for blocks.
                if (this->square->isDirectlyBelowDiagonally(square)) {
                    rvalue.first = true;
                    return rvalue;
                }
            }
            break;
    }
    return rvalue;
}

// Private Method: initSymbol
// ==========================
// This method initialises the symbol
// property of the Pawn given its Color.
void Pawn::initSymbol(Color color) {
    this->symbol = (color == White) ? WHITE_PAWN : BLACK_PAWN;
}

// Friend Operator: <<
// ===================
// Outputs the symbol property of the Pawn operand.
ostream& operator<<(ostream& os, const Pawn& pawn) { 
    os << pawn.getSymbol();
    return os; 
}
