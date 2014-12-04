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
    const ChessSide* side;
    if (color == White) {
        side = this->pieces.getWhites();
    } else {
        side = this->pieces.getBlacks();
    }
    ChessSideConstIterator i = side->begin();
    while (i != side->end()) {
        //TODO: Figure out the pointer stuff.
        ChessPiece* piece = *i;
        ChessSquare square(*((*i)->getSquare()));
        this->board[square] = piece;
        ++i;
    }
}

// Private Method: startGame
// =========================
// This method ensures that the properties of the ChessBoard are
// ready for a game of chess.
void ChessBoard::startGame() {
    this->turn = White;

    // Initialise the members that track
    // the position and state of the kings.
    ChessSquare whiteKingSquare('E', 1);
    ChessSquare blackKingSquare('E', 8);
    this->whiteKing = KingTracker(whiteKingSquare, false);
    this->blackKing = KingTracker(blackKingSquare, false);

    // Notify client that a new game has started.
    cout << "A new chess game is started!" << endl;
}

// Private Method: switchTurns
// ===========================
// This method changes the turn property of the ChessBoard
// to the Color of the player whose turn it is to move next.
void ChessBoard::switchTurns() {
    this->turn = !this->turn;
}

// Public Method: submitMove
// =========================
//
bool ChessBoard::submitMove(string source, string destination) {
    ChessSquare sourceSquare = ChessSquare(source);
    BoardIterator i = this->board.find(sourceSquare);
    // If the source ChessSquare is not on the board, then the
    // ChessBoard might have been corrupted. Notify client.
    if (i == this->board.end()) {
        cout << "ERROR! Source ChessSquare is not on the board. It's "
             << "possible that this ChessBoard has been corrupted."
             << endl;
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
    string sourcePieceName = sourcePiece->getName();
    Color sourcePieceColor = sourcePiece->getColor();

    // If the piece in the source square is not of the same color as
    // the player whose turn it is to play, notify and return false.
    if (sourcePieceColor != this->turn) {
        cout << "It is not " << sourcePieceColor << "'s "
             << "turn to move!" << endl;
        return false;
    }

    // These streams will be used to inform the client of the move.
    stringstream ssSuccess;
    stringstream ssError;

    // If the destination ChessSquare is not on the board, then
    // the ChessBoard might have been corrupted. Notify client.
    ChessSquare destinationSquare = ChessSquare(destination);
    BoardIterator j = this->board.find(destinationSquare);
    if (j == this->board.end()) {
        cout << "ERROR! Source ChessSquare is not on the board. It's "
             << "possible that this ChessBoard has been corrupted."
             << endl;
        return false;
    }

    // This is the default error message for
    // invalid moves caught after this state.
    ssError << sourcePieceColor << "'s " << sourcePieceName
            << " cannot move to " << destinationSquare << "!";

    // Get chess piece at destination square. This will
    // be a nullptr if the destination square is empty.
    ChessPiece* destinationPiece = j->second;

    // Ensure that the move is possible before validating
    // that it does not leave the King in check.
    if (!this->isPossibleMove(sourceSquare, destinationSquare,
                              sourcePiece, destinationPiece)) {
        cout << ssError.str() << endl;
        return false;
    }

    // Prepare scenario before confirming that the move is
    // fully valid, i.e. it does not leave the King in check.
    // Also update KingSquare if applicable.
    this->board[destinationSquare] = sourcePiece;
    this->board[sourceSquare] = nullptr;
    sourcePiece->setSquare(&(j->first));
    updateKingSquare(sourceSquare, destinationSquare);


    // Add information to the success case stringstream.
    ssSuccess << sourcePieceColor << "'s "
              << sourcePieceName << " moves from "
              << sourceSquare << " to " << destinationSquare;

    // If the destination square contained a piece, then this piece has
    // now been captured. Set its square property to nullptr and add
    // information about the capture to the stringstream.
    if (destinationPiece != nullptr) {
        destinationPiece->setSquare(nullptr);
        ssSuccess << " taking " << destinationPiece->getColor()
                  << "'s " << destinationPiece->getName();
    }

    // Ensure that the King is not left in check.
    if (isInCheck(this->turn)) {
        // Return pieces to their original positions.
        // Revert KingSquare if applicable.
        this->board[sourceSquare] = sourcePiece;
        this->board[destinationSquare] = destinationPiece;
        sourcePiece->setSquare(&i->first);
        if (destinationPiece != nullptr) {
            destinationPiece->setSquare(&j->first);
        }
        updateKingSquare(destinationSquare, sourceSquare);
        // TODO: Add info to error stream?
        cout << ssError.str() << endl;
        cout << "This move leaves your King in check." << endl;
        return false;
    }

    // If the opponent is now in check, notify client.
    if (isInCheck(!this->turn)) {
        ssSuccess << endl << !this->turn << " is in check";
    }

    // Inform the client about a successful move.
    cout << ssSuccess.str() << endl;

    // Signal that it is the other player's turn now.
    this->switchTurns();
    return true;
}

// Private Method: isPossibleMove
// ==============================
bool ChessBoard::isPossibleMove(const ChessSquare& sourceSquare,
                                const ChessSquare& destinationSquare,
                                ChessPiece* sourcePiece,
                                ChessPiece* destinationPiece) const {

    // Ensure that the move is possible given its rules of movement. If
    // so the first bool in the response will be true. The second bool
    // is true if the move is possible, but requires an extra check to
    // make sure there is nothing blocking the path of the move.
    pair<bool, bool> response;
    response = sourcePiece->isPossibleMove(destinationSquare,
                                           destinationPiece);
    bool isPossibleMove = response.first;
    bool isPossiblyObstructed = response.second;

    // If the move is not possible for that piece, return false.
    if (!isPossibleMove) {
        return false;
    }

    // If the move is possibly obstructed, check for blocks.
    if (isPossiblyObstructed) {
        if (isObstructed(sourceSquare, destinationSquare)) {
            return false;
        } 
    }

    return true;
}

// Private Method: isObstructed
// ============================
// Ensure that the move is unobstructed.
bool ChessBoard::isObstructed(const ChessSquare& source,
                              const ChessSquare& destination) const {

    // For moves in straight lines spanning more than one square,
    // ensure that there is no piece blocking the way between the
    // source and destination squares.
    set<ChessSquare> squares = source.getSquaresBetween(destination);
    set<ChessSquare>::iterator i = squares.begin();
    while (i != squares.end()) {
        BoardConstIterator j = this->board.find(*i);
        if (j->second != nullptr) {
            // TODO: Remove the following two lines.
            cout << "Invalid move. Path blocked by "
                 << *(j->second) << endl;
            return true;
        }
        ++i;
    }

    return false;
}

// Private Method: updateKingSquare
// ================================
// This method takes two ChessSquare objects and if the first
// contains a King, it updates the ChessSquare in that King's
// KingTracker with the second ChessSquare.
void ChessBoard::updateKingSquare(const ChessSquare& source,
                                  const ChessSquare& destination) {

    if (this->whiteKing.first == source) {
        this->whiteKing.first = destination;
    } else if (this->blackKing.first == source) {
        this->blackKing.first = destination;
    }
}

// Private Method: isInCheck
// =========================
bool ChessBoard::isInCheck(Color color) const {

    // Get this color's King's position.
    ChessSquare kingSquare = this->getKingTracker(color).first;
    BoardConstIterator i = this->board.find(kingSquare);
    ChessPiece* king = i->second;

    // Get all of the opponents pieces that are still on the board,
    // i.e. whose square property is not nullptr and see if any of
    // them can attack this player's King. If so return true.
    const ChessSide* opponents = this->pieces.getSide(!color);
    ChessSideConstIterator j = opponents->begin();
    while (j != opponents->end()) {
        ChessPiece* opponent = *j;
        const ChessSquare* opponentSquare = opponent->getSquare();
        if (opponentSquare != nullptr &&
            this->isPossibleMove(*(opponentSquare),
                                 kingSquare,
                                 opponent, king)) {
            return true;
        }
        ++j;
    }

    return false;
}

// Public Method: resetBoard
// =========================
// This method resets the chess board back to its initial state.
void ChessBoard::resetBoard() {
    this->arrange();
}

// Public Method: getBoard
// =======================
Board ChessBoard::getBoard() const {
    return this->board;
}

// Public Method: getKingTracker
// =============================
KingTracker ChessBoard::getKingTracker(Color color) const {
    switch (color) {
        case White:
            return this->whiteKing;
            break;
        case Black:
            return this->blackKing;
    }

    // Default to returning White's KingTracker.
    return this->whiteKing;
}

// Public Method: getKingStartSquare
// =================================
ChessSquare ChessBoard::getKingStartSquare(Color color) const {
    const string whiteDefault = "E1";
    const string blackDefault = "E8";

    switch (color) {
        case White:
            return ChessSquare(whiteDefault);
            break;
        case Black:
            return ChessSquare(blackDefault);
    }

    // Default to returning the White
    // King's default start square.
    return ChessSquare(whiteDefault);
}

// Public Method: print
// ====================
void ChessBoard::print() const {
    this->printTopLine();
    int count = 0;
    BoardConstIterator i = this->board.begin();
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
void ChessBoard::printTopLine() const {
    cout << "   " << "\u250C";
    for (short int i = 1; i <= 8; ++i) {
        cout << "\u2500\u2500\u2500";
        if (i != 8) cout << "\u252C";
    }
    cout << "\u2510" << endl;
}

// Private Method: printMiddleLine
// ===============================
void ChessBoard::printMiddleLine() const {
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
void ChessBoard::printBottomLine() const {
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
ChessSet ChessBoard::getChessSet() const {
    return this->pieces;
}
