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
    
    private:

        // Method: initSymbol
        // ==================
        void initSymbol(Color color);

    public:

        // Constructor:
        // ============
        Queen();
        Queen(Color color);
        Queen(Color color, ChessSquare* square);

        // Destructor:
        // ===========
        ~Queen();

        //// Method: getSymbol
        //// =================
        //string getSymbol();

        // Method: isPossibleMove
        // ===================
        pair<bool, bool> isPossibleMove(const ChessSquare& square,
                                     ChessPiece* piece) const;

        // Operator: <<
        // ============
        friend ostream& operator<<(ostream& os, Queen queen);
};

#endif
