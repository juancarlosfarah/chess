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
    
    private:

        // Method: initSymbol
        // ==================
        void initSymbol(Color color);

    public:

        // Constructor:
        // ============
        Bishop();
        Bishop(Color color);
        Bishop(Color color, ChessSquare* position);

        // Destructor:
        // ===========
        ~Bishop();

        //// Method: getSymbol
        //// =================
        //string getSymbol();

        // Operator: <<
        // ============
        friend ostream& operator<<(ostream& os, Bishop bishop);
};

#endif
