#include <iomanip>
using namespace std;

#include "ChessBoard.hpp"

// Constructor: Default
// ====================
ChessBoard::ChessBoard() {
    this->init();
    this->arrange();
}

// Destructor:
// ===========
ChessBoard::~ChessBoard() {}

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
        ChessSquare square = *((*i)->getSquare());
        this->board[square] = *i;
        ++i;
    }
}


// Public Method: submitMove
// =========================
//
bool ChessBoard::submitMove(string source, string destination) {
    ChessSquare sourceSquare = ChessSquare(source);
    BoardIterator i = this->board.find(sourceSquare);
    // Return false and notify client if
    // the square is not in the board.
    if (i == this->board.end()) {
        cerr << "Invalid move." << endl;
        return false;
    }
    // Get chess piece at source square.
    ChessPiece* piece = i->second;
    ChessSquare destinationSquare = ChessSquare(destination);
    i = this->board.find(destinationSquare);
    if (i == this->board.end()) {
        cerr << "Invalid move." << endl;
        return false;
    }
    if (piece->isValidMove(destinationSquare)) {
        //cout << destinationSquare << endl;
        this->board[destinationSquare] = piece;
        this->board[sourceSquare] = nullptr;
        //cout << "Set new piece!" << endl;
        piece->setSquare(&(i->first));
        return true;
    }

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

// Public Method: print
// ====================
void ChessBoard::print() {
    this->printTopLine();
    int count = 0;
    map<ChessSquare, ChessPiece*>::iterator i = this->board.begin();
    while (i != this->board.end()) {
        cout << "\u2502 ";
        if (i->second != nullptr) {
            cout << *(i->second);
        } else {
            cout << " ";
        }
        cout << " ";
        ++count;
        if (count % 8 == 0 && count < 64) {
            this->printMiddleLine();
        }
        ++i;
    }
    this->printBottomLine();
}


// Private Method: printMiddleLine
// ===============================
void ChessBoard::printTopLine() {
    cout << "\u250C";
    for (short int i = 1; i <= 8; ++i) {
        cout << "\u2500\u2500\u2500";
        if (i != 8) cout << "\u252C";
    }
    cout << "\u2510" << endl;
}

// Private Method: printMiddleLine
// ===============================
void ChessBoard::printMiddleLine() {
    cout << "\u2502" << endl;
    cout << "\u251C";
    for (short int i = 1; i <= 8; ++i) {
        cout << "\u2500\u2500\u2500";
        if (i != 8) cout << "\u253C";
    }
    cout << "\u2524" << endl;
}

// Private Method: printBottomLine
// ===============================
void ChessBoard::printBottomLine() {
    cout << "\u2502" << endl;
    cout << "\u2514";
    for (short int i = 1; i <= 8; ++i) {
        cout << "\u2500\u2500\u2500";
        if (i != 8) cout << "\u2534";
    }
    cout << "\u2518" << endl;
}

// Method: getChessSet
// ===================
ChessSet ChessBoard::getChessSet() {
    return this->pieces;
}
