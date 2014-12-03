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
// ========================
// Takes a ChessSquare and sets it as the
// square attribute of this ChessPiece.
void ChessPiece::setSquare(const ChessSquare* cs) {
    this->square = cs;
}

// Public Method: getSquare
// ========================
// Returns the square attribute of this ChessPiece.
const ChessSquare* ChessPiece::getSquare() {
    return this->square;
}

// Public Method: isValidMove
// ==========================
bool ChessPiece::isValidMove(const ChessSquare& square,
                             ChessPiece* piece) const {

    // A ChessPiece remaining in its place is not a valid move.
    if (*(this->square) == square) return false;

    // If the piece in the destination square is the same color as
    // this piece, then return false as you cannot attack yourself.
    if ((piece != nullptr) && (piece->getColor() == this->color)) {
        // TODO: Improve cout and remove invalid code.
        cout << "Invalid move." << endl;
        cout << *piece << " cannot attack " << *this << endl;
        return false;
    }
    return true;
}

// Virtual Public Method: getColor
// ===============================
Color ChessPiece::getColor() {
    return this->color;
}

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
