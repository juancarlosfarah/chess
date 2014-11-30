#include <iomanip>
using namespace std;

#include "ChessBoard.hpp"

// Constructor: Default
// ====================
ChessBoard::ChessBoard() {
    this->init();
    this->arrange();
}

// Private Method: init
// ====================
void ChessBoard::init() {
    for (int i = 65; i <= 72; ++i) {
        for (int rank = 1; rank <= 8; ++rank) {
            char file = static_cast<char>(i);
            try {
                ChessSquare square = ChessSquare(file, rank);
                Position position(square, nullptr);
                this->board.insert(position);
            } catch (InvalidCoordinatesException& e) {
                cerr << "ERROR! Caught InvalidCoordinatesException "
                     << "when calling ChessBoard::init()." << endl;
            }
        }
    }
}

// Private Method: arrange
// =======================
// Arranges the pieces on the chess board.
void ChessBoard::arrange() {
    arrangeSide(White);
    arrangeSide(Black);
}

// Private Method: arrangeSide
// ===========================
// Arranges the pieces on the chess board.
void ChessBoard::arrangeSide(Color color) {
    ChessSide* side;
    if (color == White) {
        side = this->pieces.getWhites();
    } else {
        side = this->pieces.getBlacks();
    }
    ChessSideIterator i = side->begin();
    while (i != side->end()) {
        
        //TODO: Figure out the pointer stuff.
        ChessSquare square = *((*i)->getPosition());
        this->board[square] = *i;
        ++i;
    }
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

// Public Method: getSquare
// ========================
map<ChessSquare, ChessPiece*> ChessBoard::getBoard() {
    return this->board;
}

// Friend Operator: <<
// ===================
ostream& operator<<(ostream& os, ChessBoard cb) {
    return os;
}

// Public Method: Print
// ====================
void ChessBoard::print() {
    cout << "---------------------------------" << endl;
    map<ChessSquare, ChessPiece*>::iterator i = this->board.begin();
    int count = 0;
    while (i != this->board.end()) {
        cout << "| ";
        if (i->second != nullptr) {
            i->second->print();
        } else {
            cout << " ";
        }
        cout << " ";
        ++count;
        if (count % 8 == 0) {
            cout << "|" << endl;
            cout << "---------------------------------" << endl;
        }
        ++i;
    }
}

// Method: getChessSet
// ===================
ChessSet ChessBoard::getChessSet() {
    return this->pieces;
}
