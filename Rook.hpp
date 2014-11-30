// ==========================================
// File:    Rook.hpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#ifndef ROOK_HPP
#define ROOK_HPP

#include <iostream>
using namespace std;

#include "ChessPiece.hpp"

class Rook : public ChessPiece {
    
    public:

        // Constructor:
        // ============
        Rook();
        Rook(Color color);
        Rook(Color color, ChessSquare* position);

        // Method: print
        // =============
        void print();

        // Operator: <<
        // ============
        friend ostream& operator<<(ostream& os, Rook rook);
};

#endif
