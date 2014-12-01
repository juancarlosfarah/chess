// ==========================================
// File:    ChessPiece.cpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#include "ChessPiece.hpp"

// Constructor:
// ============
ChessPiece::ChessPiece() {};

ChessPiece::ChessPiece(Color c, ChessSquare* p) : color(c), position(p) {
    this->initSymbol(c);
}

ChessPiece::ChessPiece(Color c) : color(c) {
    this->initSymbol(c);
}

// Destructor:
// ===========
ChessPiece::~ChessPiece() {}

// Private Method: initSymbol
// ============================
void ChessPiece::initSymbol(Color color) {
    this->symbol = (color == White) ? "W" : "B";
}

// Public Method: setPosition
// ==========================
// Takes a ChessSquare and sets it as the
// position attribute of this ChessPiece.
void ChessPiece::setPosition(const ChessSquare* cs) {
    this->position = cs;
}

// Public Method: getPosition
// ==========================
// Returns the position attribute of this ChessPiece.
const ChessSquare* ChessPiece::getPosition() {
    return this->position;
}

// Public Method: isValidMove
// ==========================
bool ChessPiece::isValidMove(ChessSquare& square) {
    return true;
}

//// Virtual Public Method: getSymbol
//// ================================
//string ChessPiece::getSymbol() {
//    return this->symbol;
//}

// Public Method: print
// ====================
void ChessPiece::print() {
    cout << this->symbol;
}

// Friend Operator: <<
// ===================
ostream& operator<<(ostream& os, ChessPiece piece) {
    os << piece.symbol;
    return os;
}
