// ==========================================
// File:    Bishop.hpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#ifndef BISHOP_HPP
#define BISHOP_HPP

#include <iostream>
using namespace std;

#include "ChessPiece.hpp"

class Bishop : public ChessPiece {
    
    public:

        // Constructor:
        // ============
        Bishop();
        Bishop(Color color);
        Bishop(Color color, ChessSquare* position);

        // Method: print
        // =============
        void print();

        // Operator: <<
        // ============
        friend ostream& operator<<(ostream& os, Bishop bishop);
};

#endif
