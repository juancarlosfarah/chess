// ==========================================
// File:    ChessBoard.hpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#ifndef CHESS_BOARD_HPP
#define CHESS_BOARD_HPP

#include <iostream>
#include <utility>
#include <map>
using namespace std;

#include "ChessSet.hpp"
#include "ChessPiece.hpp"
#include "ChessSquare.hpp"

// Type: Board & Iterators
// =======================
// The Board is a map of ChessSquare objects to pointers of ChessPiece
// objects used to track the location of the pieces on the board. When
// a square is empty, its corresponding value on the Board is a nullptr.
typedef map<ChessSquare, ChessPiece*> Board;
typedef Board::iterator BoardIterator;
typedef Board::const_iterator BoardConstIterator;

// Class: ChessBoard
// =================
// This class defines the data members and methods associated with the
// ChessBoard object, which brings together the objects needed in order
// to play a game of chess. The ChessBoard is particularly important in
// keeping track of the state of the game through its Board. It also
// receives moves from the client and ensures that they are valid given
// the state of its Board. The ChessBoard is also in charge of notifying
// the client when a game is over, indicating if it ended in checkmate
// or stalemate.
class ChessBoard {

    private:

        ChessSet* pieces;       // Pointer to the set of pieces.
        Board board;            // Map squares to pointers to pieces.
        Color turn;             // Track whose turn it is.
        bool isGameOver;        // Indicate if a game is over.

        // Tracks the position of each King.
        ChessSquare whiteKingSquare;
        ChessSquare blackKingSquare;

        // Method: init
        // ============
        // This method initialises the ChessBoard.
        void init();

        // Method: arrange
        // ===============
        // Arranges the pieces of each side on their respective squares
        // by calling the ChessBoard::arrangeSide method for each side.
        void arrange();

        // Method: arrangeSide
        // ===================
        // Takes a Color and arranges the pieces of that Color on
        // the Board given the square property of each ChessPiece.
        void arrangeSide(Color color);

        // Method: cleanUp
        // ===============
        // This method empties the Board by setting the values
        // of all its ChessSquare entries to nullptr.
        void cleanUp();

        // Method: startGame
        // =================
        // This method ensures that the properties of the ChessBoard
        // are ready for a game of chess and notifies the client.
        void startGame();

        // Method: switchTurns
        // ===================
        // This method changes the turn property of the ChessBoard
        // to the  Color of the player whose turn it is to move next.
        void switchTurns();

        // Method: updateKingSquare
        // ========================
        // This method takes two ChessSquare objects and if the first
        // contains a King, it updates the ChessSquare for that King
        // with the ChessSquare provided as a second parameter.
        void updateKingSquare(ChessSquare& source,
                              ChessSquare& destination);

        // Method: update
        // ==============
        // Takes source and destination ChessPiece pointers, and source
        // and destination ChessSquare objects by reference and updates
        // the state of the Board and the pieces to reflect a move of the
        // ChessPiece at source to the destination ChessSquare. This
        // method is also used in conjunction with ChessBoard::reverse to
        // play out moves to check for check, checkmate and stalemate.
        void update(ChessPiece* sourcePiece,
                    ChessPiece* destinationPiece,
                    ChessSquare& sourceSquare,
                    ChessSquare& destinationSquare);
        
        // Method: reverse
        // ===============
        // Takes source and destination ChessPiece pointers, and source
        // and destination ChessSquare objects by reference and updates
        // the state of the Board and the pieces to reflect reversing a
        // move of the ChessPiece at source to the destination ChessSquare
        // back to its source ChessSquare. This method is used with
        // ChessBoard::update to check for check, checkmate and stalemate.
        void reverse(ChessPiece* sourcePiece,
                     ChessPiece* destinationPiece,
                     ChessSquare& sourceSquare,
                     ChessSquare& destinationSquare);

        // Method: isObstructed
        // ====================
        // Takes two ChessSquare objects by reference and returns a bool
        // indicating if there are any pieces in the squares between them.
        bool isObstructed(ChessSquare& source,
                          ChessSquare& destination) const;

        // Method: isInCheck
        // =================
        // This method takes a Color and returns a bool indicating
        // whether or not the King of the given Color is in check.
        bool isInCheck(Color color) const;

        // Method: hasValidMove
        // ====================
        // Takes a Color and returns a bool indicating if the side of
        // the given Color can make a valid move.
        bool hasValidMove(Color color);

        // Method: isPossibleMove
        // ======================
        // Takes source and destination ChessSquare objects by reference,
        // and source and destination ChessPiece pointers, and returns a
        // bool indicating if the move is possible given the rules of
        // movement for the source piece and any possible obstructions.
        // Returning true doesn't mean that this move is valid, as it
        // doesn't ensure that the move doesn't leave its King in check.
        bool isPossibleMove(ChessSquare& sourceSquare,
                            ChessSquare& destinationSquare,
                            ChessPiece* sourcePiece,
                            ChessPiece* destinationPiece) const;

        // Method: isValidMove
        // ===================
        // Takes source and destination ChessSquare objects, source and
        // destination ChessPiece pointers, a stringstream and a bool,
        // and returns a bool indicating if the move is valid. The
        // stringstream is used to insert messages that might be later
        // on printed out to the client. If the isQuiet argument is
        // true, any errors are silenced. That is used when playing out
        // moves when checking for check, checkmate and stalemate.
        bool isValidMove(ChessSquare sourceSquare,
                         ChessSquare destinationSquare,
                         ChessPiece* sourcePiece,
                         ChessPiece* destinationPiece,
                         stringstream& ssSuccess, bool isQuiet);

        // Method: printTopLine
        // ====================
        // This method prints the top line of the ChessBoard.
        void printTopLine() const;

        // Method: printMiddleLine
        // =======================
        // This method prints one of the lines between
        // the middle rows of the ChessBoard.
        void printMiddleLine() const;

        // Method: printBottomLine
        // =======================
        // This method prints the bottom line of the ChessBoard.
        void printBottomLine() const;

    public:

        // Constructor: Default
        // ====================
        ChessBoard();

        // Destructor:
        // ===========
        virtual ~ChessBoard();

        // Method: submitMove
        // ==================
        // Takes a source string and a destination string, presumably
        // with chess coordinates of the form file followed by rank, e.g.
        // "A1", "H4" and returns a bool indicating if the move is valid.
        bool submitMove(string source, string destination);

        // Method: resetBoard
        // ==================
        // This method resets the chess board back to its initial state.
        void resetBoard();
   
        // Method: getBoard
        // ================
        // This method returns the board property of the ChessBoard.
        Board getBoard() const;

        // Method: getKingSquare
        // =====================
        // This method takes a Color and returns the ChessSquare
        // where the King of that Color is currently located.
        const ChessSquare getKingSquare(Color color) const;

        // Method: getKingStartSquare
        // ==========================
        // This method takes a Color and returns the ChessSquare
        // where the King of that Color starts by default.
        const ChessSquare getKingStartSquare(Color color) const;

        // Method: print
        // =============
        // This method prints out this ChessBoard in a human-friendly
        // manner, showing all of the pieces that are still in play.
        void print() const;

};

#endif
