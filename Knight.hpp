// ==========================================
// File:    Knight.hpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include <iostream>
using namespace std;

#include "ChessPiece.hpp"

class Knight : public ChessPiece {
    
    private:

        // Method: initSymbol
        // ==================
        void initSymbol(Color color);

    public:

        // Constructor:
        // ============
        Knight();
        Knight(Color color);
        Knight(Color color, ChessSquare* square);

        // Destructor:
        // ===========
        ~Knight();

        //// Method: getSymbol
        //// =================
        //string getSymbol();

        // Operator: <<
        // ============
        friend ostream& operator<<(ostream& os, Knight knight);
};

#endif
