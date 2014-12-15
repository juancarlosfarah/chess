// ==========================================
// File:    ChessSet.cpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#include "ChessSet.hpp"

// Constructor: Default
// ====================
ChessSet::ChessSet() {
    this->initSide(White);
    this->initSide(Black);
}

// Destructor:
// ===========
// This destructor ensures that all of the ChessPiece objects created
// for each ChessSide are deleted when the ChessSet is destructed.
ChessSet::~ChessSet() {

    // Delete the Whites.
    ChessSideIterator i = this->whites.begin();
    while (i != this->whites.end()) {
        delete *(i);
        *i = nullptr;
        ++i;
    }

    // Delete the Blacks.
    i = this->blacks.begin();
    while (i != this->blacks.end()) {
        delete *(i);
        *i = nullptr;
        ++i;
    }
}

// Private Method: initSide
// ========================
// This method initialises the array of pieces that will be used
// by one ChessSide. It ensures that it has the right number and
// type of pieces according to the rules of chess.
void ChessSet::initSide(Color color) {
    for (int i = 0; i < PIECES_PER_SIDE ; ++i) {

        // Whites are placed in the first two ranks,
        // while Blacks are placed in the last two.
        char file = LEFTMOST_FILE + (i % SIDE_LEN);
        int rank;
        ChessSide* side;
        if (color == White) {
            side = &(this->whites);
            rank = (i >= SIDE_LEN) + BOTTOM_RANK;
        } else {
            side = &(this->blacks);
            rank = TOP_RANK - (i >= SIDE_LEN);
        }

        // Initialise each piece and place it according to
        // its default position as set in Settings.hpp.
        ChessSquare square(file, rank);
        ChessPiece* piece = nullptr;
        if (rank == WHITE_PAWNS || rank == BLACK_PAWNS) {
            piece = new Pawn(color, square);
        } else if (file == L_KNIGHT || file == R_KNIGHT) {
            piece = new Knight(color, square);
        } else if (file == L_BISHOP || file == R_BISHOP) {
            piece = new Bishop(color, square);
        } else if (file == L_ROOK || file == R_ROOK) {
            piece = new Rook(color, square);
        } else if (file == QUEEN) {
            piece = new Queen(color, square);
        } else if (file == KING) {
            piece = new King(color, square);
        }
        side->at(i) = piece;
    }
}

// Public Method: getSide
// ======================
// This method takes a Color and returns a pointer to the
// ChessSide in this ChessSet matching the given Color.
const ChessSide* ChessSet::getSide(const Color& color) const {
    if (color == White) {
        return &(this->whites);
    } else if (color == Black) {
        return &(this->blacks);
    }
    return nullptr;
}

// Public Method: getWhites
// ========================
// Returns a pointer to the whites property of this ChessSet.
const ChessSide* ChessSet::getWhites() const {
    return this->getSide(White);
}

// Public Method: getBlacks
// ========================
// Returns a pointer to the blacks property of this ChessSet.
const ChessSide* ChessSet::getBlacks() const {
    return this->getSide(Black);
}
