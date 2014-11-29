#include "ChessBoard.hpp"

// Constructor: Default
// ====================
ChessBoard::ChessBoard() {
    this->arrange();
}

// Private Method: arrange
// =======================
// Arranges the pieces on the chess board.
void ChessBoard::arrange() {
        
}

// Public Method: submitMove
// =========================
//
bool ChessBoard::submitMove(string source, string destination) {
    return false;
}

// Public Method: resetBoard
// =========================
// This method resets the chess board back to its initial state.
void ChessBoard::resetBoard() {
    this->arrange();
}

// Friend Operator: <<
// ===================
ostream& operator<<(ostream& os, ChessBoard cb) {
    return os;
}
