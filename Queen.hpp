// ==========================================
// File:    Queen.hpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#ifndef QUEEN_HPP
#define QUEEN_HPP

#include <iostream>
using namespace std;

#include "ChessPiece.hpp"

class Queen : public ChessPiece {
    
    public:

        // Constructor:
        // ============
        Queen();
        Queen(Color color);
        Queen(Color color, ChessSquare* position);

        // Method: print
        // =============
        void print();

        // Operator: <<
        // ============
        friend ostream& operator<<(ostream& os, Queen queen);
};

#endif
