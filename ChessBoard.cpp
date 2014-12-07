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

    // Get Set of ChessPieces
    this->pieces = new ChessSet();

    for (int i = 65; i <= 72; ++i) {
        for (int rank = 1; rank <= 8; ++rank) {
            char file = static_cast<char>(i);
            try {
                Position position(ChessSquare(file, rank), nullptr);
                this->board.insert(position);
            } catch (InvalidCoordinatesException& e) {
                cerr << "ERROR! Caught InvalidCoordinatesException "
                     << "when calling ChessBoard::init()." << endl;
            }
        }
    }
}

// Private Method: cleanUp
// =======================
void ChessBoard::cleanUp() {
    BoardIterator i = this->board.begin();
    while (i != this->board.end()) {
        i->second = nullptr;
        ++i;
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
        side = this->pieces->getWhites();
    } else {
        side = this->pieces->getBlacks();
    }
    ChessSideConstIterator i = side->begin();
    while (i != side->end()) {
        //TODO: Figure out the pointer stuff.
        ChessPiece* piece = *i;
        this->board[*(piece->getSquare())] = piece;
        ++i;
    }
}

// Private Method: startGame
// =========================
// This method ensures that the properties of the ChessBoard are
// ready for a game of chess.
void ChessBoard::startGame() {
    this->turn = White;

    // Get pointers to the squares for the kings on the board.
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
//
bool ChessBoard::submitMove(string source, string destination) {

    BoardIterator i = this->board.find(ChessSquare(source));

    // If the source ChessSquare is not on the board, then the
    // ChessBoard might have been corrupted. Notify client.
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

    // If the destination ChessSquare is not on the board, then
    // the ChessBoard might have been corrupted. Notify client.
    BoardIterator j = this->board.find(ChessSquare(destination));
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

    // If the opponent is now in check, notify client.
    pair<bool, ChessSquare> response = this->isInCheck(!this->turn);
    bool isInCheck = response.first;
    ChessSquare checkSquare = response.second;
    if (isInCheck) {
        ssSuccess << endl << !this->turn << " is in check";
        if (this->isInCheckmate(!this->turn, checkSquare)) {
            ssSuccess << "mate";
        }
    }

    // Inform the client about a successful move.
    cout << ssSuccess.str() << endl;

    // Signal that it is the other player's turn now.
    this->switchTurns();
    return true;
}

// Private Method: isInCheckmate
// =============================
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
    // not possible.
    // If the path cannot be blocked, then only way to avoid checkmate
    // is if the opponent's attacking piece can be captured.
    set<ChessSquare> blockSquares;
    if (!square.isAdjacent(kingSquare) &&
        !square.isKnightHopFrom(kingSquare)) {
        
        blockSquares = square.getSquaresBetween(kingSquare);
    }
    blockSquares.insert(square);
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

// Private Method: isValidMove
// ===========================
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
            cout << "This move leaves your King in check." << endl;
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
        if (isObstructed(sourceSquare, destinationSquare)) {
            return false;
        } 
    }

    return true;
}

// Private Method: isObstructed
// ============================
// Ensure that the move is unobstructed.
bool ChessBoard::isObstructed(ChessSquare& source,
                              ChessSquare& destination) const {

    // For moves in straight lines spanning more than one square,
    // ensure that there is no piece blocking the way between the
    // source and destination squares.
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
// with the ChessSquare provided as a second argument.
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
pair<bool, ChessSquare> ChessBoard::isInCheck(Color color) const {
    pair<bool, ChessSquare> rvalue;

    // Get this color's King's position.
    ChessSquare kingSquare = this->getKingSquare(color);
    BoardConstIterator i = this->board.find(kingSquare);
    ChessPiece* king = i->second;

    // Get all of the opponents pieces that are still on the board,
    // i.e. whose square property is not nullptr and see if any of
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

    // If the King is not in Check return its square as the second
    // parameter in the response.
    rvalue.first = false;
    rvalue.second = kingSquare;
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
Board ChessBoard::getBoard() const {
    return this->board;
}

// Public Method: getKingSquare
// ============================
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
const ChessSquare ChessBoard::getKingStartSquare(Color color) const {
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
    return *(this->pieces);
}
