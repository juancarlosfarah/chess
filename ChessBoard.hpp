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


class ChessBoard {

    private:

        ChessSet pieces;        
        map<ChessSquare, ChessPiece*> board;

        // Method: init
        // ============
        void init();

        // Method: arrange
        // ===============
        void arrange();

        // Method: arrangeSide
        // ===================
        void arrangeSide(Color color);

    public:

        // Constructor: Default
        // ====================
        ChessBoard();

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
