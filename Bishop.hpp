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
        Bishop(Color color, const ChessSquare& square);

        // Destructor:
        // ===========
        ~Bishop();

        //// Method: getSymbol
        //// =================
        //string getSymbol();

        // Method: isPossibleMove
        // ======================
        pair<bool, bool> isPossibleMove(ChessSquare& square,
                                        ChessPiece* piece) const;

        // Operator: <<
        // ============
        friend ostream& operator<<(ostream& os, Bishop bishop);
};

#endif
