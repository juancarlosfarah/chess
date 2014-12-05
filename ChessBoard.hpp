#ifndef CHESS_BOARD_HPP
#define CHESS_BOARD_HPP

#include <iostream>
#include <utility>
#include <map>
using namespace std;

#include "ChessSet.hpp"
#include "ChessPiece.hpp"
#include "ChessSquare.hpp"

// Type: Position
// ==============
typedef pair<ChessSquare, ChessPiece*> Position;
typedef map<ChessSquare, ChessPiece*> Board;
typedef Board::iterator BoardIterator;
typedef Board::const_iterator BoardConstIterator;
typedef pair<ChessSquare, bool> KingTracker;

class ChessBoard {

    private:

        ChessSet* pieces;
        Board board;
        Color turn;

        // Tracks position and check status of each King.
        KingTracker whiteKing;
        KingTracker blackKing;

        // Method: init
        // ============
        void init();

        // Method: arrange
        // ===============
        void arrange();

        // Method: arrangeSide
        // ===================
        void arrangeSide(Color color);

        // Method: cleanUp
        // ===============
        void cleanUp();

        // Method: startGame
        // =================
        void startGame();

        // Method: switchTurns
        // ===================
        // This method changes the turn property of the ChessBoard
        // to the  Color of the player whose turn it is to move next.
        void switchTurns();

        // Method: updateKingSquare
        // ========================
        void updateKingSquare(const ChessSquare& source,
                              const ChessSquare& destination);

        // Method: isObstructed
        // ====================
        bool isObstructed(const ChessSquare& source,
                          const ChessSquare& destination) const;

        // Method: isInCheck
        // =================
        bool isInCheck(Color color) const;

        // Method: isPossibleMove
        // ======================
        bool isPossibleMove(const ChessSquare& sourceSquare,
                            const ChessSquare& destinationSquare,
                            ChessPiece* sourcePiece,
                            ChessPiece* destinationPiece) const;

        // Method: printTopLine
        // ====================
        void printTopLine() const;

        // Method: printMiddleLine
        // =======================
        void printMiddleLine() const;

        // Method: printBottomLine
        // =======================
        void printBottomLine() const;

    public:

        // Constructor: Default
        // ====================
        ChessBoard();

        // Destructor:
        // ===========
        ~ChessBoard();

        // Method: submitMove
        // ==================
        bool submitMove(string , string);

        // Method: resetBoard
        // ==================
        void resetBoard();
   
        // Method: getBoard
        // ================
        Board getBoard() const;

        // Method: getChessSet
        // ===================
        ChessSet getChessSet() const;

        // Method: getKingTracker
        // ======================
        KingTracker getKingTracker(Color color) const;

        // Method: getKingStartSquare
        // ==========================
        // This method is used to define the default
        // start square for the black and white Kings.
        ChessSquare getKingStartSquare(Color color) const;

        // Method: print
        // =============
        void print() const;

};

#endif
