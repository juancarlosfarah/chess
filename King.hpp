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
    
    private:

        // Method: initSymbol
        // ==================
        void initSymbol(Color color);

    public:

        // Constructor:
        // ============
        King();
        King(Color color);
        King(Color color, ChessSquare* square);

        // Destructor:
        // ===========
        ~King();

        //// Method: getSymbol
        //// =================
        //string getSymbol();

        // Method: isPossibleMove
        // ===================
        pair<bool, bool> isPossibleMove(const ChessSquare& square,
                                     ChessPiece* piece) const;

        // Operator: <<
        // ============
        friend ostream& operator<<(ostream& os, King king);
};

#endif
