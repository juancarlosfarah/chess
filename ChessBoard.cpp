#include <iomanip>
#include <sstream>
using namespace std;

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
    for (int i = 'A'; i <= 'H'; ++i) {
        for (int rank = 1; rank <= 8; ++rank) {
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

    // If the game was over, it isn't anymore!
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
// This method takes a source string and a destination string, presumably
// with chess coordinates of the form file letter followed by rank number,
// e.g. "A1", "H4" and returns a bool indicating if the move is valid.
bool ChessBoard::submitMove(string source, string destination) {

    // Cannot submit any more moves if the game is over. Notify client.
    if (this->isGameOver) {
        cout << "Game is over. No more moves are allowed." << endl;
        return false;
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

        return false;
    }

    // If the source ChessSquare is valid but not on the board, then
    // the ChessBoard might have been corrupted. Notify client.
    if (i == this->board.end()) {
        cout << "ERROR! Source ChessSquare is not on the board. It's "
             << "possible that this ChessBoard has been corrupted."
             << endl;
        return false;
    }

    // Get ChessSquare and ChessPiece at provided source.
    // Return false and notify client if the square is empty.
    ChessSquare sourceSquare = i->first;
    ChessPiece* sourcePiece = i->second;
    if (i->second == nullptr) {
        cout << "There is no piece at position "
             << sourceSquare << "!" << endl;
        return false;
    }

    // If the piece in the source square is not of the same color as
    // the player whose turn it is to play, notify and return false.
    Color sourcePieceColor = sourcePiece->getColor();
    if (sourcePieceColor != this->turn) {
        cout << "It is not " << sourcePieceColor << "'s "
             << "turn to move!" << endl;
        return false;
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

        return false;
    }

    // If the destination ChessSquare is valid but not on the board,
    // then the ChessBoard might have been corrupted. Notify client.
    if (j == this->board.end()) {
        cout << "ERROR! Source ChessSquare is not on the board. It's "
             << "possible that this ChessBoard has been corrupted."
             << endl;
        return false;
    }

    // Get ChessSquare and ChessPiece at destination square. The
    // second will be a nullptr if the destination square is empty.
    ChessSquare destinationSquare = j->first;
    ChessPiece* destinationPiece = j->second;

    // This stream will be used to inform the client of a valid move.
    stringstream ssSuccess;

    // Ensure the move is valid.
    if (!this->isValidMove(sourceSquare, destinationSquare, sourcePiece,
                           destinationPiece, ssSuccess, false)) {
        return false;
    }

    // If the opponent is now in check or checkmate, or if the game has
    // ended in stalemate, notify the client. If the game has ended, set
    // the appropriate flags in order to prevent further moves.
    pair<bool, ChessSquare> response = this->isInCheck(!this->turn);
    bool isInCheck = response.first;
    ChessSquare checkSquare = response.second;
    if (isInCheck) {
        ssSuccess << endl << !this->turn << " is in check";
        if (this->isInCheckmate(!this->turn, checkSquare)) {
            ssSuccess << "mate";
            this->isGameOver = true;
        }
    } else {
        if (this->isStalemate(!this->turn)) {
            ssSuccess << endl << !this->turn << " cannot move. "
                      << "Stalemate!" << endl;
            this->isGameOver = true;
        }
    }

    // Inform the client about a successful move.
    cout << ssSuccess.str() << endl;

    // Signal that it's the other player's turn now if the game goes on.
    if (!this->isGameOver) this->switchTurns();

    return true;
}

// Private Method: isInCheckmate
// =============================
// This method takes a Color and a ChessSquare and returns a
// bool indicating if the side of that Color is in checkmate.
bool ChessBoard::isInCheckmate(Color color, const ChessSquare& square) {

    ChessSquare kingSquare = this->getKingSquare(color);
    BoardConstIterator k;
    k = this->board.find(kingSquare);
    ChessPiece* king = k->second;
    
    // This stringstream is used to consume output and then silence it.
    stringstream ss;

    // TODO: Delete.
    // cout << "Attack from: " << square << endl;

    // If the King can move to any adjacent square, it isn't checkmate.
    set<ChessSquare> squares = kingSquare.getAdjacentSquares();
    set<ChessSquare>::iterator i = squares.begin();
    while (i != squares.end()) {
        ChessSquare destinationSquare = *i;
        k = this->board.find(destinationSquare);
        ChessPiece* destinationPiece = k->second;
        if (isValidMove(kingSquare, destinationSquare, king,
                        destinationPiece, ss, true)) {
            // TODO: Delete.
            // cout << "Escape from " << kingSquare << " to "
            //      << destinationSquare << endl;
            return false;
        }
        ++i;
    }

    // If the square is adjacent, or the attacking piece is a Knight,
    // then there is no need to check for obstructing its path, as it's
    // not possible. If the path cannot be blocked, then only way to avoid
    // checkmate is if the opponent's attacking piece can be captured.
    // Thus include the attacking square in the set of blockSquares.
    set<ChessSquare> blockSquares;
    if (!square.isAdjacent(kingSquare) &&
        !square.isKnightHopFrom(kingSquare)) {
        
        blockSquares = square.getSquaresBetween(kingSquare);
    }
    blockSquares.insert(square);

    // Iterate through the squares that might block the check and
    // see if any of the pieces of this Color can reach them.
    i = blockSquares.begin();
    while (i != blockSquares.end()) {
        ChessSquare destinationSquare = *i;
        
        // TODO: Delete
        //cout << "DSquare: " << destinationSquare << endl;
        
        k = this->board.find(destinationSquare);
        ChessPiece* destinationPiece = k->second;
        const ChessSide* team = this->pieces->getSide(color);
        ChessSideConstIterator j = team->begin();
        while (j != team->end()) {

            // Don't consider teammates who have already been
            // captured, i.e. have nullptr in their square property.
            ChessPiece* teammate = *j;
            ChessSquare* teammateSquare = teammate->getSquare();
            
            // TODO: Delete
            //cout << *teammate << " at "; 
            //if (teammateSquare != nullptr) cout << *teammateSquare <<
            //    endl;

            if (teammateSquare != nullptr &&
                this->isValidMove(*teammateSquare, destinationSquare,
                                  teammate, destinationPiece, ss, true)) {
            // TODO: Delete.
            //cout << "Blocked by " << *teammate << " from "
            //   << *teammateSquare << " to " << destinationSquare << endl;
                return false;
            }
            ++j;
        }
        ++i;
    }

    return true;
}

// Private Method: isStalemate
// ===========================
// Takes a Color and returns true if no pieces of that Color can make a
// valid move. When used with the Color of the side that is up next,
// this means that the game has ended in stalemate.
bool ChessBoard::isStalemate(Color color) {

    // Used to suppress output to client as this check is silent.
    stringstream ss;

    // Iterate through all of the pieces of the given color and
    // check if any of them can move. If so, then it's not stalemate.
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
                    return false;
                }
                ++j;
            }
        }
        ++i;
    }
    return true;
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
    pair<bool, ChessSquare> response = this->isInCheck(sourcePieceColor);
    bool isInCheck = response.first;
    if (isInCheck) {
        // Return pieces to their original positions.
        this->reverse(sourcePiece, destinationPiece,
                      sourceSquare, destinationSquare);
        if (!isQuiet) {
            cout << ssErr.str() << endl;
            // TODO: Add info to error stream?
            //cout << "This move leaves your King in check." << endl;
        }
        return false;
    }
    if (isQuiet) {
        //TODO: Delete.
        //cout << "Reversing pieces." << endl;
        
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

    // TODO: Playing Out.
    //cout << "Playing Out: " << *sourcePiece;
    //cout << "  From: " << sourceSquare; 
    //cout << "  To: " << destinationSquare << endl;
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
    // TODO: Delete.
    //cout << "Reversing: " << *sourcePiece;
    //cout << "  Back From: " << destinationSquare; 
    //cout << "  Back To: " << sourceSquare << endl;
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
            // TODO: Remove the following two lines.
            //cout << "Invalid move. Path blocked by "
            //     << *(j->second) << endl;
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
// This method takes a Color and returns a pair<bool, ChessSquare>
// with the first param indicating if the King of the given Color is in
// check and if so, with the second param containing a ChessSquare from
// which the King is being attacked. Note that if the King is not in
// check, the second param will be the King's current ChessSquare.
pair<bool, ChessSquare> ChessBoard::isInCheck(Color color) const {

    // Get this color's King's position.
    ChessSquare kingSquare = this->getKingSquare(color);
    BoardConstIterator i = this->board.find(kingSquare);
    ChessPiece* king = i->second;

    // Define default return value. If the King is not in check,
    // return its square as the second parameter in the response.
    pair<bool, ChessSquare> rvalue(false, kingSquare);

    // Get all of the opponent's pieces that are still on the board,
    // i.e. whose square property is not nullptr, and see if any of
    // them can attack this player's King. If so return true.
    const ChessSide* opponents = this->pieces->getSide(!color);
    ChessSideConstIterator j = opponents->begin();
    while (j != opponents->end()) {
        ChessPiece* opponent = *j;
        ChessSquare* opponentSquare = opponent->getSquare();
        // TODO: Debug
        //cout << *opponent << "   " << *opponentSquare << endl;
        if (opponentSquare != nullptr &&
            this->isPossibleMove(*opponentSquare, kingSquare,
                                 opponent, king)) {
            //TODO: Debug
            //cout << *opponent << *opponentSquare << endl;
            rvalue.first = true;
            rvalue.second = *opponentSquare;
            return rvalue;
        }
        ++j;
    }

    return rvalue;
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
// TODO: Delete.
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

    // These are the default starting squares.
    const string whiteDefault = "E1";
    const string blackDefault = "E8";

    switch (color) {
        case White:
            return ChessSquare(whiteDefault);
        case Black:
            return ChessSquare(blackDefault);
    }

    // Default to returning White's King start ChessSquare,
    // but issue a warning to the client just in case.
    cout << "WARNING! Color argument to ChessBoard::getKingSquare did "
         << "not match Black or White. Check for possible corruption."
         << endl;
    return ChessSquare(whiteDefault);
}

// Public Method: print
// ====================
// This method prints out this ChessBoard in a human-friendly manner.
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
