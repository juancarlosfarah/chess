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
    
    private:
        Color color;

    public:

        // Constructor: Default
        // ====================
        ChessPiece();
};

#endif
