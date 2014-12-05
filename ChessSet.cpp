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
ChessSet::~ChessSet() {
    ChessSideIterator i = this->whites.begin();
    while (i != this->whites.end()) {
        delete *(i);
        *i = nullptr;
        ++i;
    }
    cout << endl;
    i = this->blacks.begin();
    while (i != this->blacks.end()) {
        delete *(i);
        *i = nullptr;
        ++i;
    }
}

// Private Method: initSide
// ========================
//
void ChessSet::initSide(Color color) {
    for (int i = 0; i < 16; ++i) {
        char file = 65 + (i % 8);
        int rank;
        ChessSide* side;
        if (color == White) {
            side = &(this->whites);
            rank = (i >= 8) + 1;
        } else {
            side = &(this->blacks);
            rank = 8 - (i >= 8);
        }
        ChessSquare* square = new ChessSquare(file, rank);
        ChessPiece* piece;
        if (rank == 2 || rank == 7) {
            piece = new Pawn(color, square);
        } else if (file == 'B' || file == 'G') {
            piece = new Knight(color, square);
        } else if (file == 'C' || file == 'F') {
            piece = new Bishop(color, square);
        } else if (file == 'A' || file == 'H') {
            piece = new Rook(color, square);
        } else if (file == 'D') {
            piece = new Queen(color, square);
        } else if (file == 'E') {
            piece = new King(color, square);
        }
        side->at(i) = piece;
        // TODO: pointer. Does this make sense?
        square = nullptr;
    }
}

// Public Method: getSide
// ======================
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
const ChessSide* ChessSet::getWhites() const {
    return this->getSide(White);
}

// Public Method: getBlacks
// ========================
const ChessSide* ChessSet::getBlacks() const {
    return this->getSide(Black);
}

// Public Method: print
// ====================
void ChessSet::print() const {
    ChessSideConstIterator i = this->whites.begin();
    while (i != this->whites.end()) {
        cout << **i;
        ++i;
    }
    cout << endl;
    i = this->blacks.begin();
    while (i != this->blacks.end()) {
        cout << **i;
        ++i;
    }
    cout << endl;
}
