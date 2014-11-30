// ==========================================
// File:    Pawn.hpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#ifndef PAWN_HPP
#define PAWN_HPP

#include <iostream>
using namespace std;

#include "ChessPiece.hpp"

class Pawn : public ChessPiece {
    
    public:

        // Constructor:
        // ============
        Pawn();
        Pawn(Color color);
        Pawn(Color color, ChessSquare* position);

        // Method: print
        // =============
        void print();

        // Operator: <<
        // ============
        friend ostream& operator<<(ostream& os, Pawn pawn);
};

#endif
