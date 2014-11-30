// ==========================================
// File:    ChessPiece.hpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#ifndef CHESS_PIECE_HPP
#define CHESS_PIECE_HPP

#include <iostream>
using namespace std;

#include "ChessSquare.hpp"

enum Color {White, Black};

class ChessPiece {
    
    protected:

        Color color;
        ChessSquare* position;

    public:

        // Constructor:
        // ============
        ChessPiece();
        ChessPiece(Color color);
        ChessPiece(Color color, ChessSquare* position);

        // Method: setPosition
        // ===================
        // Takes a ChessSquare and sets it as the position
        // attribute of this ChessPiece.
        void setPosition(ChessSquare* cs);

        // Method: getPosition
        // ===================
        // Returns the position attribute of this ChessPiece.
        ChessSquare* getPosition();

        // Method: print
        // =============
        virtual void print();

        // Operator: <<
        // ============
        friend ostream& operator<<(ostream& os, ChessPiece cp);
};

#endif
