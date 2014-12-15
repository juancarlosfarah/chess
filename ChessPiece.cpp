// ==========================================
// File:    ChessPiece.cpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#include "ChessPiece.hpp"
#include "Settings.hpp"

// Constructor: Default
// ====================
ChessPiece::ChessPiece() {};

// Constructor: Copy
// =================
ChessPiece::ChessPiece(const ChessPiece& other) {
    this->name = other.name;
    this->color = other.color;
    this->symbol = other.symbol;
    this->square = other.square;
}

// Constructor:
// ============
// This constructor takes a Color and a ChessSquare and
// constructs a ChessPiece of that Color and sets its
// square property to point to the given ChessSquare.
ChessPiece::ChessPiece(Color c, const ChessSquare& square) : color(c) {
    this->name = CHESS_PIECE_NAME;
    this->initSymbol(c);
    this->square = new ChessSquare(square);
}

// Constructor:
// ============
// This constructor takes a Color and creates
// a ChessPiece object of that Color.
ChessPiece::ChessPiece(Color c) : color(c) {
    this->name = CHESS_PIECE_NAME;
    this->initSymbol(c);
    this->square = nullptr;
}

// Destructor:
// ===========
// This destructor ensures that the ChessSquare this ChessPiece
// is pointing to is deleted before it is destructed.
ChessPiece::~ChessPiece() {
    if (this->square != nullptr) {
        delete this->square;
    }
    this->square = nullptr;
}

// Private Method: initSymbol
// ==========================
// This method initialises the symbol property
// of the ChessPiece given its Color.
void ChessPiece::initSymbol(Color color) {
    this->symbol = (color == White) ? WHITE_SYMBOL : BLACK_SYMBOL;
}

// Public Method: setSquare
// ========================
// Takes a ChessSquare, creates a copy of that ChessSquare and sets
// a pointer to it as the square attribute of this ChessPiece.
void ChessPiece::setSquare(ChessSquare& square) {
    if (this->square != nullptr) {
        delete this->square;
    }
    this->square = new ChessSquare(square);
}

// Public Method: setSquare
// ========================
// Takes a pointer to a ChessSquare and sets it
// as the square property of this ChessPiece.
void ChessPiece::setSquare(ChessSquare* square) {
    if (this->square != nullptr) {
        delete this->square;
    }
    this->square = (square == nullptr) ? nullptr : new ChessSquare(square);
}

// Public Method: getSquare
// ========================
// This method returns the square property of this ChessPiece.
ChessSquare* ChessPiece::getSquare() {
    return this->square;
}

// Public Method: isPossibleMove
// =============================
// This method takes a ChessSquare and a pointer to the ChessPiece
// in that ChessSquare (or nullptr if its empty), and returns a
// pair of booleans. The first bool indicates if the move is
// possible given the rules of movement of each piece. The second
// bool is true if the move requires the piece to go through one
// or more squares. This indicates if the move needs to be checked
// further by the ChessBoard for any potential obstructions. This
// method is virtual and is overriden by each individual subclass.
pair<bool, bool> ChessPiece::isPossibleMove(ChessSquare& square,
                                            ChessPiece* piece) const {

    // Initialise return value pair.
    pair<bool, bool> rvalue(true, false);

    // A ChessPiece remaining in its place is not a valid move. Also,
    // if the piece in the destination square is the same color as
    // this piece, then return false as you cannot attack yourself.
    if ((*(this->square) == square) ||
        ((piece != nullptr) && (piece->getColor() == this->color))) {

        rvalue.first = false;
    }
    return rvalue;
}

// Public Method: getColor
// =======================
// This method returns the color property of the ChessPiece.
Color ChessPiece::getColor() const {
    return this->color;
}

// Public Method: getSymbol
// ========================
// This method returns the symbol property of the ChessPiece.
string ChessPiece::getSymbol() const {
    return this->symbol;
}

// Public Method: getName
// ======================
// This method returns the name property of the ChessPiece.
string ChessPiece::getName() const {
    return this->name;
}

// Public Method: print
// ====================
// This method prints the symbol property of the ChessPiece.
void ChessPiece::print() const {
    cout << this->symbol;
}

// Friend Operator: <<
// ===================
// Outputs the symbol property of the ChessPiece operand.
ostream& operator<<(ostream& os, const ChessPiece& piece) {
    os << piece.symbol;
    return os;
}

// Operator: <<
// ============
// The insertion operator for the Color enum
// outputs the string name of the given Color.
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
// The negation operator for the Color enum
// returns the Color that is not the operand.
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
