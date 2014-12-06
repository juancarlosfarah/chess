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
    
    private:

        // Method: initSymbol
        // ==================
        void initSymbol(Color color);

    public:

        // Constructor:
        // ============
        Pawn();
        Pawn(Color color);
        Pawn(Color color, const ChessSquare& square);
        // Destructor:
        // ===========
        ~Pawn();

        // Method: isPossibleMove
        // ======================
        pair<bool, bool> isPossibleMove(ChessSquare& square,
                                        ChessPiece* piece) const;

        //// Method: getSymbol
        //// =================
        //string getSymbol();

        // Operator: <<
        // ============
        friend ostream& operator<<(ostream& os, const Pawn& pawn);
};

#endif
