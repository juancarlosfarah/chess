// ==========================================
// File:    King.hpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#ifndef KING_HPP
#define KING_HPP

#include <iostream>
using namespace std;

#include "ChessPiece.hpp"

class King : public ChessPiece {
    
    public:

        // Constructor:
        // ============
        King();
        King(Color color);
        King(Color color, ChessSquare* position);

        // Method: print
        // =============
        void print();

        // Operator: <<
        // ============
        friend ostream& operator<<(ostream& os, King king);
};

#endif
