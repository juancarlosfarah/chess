#ifndef CHESS_BOARD_HPP
#define CHESS_BOARD_HPP

#include <iostream>
#include <map>
using namespace std;

#include "ChessSet.hpp"
#include "ChessPiece.hpp"
#include "ChessSquare.hpp"

class ChessBoard {

    private:

        ChessSet pieces;        
        map<ChessSquare, ChessPiece> board;

        // Method: arrange
        // ===============
        void arrange();

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
   
        // Operator: <<
        // ============
        friend ostream& operator<<(ostream& os, ChessBoard cb);
};


#endif
