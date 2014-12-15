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

// Class: Rook
// ===========
// This class defines the data members and methods of the Rook, which
// is a subclass of ChessPiece. This class defines how a Rook can move,
// its name and the symbol it is given according to its Color.
class Rook : public ChessPiece {

    private:

        // Method: initSymbol
        // ==================
        // This method initialises the symbol
        // property of the Rook given its Color.
        void initSymbol(Color color);

    public:

        // Constructor:
        // ============
        // These mirror the constructors of the ChessPiece superclass.
        Rook();
        Rook(Color color);
        Rook(Color color, const ChessSquare& square);

        // Destructor:
        // ===========
        virtual ~Rook();

        // Method: isPossibleMove
        // ======================
        // This method takes a ChessSquare and a pointer to the ChessPiece
        // in that ChessSquare (or nullptr if its empty), and returns a
        // pair of booleans. The first bool indicates if the move is
        // possible given the rules of movement of the Rook. The second
        // bool is true if the move requires the Rook to go through one
        // or more squares. This indicates if the move needs to be checked
        // further by the ChessBoard for any potential obstructions.
        // This method is inherited from the ChessPiece superclass.
        pair<bool, bool> isPossibleMove(ChessSquare& square,
                                        ChessPiece* piece) const;

        // Operator: <<
        // ============
        // Outputs the symbol property of the Rook operand.
        friend ostream& operator<<(ostream& os, Rook rook);
};

#endif
