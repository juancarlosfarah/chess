// ==========================================
// File:    ChessPiece.cpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#include "ChessPiece.hpp"

// Constructor:
// ============
ChessPiece::ChessPiece() {};

ChessPiece::ChessPiece(const ChessPiece& other) {
    this->name = other.name;
    this->color = other.color;
    this->symbol = other.symbol;
    this->square = other.square;
}

ChessPiece::ChessPiece(Color c, const ChessSquare& square) : color(c) {
    this->name = "Piece";
    this->initSymbol(c);
    this->square = new ChessSquare(square);
}

ChessPiece::ChessPiece(Color c) : color(c) {
    this->name = "Piece";
    this->initSymbol(c);
    this->square = nullptr;
}

// Destructor:
// ===========
ChessPiece::~ChessPiece() {
    if (this->square != nullptr) {
        delete this->square;
    }
    this->square = nullptr;
}

// Private Method: initSymbol
// ============================
void ChessPiece::initSymbol(Color color) {
    this->symbol = (color == White) ? "W" : "B";
}

// Public Method: setSquare
// ========================
// Takes a ChessSquare and sets it as the
// square attribute of this ChessPiece.
void ChessPiece::setSquare(ChessSquare& square) {
    if (this->square != nullptr) {
        delete this->square;
    }
    this->square = new ChessSquare(square);
}

// Public Method: setSquare
// ========================
// Takes a ChessSquare and sets it as the
// square attribute of this ChessPiece.
void ChessPiece::setSquare(ChessSquare* square) {
    if (this->square != nullptr) {
        delete this->square;
    }
    this->square = (square == nullptr) ? nullptr : new ChessSquare(square);
}

// Public Method: getSquare
// ========================
// Returns the square attribute of this ChessPiece.
ChessSquare* ChessPiece::getSquare() {
    return this->square;
}

// Public Method: isPossibleMove
// =============================
pair<bool, bool> ChessPiece::isPossibleMove(ChessSquare& square,
                                            ChessPiece* piece) const {

    // Initialise return value pair.
    pair<bool, bool> rvalue(true, false);

    // A ChessPiece remaining in its place is not a valid move. Also,
    // if the piece in the destination square is the same color as
    // this piece, then return false as you cannot attack yourself.
    if ((*(this->square) == square) ||
        ((piece != nullptr) && (piece->getColor() == this->color))) {

        // TODO: Improve cout and remove invalid code.
        cout << "Invalid move." << endl;
        if (piece != nullptr) {
            cout << *piece << " cannot attack " << *this << endl;
        }
        rvalue.first = false;
    }
    return rvalue;
}

// Public Method: getColor
// =======================
Color ChessPiece::getColor() {
    return this->color;
}

// Public Method: getSymbol
// ========================
string ChessPiece::getSymbol() const {
    return this->symbol;
}

// Public Method: getName
// ======================
string ChessPiece::getName() {
    return this->name;
}

// Public Method: print
// ====================
void ChessPiece::print() {
    cout << this->symbol;
}

// Friend Operator: <<
// ===================
ostream& operator<<(ostream& os, const ChessPiece& piece) {
    os << piece.symbol;
    return os;
}

// Operator: <<
// ============
// Define the insertion operator for Color.
ostream& operator<<(ostream& os, const Color& color) {
    switch (color) {
        case White:
            os << "White";
            break;
        case Black:
            os << "Black";
            break;
        default:
            os << "Invalid Color";
    }
    return os;
}

// Operator: !
// ===========
// Define the negation operator for Color.
Color operator!(const Color& color) {
    switch (color) {
        case White:
            return Black;
        case Black:
            return White;
    }
    // By default return White, but notify client
    // that there is a potential problem with Color.
    cout << "ERROR! Invalid Color. Returning White as "
         << "default. Check for possible corruption."
         << endl;
    return White;
}
