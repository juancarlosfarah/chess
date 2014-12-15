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

// Class: Knight
// =============
// This class defines the data members and methods of the Knight, which
// is a subclass of ChessPiece. This class defines how a Knight can move,
// its name and the symbol it is given according to its Color.
class Knight : public ChessPiece {
    
    private:

        // Method: initSymbol
        // ==================
        // This method initialises the symbol
        // property of the Knight given its Color.
        void initSymbol(Color color);

    public:

        // Constructor:
        // ============
        // These mirror the constructors of the ChessPiece superclass.
        Knight();
        Knight(Color color);
        Knight(Color color, const ChessSquare& square);

        // Destructor:
        // ===========
        virtual ~Knight();

        // Method: isPossibleMove
        // ======================
        // This method takes a ChessSquare and a pointer to the ChessPiece
        // in that ChessSquare (or nullptr if its empty), and returns a
        // pair of booleans. The first bool indicates if the move is
        // possible given the rules of movement of the Knight. The second
        // bool is used to indicate if a piece might be blocking the path
        // of the Knight. Because Knights hop over squares, they cannot
        // be blocked along the way. Hence that bool is always false.
        // This method is inherited from the ChessPiece superclass.
        pair<bool, bool> isPossibleMove(ChessSquare& square,
                                        ChessPiece* piece) const;

        // Operator: <<
        // ============
        // Outputs the symbol property of the Knight operand.
        friend ostream& operator<<(ostream& os, Knight knight);
};

#endif
