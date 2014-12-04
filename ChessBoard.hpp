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

        ChessSet pieces;        
        Board board;
        Color turn;

        // Method: init
        // ============
        void init();

        // Method: arrange
        // ===============
        void arrange();

        // Method: arrangeSide
        // ===================
        void arrangeSide(Color color);

        // Method: startGame
        // =================
        void startGame();

        // Method: switchTurns
        // ===================
        // This method changes the turn property of the ChessBoard
        // to the  Color of the player whose turn it is to move next.
        void switchTurns();

        // Method: isValidMove
        // ===================
        bool isValidMove(const ChessSquare& source,
                         const ChessSquare& destination,
                         bool isPotentiallyBlocked) const;

        // Method: printTopLine
        // ====================
        void printTopLine();

        // Method: printMiddleLine
        // =======================
        void printMiddleLine();

        // Method: printBottomLine
        // =======================
        void printBottomLine();

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
        map<ChessSquare, ChessPiece*> getBoard();

        // Method: print
        // =============
        void print();

        // Method: getChessSet
        // ===================
        ChessSet getChessSet();

        // Operator: <<
        // ============
        friend ostream& operator<<(ostream& os, ChessBoard cb);
};

#endif
