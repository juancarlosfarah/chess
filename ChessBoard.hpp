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

class ChessBoard {

    private:

        ChessSet* pieces;
        Board board;
        Color turn;

        // Tracks position of each King.
        ChessSquare whiteKingSquare;
        ChessSquare blackKingSquare;

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
        void updateKingSquare(ChessSquare& source,
                              ChessSquare& destination);

        // Method: update
        // ==============
        void update(ChessPiece* sourcePiece, ChessPiece* destinationPiece,
                    ChessSquare& sourceSquare,
                    ChessSquare& destinationSquare);
        
        // Method: update
        // ==============
        void reverse(ChessPiece* sourcePiece, ChessPiece* destinationPiece,
                     ChessSquare& sourceSquare,
                     ChessSquare& destinationSquare);

        // Method: isObstructed
        // ====================
        bool isObstructed(ChessSquare& source,
                          ChessSquare& destination) const;

        // Method: isInCheck
        // =================
        bool isInCheck(Color color) const;

        // Method: isInCheckmate
        // ====================
        bool isInCheckmate(Color color, ChessSquare& square) const;

        // Method: isPossibleMove
        // ======================
        bool isPossibleMove(ChessSquare& sourceSquare,
                            ChessSquare& destinationSquare,
                            ChessPiece* sourcePiece,
                            ChessPiece* destinationPiece) const;

        // Method: isValidMove
        // ===================
        bool isValidMove(ChessSquare& sourceSquare,
                         ChessSquare& destinationSquare,
                         ChessPiece* sourcePiece,
                         ChessPiece* destinationPiece,
                         stringstream& ssSuccess, bool isQuiet);

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

        // Method: getKingSquare
        // =====================
        const ChessSquare getKingSquare(Color color) const;

        // Method: getKingStartSquare
        // ==========================
        // This method is used to define the default
        // start square for the black and white Kings.
        const ChessSquare getKingStartSquare(Color color) const;

        // Method: print
        // =============
        void print() const;

};

#endif
