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

    private:
        // Method: initSymbol
        // ==================
        void initSymbol(Color color);

    public:

        // Constructor:
        // ============
        Rook();
        Rook(Color color);
        Rook(Color color, ChessSquare* square);

        // Destructor:
        // ===========
        ~Rook();

        // Method: isValidMove
        // ===================
        bool isValidMove(const ChessSquare& square,
                         ChessPiece* piece) const;

        //// Method: getSymbol
        //// =================
        //string getSymbol();

        // Operator: <<
        // ============
        friend ostream& operator<<(ostream& os, Rook rook);
};

#endif
