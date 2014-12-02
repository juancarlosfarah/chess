// ==========================================
// File:    ChessPiece.cpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#include "ChessPiece.hpp"

// Constructor:
// ============
ChessPiece::ChessPiece() {};

ChessPiece::ChessPiece(Color c, ChessSquare* p) : color(c), square(p) {
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

// Public Method: setSquare
// ==========================
// Takes a ChessSquare and sets it as the
// square attribute of this ChessPiece.
void ChessPiece::setSquare(const ChessSquare* cs) {
    this->square = cs;
}

// Public Method: getSquare
// ==========================
// Returns the square attribute of this ChessPiece.
const ChessSquare* ChessPiece::getSquare() {
    return this->square;
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
