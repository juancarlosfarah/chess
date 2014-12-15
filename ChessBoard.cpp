// ==========================================
// File:    ChessBoard.cpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#include <iomanip>
#include <sstream>
using namespace std;

#include "Settings.hpp"
#include "ChessBoard.hpp"

// Constructor: Default
// ====================
// This default constructor calls methods that initialise the ChessBoard
// object's properties, arrange the pieces on the board and start the
// game so that it is ready to receive moves.
ChessBoard::ChessBoard() {
    this->init();
    this->arrange();
    this->startGame();
}

// Destructor:
// ===========
ChessBoard::~ChessBoard() {

    // If this ChessBoard has a ChessSet, delete it before destructing.
    if (this->pieces != nullptr) delete this->pieces;
    this->pieces = nullptr;
}

// Private Method: init
// ====================
// This method initialises the ChessBoard.
void ChessBoard::init() {

    // Create a new ChessSet for this Board.
    this->pieces = new ChessSet();

    // Initialise the Board so that each entry corresponds to a
    // empty ChessSquare. Signal that the Board is empty by assigning
    // all squares in the map a nullptr as a value.
    for (int i = LEFTMOST_FILE; i <= RIGHTMOST_FILE; ++i) {
        for (int rank = BOTTOM_RANK; rank <= TOP_RANK; ++rank) {
            char file = static_cast<char>(i);

            // Prevent inserting corrupted ChessSquare objects by
            // throwing an exception if the coordinates are invalid.
            try {
                ChessSquare square(file, rank);
                pair<ChessSquare, ChessPiece*> position(square, nullptr);
                this->board.insert(position);
            } catch (InvalidCoordinatesException& e) {
                cerr << "ERROR! Caught InvalidCoordinatesException "
                     << "when calling ChessSquare constructor with "
                     << "file=" << file << " and rank=" << rank << " "
                     << "in ChessBoard::init." << endl;
            }
        }
    }
}

// Private Method: cleanUp
// =======================
// Empties the Board by setting the values of
// all its ChessSquare entries to nullptr.
void ChessBoard::cleanUp() {
    BoardIterator i = this->board.begin();
    while (i != this->board.end()) {
        i->second = nullptr;
        ++i;
    }
}

// Private Method: arrange
// =======================
// Arranges the pieces of each side on their respective squares
// by calling the ChessBoard::arrangeSide method for each side.
void ChessBoard::arrange() {
    this->arrangeSide(White);
    this->arrangeSide(Black);
}

// Private Method: arrangeSide
// ===========================
// This method takes a Color and arranges the pieces of that colour
// on the Board given the square property of each ChessPiece.
void ChessBoard::arrangeSide(Color color) {

    // Get the respective side.
    const ChessSide* side;
    if (color == White) {
        side = this->pieces->getWhites();
    } else {
        side = this->pieces->getBlacks();
    }

    // Iterate through all the pieces of that Color and
    // place them onto their respecive square on the board.
    ChessSideConstIterator i = side->begin();
    while (i != side->end()) {
        ChessPiece* piece = *i;
        ChessSquare* squarePtr = piece->getSquare();
        ChessSquare square = *squarePtr;
        this->board[square] = piece;
        ++i;
    }
}

// Private Method: startGame
// =========================
// This method ensures that the properties of the ChessBoard
// are ready for a game of chess and notifies the client.
void ChessBoard::startGame() {

    // Reset isGameOver bool.
    this->isGameOver = false;

    // Default is for White to play first.
    this->turn = White;

    // Get the squares containing each King.
    this->whiteKingSquare = this->getKingStartSquare(White);
    this->blackKingSquare = this->getKingStartSquare(Black);

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
// Takes a source string and a destination string, presumably
// with chess coordinates of the form file followed by rank,
// e.g. "A1", and persists it on the Board if the move is valid.
void ChessBoard::submitMove(string source, string destination) {

    // Cannot submit any more moves if the game is over. Notify client.
    if (this->isGameOver) {
        cout << "Game is over. No more moves are allowed." << endl;
        return;
    }

    // Get the location of the source ChessSquare on the Board,
    // but make sure to catch the exception if the source parameter
    // does not correspond to a valid square.
    BoardIterator i;
    try {
        ChessSquare square(source);
        i = this->board.find(square);
    } catch (InvalidCoordinatesException& e) {
        cout << "ERROR! Caught InvalidCoordinatesException when calling "
             << "ChessSquare constructor for source ChessSquare with "
             << "input=" << source << " in ChessBoard::submitMove."
             << endl;
        return;
    }

    // If the source ChessSquare is valid but not on the board, then
    // the ChessBoard might have been corrupted. Notify client.
    if (i == this->board.end()) {
        cout << "ERROR! Source ChessSquare is not on the board. It's "
             << "possible that this ChessBoard has been corrupted."
             << endl;
        return;
    }

    // Get ChessSquare and ChessPiece at provided source.
    // Return false and notify client if the square is empty.
    ChessSquare sourceSquare = i->first;
    ChessPiece* sourcePiece = i->second;
    if (i->second == nullptr) {
        cout << "There is no piece at position "
             << sourceSquare << "!" << endl;
        return;
    }

    // If the piece in the source square is not of the same color as
    // the player whose turn it is to play, notify and return false.
    Color sourcePieceColor = sourcePiece->getColor();
    if (sourcePieceColor != this->turn) {
        cout << "It is not " << sourcePieceColor << "'s "
             << "turn to move!" << endl;
        return;
    }

    // Get the location of the destination ChessSquare on the Board,
    // but make sure to catch the exception if the destination parameter
    // does not correspond to a valid square.
    BoardIterator j;
    try {
        ChessSquare square(destination);
        j = this->board.find(square);
    } catch (InvalidCoordinatesException& e) {
        cout << "ERROR! Caught InvalidCoordinatesException when calling "
             << "ChessSquare constructor for destination ChessSquare with "
             << "input=" << destination << " in ChessBoard::submitMove."
             << endl;
        return;
    }

    // If the destination ChessSquare is valid but not on the board,
    // then the ChessBoard might have been corrupted. Notify client.
    if (j == this->board.end()) {
        cout << "ERROR! Source ChessSquare is not on the board. It's "
             << "possible that this ChessBoard has been corrupted."
             << endl;
        return;
    }

    // Get ChessSquare and ChessPiece at destination square. The
    // second will be a nullptr if the destination square is empty.
    ChessSquare destinationSquare = j->first;
    ChessPiece* destinationPiece = j->second;

    // This stream will be used to inform the client of a valid move.
    stringstream ssSuccess;

    // Ensure the move is valid, else return.
    if (!this->isValidMove(sourceSquare, destinationSquare, sourcePiece,
                           destinationPiece, ssSuccess, false)) {
        return;
    }

    // If the opponent is now in check or checkmate, or if the game has
    // ended in stalemate, notify the client. If the game has ended, set
    // the appropriate flags in order to prevent further moves.
    if (this->isInCheck(!this->turn)) {

        // Inform client that opponent is in check.
        ssSuccess << endl << !this->turn << " is in check";

        // If opponent is in check and can't move, it is checkmate.
        if (!this->hasValidMove(!this->turn)) {
            ssSuccess << "mate";
            this->isGameOver = true;
        }

    } else {

        // If opponent isn't in check and can't move, it is stalemate.
        if (!this->hasValidMove(!this->turn)) {
            ssSuccess << endl << !this->turn << " cannot move. "
                      << "Stalemate!" << endl;
            this->isGameOver = true;
        }

    }

    // Inform the client about a successful move.
    cout << ssSuccess.str() << endl;

    // Signal that it's the other player's turn now if the game goes on.
    if (!this->isGameOver) this->switchTurns();

}

// Private Method: hasValidMove
// ============================
// Takes a Color and returns true if it can make a valid move.
bool ChessBoard::hasValidMove(Color color) {

    // Used to suppress output to client as this check is silent.
    stringstream ss;

    // Iterate through all of the pieces of the given
    // color and check if any of them can move.
    const ChessSide* side = this->pieces->getSide(color);
    ChessSideConstIterator i = side->begin();
    while (i != side->end()) {
        ChessPiece* sourcePiece = *i;
        ChessSquare* sourceSquarePtr = sourcePiece->getSquare();

        // Do not consider pieces that have already been captured.
        if (sourceSquarePtr != nullptr) {
            ChessSquare sourceSquare = *sourceSquarePtr;
            BoardIterator j = this->board.begin();
            while (j != this->board.end()) {
                ChessSquare destinationSquare = j->first;
                ChessPiece* destinationPiece = j->second;
                if (isValidMove(sourceSquare, destinationSquare,
                                sourcePiece, destinationPiece, ss, true)){
                    return true;
                }
                ++j;
            }
        }
        ++i;
    }
    return false;
}


// Private Method: isValidMove
// ===========================
// Takes source and destination ChessSquare objects, source and destination
// ChessPiece pointers, a stringstream and a bool, and returns a bool
// indicating if the move is valid. The stringstream is used to insert
// messages that might be later on printed out to the client. If the
// isQuiet argument is true, any errors are silenced. That is used when
// playing out moves when checking for check, checkmate and stalemate.
bool ChessBoard::isValidMove(ChessSquare sourceSquare,
                             ChessSquare destinationSquare,
                             ChessPiece* sourcePiece,
                             ChessPiece* destinationPiece,
                             stringstream& ssSuccess,
                             bool isQuiet) {

    string sourcePieceName = sourcePiece->getName();
    Color sourcePieceColor = sourcePiece->getColor();

    // This is the default error message for invalid moves caught.
    stringstream ssErr;
    ssErr << sourcePieceColor << "'s " << sourcePieceName
          << " cannot move to " << destinationSquare << "!";

    // Ensure that the move is possible before validating
    // that it does not leave the King in check.
    if (!this->isPossibleMove(sourceSquare, destinationSquare,
                              sourcePiece, destinationPiece)) {
        if (!isQuiet) cout << ssErr.str() << endl;
        return false;
    }

    // Prepare scenario before confirming that the move is
    // fully valid, i.e. it does not leave the King in check.
    // Also update KingSquare if applicable.
    this->update(sourcePiece, destinationPiece,
                 sourceSquare, destinationSquare);

    // Add information to the success case stringstream.
    if (!isQuiet) {
        ssSuccess << sourcePieceColor << "'s "
                  << sourcePieceName << " moves from "
                  << sourceSquare << " to " << destinationSquare;
    }

    // If the destination square contained a piece, add
    // information about the capture to the stringstream.
    if (destinationPiece != nullptr && !isQuiet) {
        ssSuccess << " taking " << destinationPiece->getColor()
                  << "'s " << destinationPiece->getName();
    }

    // Ensure that the King is not left in check.
    if (this->isInCheck(sourcePieceColor)) {
        // Return pieces to their original positions.
        this->reverse(sourcePiece, destinationPiece,
                      sourceSquare, destinationSquare);
        if (!isQuiet) {
            cout << ssErr.str() << endl;
        }
        return false;
    }
    if (isQuiet) {
        // Return pieces to their original positions.
        this->reverse(sourcePiece, destinationPiece,
                      sourceSquare, destinationSquare);
    }
    
    return true;
}

// Private Method: update
// ======================
// This method takes source and destination ChessPiece pointers, and
// source and destination ChessSquare objects by reference and updates
// the state of the Board and the ChessPiece objects to reflect a move
// of the ChessPiece at source to the destination ChessSquare. This
// method is also used in conjunction with ChessBoard::revers, to play
// out moves in order to check for check, checkmate and stalemate.
void ChessBoard::update(ChessPiece* sourcePiece,
                        ChessPiece* destinationPiece,
                        ChessSquare& sourceSquare,
                        ChessSquare& destinationSquare) {

    this->board[destinationSquare] = sourcePiece;
    this->board[sourceSquare] = nullptr;
    sourcePiece->setSquare(destinationSquare);
    if (destinationPiece != nullptr) {
        destinationPiece->setSquare(nullptr);
    }
    updateKingSquare(sourceSquare, destinationSquare);
}

// Private Method: reverse
// =======================
// Takes source and destination ChessPiece pointers, and source
// and destination ChessSquare objects by reference and updates
// the state of the Board and the pieces to reflect reversing a
// move of the ChessPiece at source to the destination ChessSquare
// back to its source ChessSquare. This method is used with
// ChessBoard::update to check for check, checkmate and stalemate.
void ChessBoard::reverse(ChessPiece* sourcePiece,
                         ChessPiece* destinationPiece,
                         ChessSquare& sourceSquare,
                         ChessSquare& destinationSquare) {

    this->board[sourceSquare] = sourcePiece;
    this->board[destinationSquare] = destinationPiece;
    sourcePiece->setSquare(sourceSquare);
    if (destinationPiece != nullptr) {
        destinationPiece->setSquare(destinationSquare);
    }
    updateKingSquare(destinationSquare, sourceSquare);
}


// Private Method: isPossibleMove
// ==============================
// This method takes a source and a destination ChessSquare object by
// reference, and a source and a destination ChessPiece pointer, and
// returns a bool indicating if the move is possible given the rules
// of movement for the source piece and any possible obstructions.
// Note that returning true does not mean that this move is valid, as
// it does not ensure that the move does not leave its King in check.
bool ChessBoard::isPossibleMove(ChessSquare& sourceSquare,
                                ChessSquare& destinationSquare,
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
        if (this->isObstructed(sourceSquare, destinationSquare)) {
            return false;
        } 
    }

    return true;
}

// Private Method: isObstructed
// ============================
// This method takes two ChessSquare objects by reference and return a
// bool indicating if there are any pieces in the squares between them.
bool ChessBoard::isObstructed(ChessSquare& source,
                              ChessSquare& destination) const {

    // For moves in straight lines spanning more than one square, ensure
    // that there's no obstruction between the source and destination.
    set<ChessSquare> squares = source.getSquaresBetween(destination);
    set<ChessSquare>::iterator i = squares.begin();
    while (i != squares.end()) {
        BoardConstIterator j = this->board.find(*i);
        if (j->second != nullptr) {
            return true;
        }
        ++i;
    }
    return false;
}

// Private Method: updateKingSquare
// ================================
// This method takes two ChessSquare objects and if the first
// contains a King, it updates the ChessSquare for that King
// with the ChessSquare provided as a second parameter.
void ChessBoard::updateKingSquare(ChessSquare& source,
                                  ChessSquare& destination) {

    if (this->whiteKingSquare == source) {
        this->whiteKingSquare = destination;
    } else if (this->blackKingSquare == source) {
        this->blackKingSquare = destination;
    }
}

// Private Method: isInCheck
// =========================
// This method takes a Color and returns a bool indicating
// whether or not the King of the given Color is in check.
bool ChessBoard::isInCheck(Color color) const {

    // Get this color's King's position.
    ChessSquare kingSquare = this->getKingSquare(color);
    BoardConstIterator i = this->board.find(kingSquare);
    ChessPiece* king = i->second;

    // Get all of the opponent's pieces that are still on the board,
    // i.e. whose square property is not nullptr, and see if any of
    // them can attack this player's King. If so return true.
    const ChessSide* opponents = this->pieces->getSide(!color);
    ChessSideConstIterator j = opponents->begin();
    while (j != opponents->end()) {
        ChessPiece* opponent = *j;
        ChessSquare* opponentSquare = opponent->getSquare();
        if (opponentSquare != nullptr &&
            this->isPossibleMove(*opponentSquare, kingSquare,
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

    // Reset pieces to a fresh ChessSet
    delete this->pieces;
    this->pieces = new ChessSet();

    // Clean up the board
    this->cleanUp();
    this->arrange();
    this->startGame();
}

// Public Method: getBoard
// =======================
// This method returns the board property of the ChessBoard.
Board ChessBoard::getBoard() const {
    return this->board;
}

// Public Method: getKingSquare
// ============================
// This method takes a Color and returns the ChessSquare
// where the King of that Color is currently located.
const ChessSquare ChessBoard::getKingSquare(Color color) const {

    switch (color) {
        case White:
            return this->whiteKingSquare;
        case Black:
            return this->blackKingSquare;
    }

    // Default to returning White's King ChessSquare,
    // but issue a warning to the client just in case.
    cout << "WARNING! Color argument to ChessBoard::getKingSquare did "
         << "not match Black or White. Check for possible corruption."
         << endl;
    return this->whiteKingSquare;
}

// Public Method: getKingStartSquare
// =================================
// This method takes a Color and returns the ChessSquare where the
// King of that Color starts by default.
const ChessSquare ChessBoard::getKingStartSquare(Color color) const {

    switch (color) {
        case White:
            return ChessSquare(WHITE_KING_SQUARE);
        case Black:
            return ChessSquare(BLACK_KING_SQUARE);
    }

    // Default to returning White's King start ChessSquare,
    // but issue a warning to the client just in case.
    cout << "WARNING! Color argument to ChessBoard::getKingSquare did "
         << "not match Black or White. Check for possible corruption."
         << endl;
    return ChessSquare(WHITE_KING_SQUARE);
}

// Public Method: print
// ====================
// This method prints out this ChessBoard in a human-friendly manner.
void ChessBoard::print() const {

    // Output a top line and prepare to iterate.
    this->printTopLine();
    int count = 0;
    BoardConstIterator i = this->board.begin();
    while (i != this->board.end()) {

        // At the beginning of each rank output the rank number.
        if (count % SIDE_LEN == 0) {
            int rank = SIDE_LEN - (count / SIDE_LEN);
            cout << SMALL_SPACE << rank << SMALL_SPACE;
        }

        // Output each square with its piece, if any.
        cout << VERTICAL_BAR << SMALL_SPACE;
        if (i->second != nullptr) {
            cout << *(i->second);
        } else {
            cout << SMALL_SPACE;
        }
        cout << SMALL_SPACE;
        ++count;

        // Between each row output a middle line.
        if (count % SIDE_LEN == 0 && count < NUM_SQUARES) {
            this->printMiddleLine();
        }
        ++i;
    }

    // Output the bottom line, closing the board.
    this->printBottomLine();
}


// Private Method: printTopLine
// ============================
// This method prints the top line of the ChessBoard.
void ChessBoard::printTopLine() const {
    cout << LARGE_SPACE << TOP_LEFT_CORNER;
    for (short int i = 1; i <= SIDE_LEN; ++i) {
        cout << LONG_BAR;
        if (i != SIDE_LEN) cout << TOP_JOIN;
    }
    cout << TOP_RIGHT_CORNER << endl;
}

// Private Method: printMiddleLine
// ===============================
// This method prints one of the lines between
// the middle rows of the ChessBoard.
void ChessBoard::printMiddleLine() const {
    cout << VERTICAL_BAR << endl;
    cout << LARGE_SPACE << LEFT_JOIN;
    for (short int i = 1; i <= SIDE_LEN; ++i) {
        cout << LONG_BAR;
        if (i != SIDE_LEN) cout << INNER_JOIN;
    }
    cout << RIGHT_JOIN << endl;
}

// Private Method: printBottomLine
// ===============================
// This method prints the bottom line of the ChessBoard.
void ChessBoard::printBottomLine() const {

    // Close the bottom rank with the appropriate characters.
    cout << VERTICAL_BAR << endl;
    cout << LARGE_SPACE << BOTTOM_LEFT_CORNER;
    for (short int i = 1; i <= SIDE_LEN; ++i) {
        cout << LONG_BAR;
        if (i != 8) cout << BOTTOM_JOIN;
    }
    cout << BOTTOM_RIGHT_CORNER << endl;

    // Output the letter of each file below the board.
    cout << MEDIUM_SPACE;
    for (int i = 0; i < SIDE_LEN; ++i) {
        char file = LEFTMOST_FILE + i;
        cout << LARGE_SPACE << file;
    }
    cout << endl;
}
