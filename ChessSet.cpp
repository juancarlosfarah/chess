// ==========================================
// File:    ChessSet.cpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#include "ChessSet.hpp"

ChessSet::ChessSet() {
    this->initSide(White);
    this->initSide(Black);
}

void ChessSet::initSide(Color color) {
    for (int i = 0; i < 16; ++i) {
        char file = 65 + (i % 8);
        int rank;
        if (color == White) {
            rank = (i >= 8) + 1;
        } else {
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
        ChessSide* side = this->getSide(color);
        side->at(i) = piece;
        // TODO: pointer?
    }
}

ChessSide* ChessSet::getSide(Color color) {
    if (color == White) {
        return &(this->whites);
    } else if (color == Black) {
        return &(this->blacks);
    }
    return nullptr;
}

// Public Method: getWhites
// ========================
ChessSide* ChessSet::getWhites() {
    return this->getSide(White);
}

// Public Method: getBlacks
// ========================
ChessSide* ChessSet::getBlacks() {
    return this->getSide(Black);
}

// Public Method: print
// ====================
void ChessSet::print() {
    ChessSide::iterator i = this->whites.begin();
    while (i != this->whites.end()) {
        (*i)->print();
        ++i;
    }
    cout << endl;
    i = this->blacks.begin();
    while (i != this->blacks.end()) {
        (*i)->print();
        ++i;
    }
    cout << endl;
}


