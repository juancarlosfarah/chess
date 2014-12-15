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

// Class: Queen
// ============
// This class defines the data members and methods of the Queen, which
// is a subclass of ChessPiece. This class defines how a Queen can move,
// its name and the symbol it is given according to its Color.
class Queen : public ChessPiece {
    
    private:

        // Method: initSymbol
        // ==================
        // This method initialises the symbol
        // property of the Queen given its Color.
        void initSymbol(Color color);

    public:

        // Constructor:
        // ============
        // These mirror the constructors of the ChessPiece superclass.
        Queen();
        Queen(Color color);
        Queen(Color color, const ChessSquare& square);

        // Destructor:
        // ===========
        virtual ~Queen();

        // Method: isPossibleMove
        // ======================
        // This method takes a ChessSquare and a pointer to the ChessPiece
        // in that ChessSquare (or nullptr if its empty), and returns a
        // pair of booleans. The first bool indicates if the move is
        // possible given the rules of movement of the Queen. The second
        // bool is true if the move requires the Queen to go through one
        // or more squares. This indicates if the move needs to be checked
        // further by the ChessBoard for any potential obstructions.
        // This method is inherited from the ChessPiece superclass.
        pair<bool, bool> isPossibleMove(ChessSquare& square,
                                        ChessPiece* piece) const;

        // Operator: <<
        // ============
        // Outputs the symbol property of the Queen operand.
        friend ostream& operator<<(ostream& os, Queen queen);
};

#endif
