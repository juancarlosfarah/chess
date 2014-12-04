#include <iomanip>
#include <sstream>
using namespace std;

#include "ChessBoard.hpp"

// Constructor: Default
// ====================
ChessBoard::ChessBoard() {
    this->init();
    this->arrange();
    this->startGame();
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

// Private Method: startGame
// =========================
// This method ensures that the properties of the ChessBoard are
// ready for a game of chess.
void ChessBoard::startGame() {
    this->turn = White;
    cout << "A new chess game is started!" << endl;
}

// Private Method: switchTurns
// ===========================
// This method changes the turn property of the ChessBoard
// to the Color of the player whose turn it is to move next.
void ChessBoard::switchTurns() {
    switch (this->turn) {
        case White:
            this->turn = Black;
            break;
        case Black:
            this->turn = White;
            break;
        default:
            cerr << "WARNING! The turn property of this "
                 << "ChessBoard is not set properly. "
                 << "Setting it by default to White." << endl;
            this->turn = White;
    }
}

// Public Method: submitMove
// =========================
//
bool ChessBoard::submitMove(string source, string destination) {
    ChessSquare sourceSquare = ChessSquare(source);
    BoardIterator i = this->board.find(sourceSquare);
    // If the ChessSquare is not on the board, then the ChessBoard
    // might have been corrupted. Notify client.
    if (i == this->board.end()) {
        cout << "ERROR! Square is not on the board. It is possible "
             << "that this ChessBoard has been corrupted." << endl;
        return false;
    }

    // Return false and notify client if the square is empty.
    if (i->second == nullptr) {
        cout << "There is no piece at position "
             << sourceSquare << "!" << endl;
        return false;
    }
    // Get chess piece at source square.
    ChessPiece* sourcePiece = i->second;

    // If the piece in the source square is not of the same color as
    // the player whose turn it is to play, notify and return false.
    Color sourcePieceColor = sourcePiece->getColor();
    if (sourcePieceColor != this->turn) {
        cout << "It is not " << sourcePieceColor << "'s "
             << "turn to move!" << endl;
        return false;
    }

    // Construct a square for the destination and ensure
    // that it is not the same as the source square.
    ChessSquare destinationSquare = ChessSquare(destination);
    if (sourceSquare == destinationSquare) return false;

    i = this->board.find(destinationSquare);
    if (i == this->board.end()) {
        // TODO: Improve cerr.
        cout << "Invalid move." << endl;
        return false;
    }

    // This stream will be used to inform the client of the move.
    stringstream ss;

    // Get chess piece at destination square. This will
    // be a nullptr if the destination square is empty.
    ChessPiece* destinationPiece = i->second;

    // Ensure that the move is possible given its rules of movement. If
    // so the first bool in the response will be true. The second bool
    // is true if the move is possible, but requires an extra check to
    // make sure there is nothing blocking the path of the move.
    pair<bool, bool> response;
    response = sourcePiece->isPossibleMove(destinationSquare,
                                        destinationPiece);

    // If the move is not possible for that piece, return false.
    if (!response.first) {
        // TODO: Improve output.
        cout << "Invalid move." << endl;
        return false;
    }

    if (this->isValidMove(sourceSquare, destinationSquare,
                          response.second)) {

        this->board[destinationSquare] = sourcePiece;
        this->board[sourceSquare] = nullptr;
        sourcePiece->setSquare(&(i->first));

        // Add information to the stringstream.
        ss << sourcePieceColor << "'s "
           << sourcePiece->getName() << " moves from "
           << sourceSquare << " to " << destinationSquare;
    } else {
        return false;
    }

    // If the destination square contained a piece, then this piece has
    // now been captured. Set it's square property to nullptr.
    if (destinationPiece != nullptr) {
        destinationPiece->setSquare(nullptr);

        // Add information about capture to stringstream.
        ss << " taking " << destinationPiece->getColor()
           << "'s " << destinationPiece->getName();
    }

    // Inform the client about the current move.
    cout << ss.str() << endl;

    // Signal that it is the other player's turn now.
    this->switchTurns();
    return true;
}

// Private Method: isValidMove
// ===========================
// Validate the move from the point of view of the ChessBoard.
bool ChessBoard::isValidMove(const ChessSquare& source,
                             const ChessSquare& destination,
                             bool isPotentiallyBlocked) const {

    // Get the name and colour of the piece being moved
    // in order to include them in messages to the client.
    BoardConstIterator i = this->board.find(source);
    string name = i->second->getName();
    Color color = i->second->getColor();

    // For moves in straight lines spanning more than one square,
    // ensure that there is no piece blocking the way between the
    // source and destination squares.
    if (isPotentiallyBlocked) {
        set<ChessSquare> squares = source.getSquaresBetween(destination);
        set<ChessSquare>::iterator j = squares.begin();
        while (j != squares.end()) {
            i = this->board.find(*j);
            if (i->second != nullptr) {
                // TODO: Remove the following two lines.
                cout << "Invalid move. Path blocked by "
                     << *(i->second) << endl;
                cout << color << "'s " << name << " cannot move to "
                     << destination << "!" << endl;
                return false;
            }
            ++j;
        }
    }

    // Ensure that the King is not left in check.

    return true;
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
        if (count % 8 == 0) {
            int rank = 8 - (count / 8);
            cout << " " << rank << " ";
        }
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
    cout << "   " << "\u250C";
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
    cout << "   " << "\u251C";
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
    cout << "   " << "\u2514";
    for (short int i = 1; i <= 8; ++i) {
        cout << "\u2500\u2500\u2500";
        if (i != 8) cout << "\u2534";
    }
    cout << "\u2518" << endl;
    string files = "ABCDEFGH";
    cout << "  ";
    for (char file : files) {
        cout << "   " << file;
    }
    cout << endl;
}

// Method: getChessSet
// ===================
ChessSet ChessBoard::getChessSet() {
    return this->pieces;
}
