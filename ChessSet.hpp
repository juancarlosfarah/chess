// ==========================================
// File:    ChessSet.hpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#ifndef CHESS_SET_HPP
#define CHESS_SET_HPP

#include <array>
#include <iostream>
using namespace std;

#include "ChessPiece.hpp"
#include "Pawn.hpp"
#include "Bishop.hpp"
#include "Knight.hpp"
#include "Rook.hpp"
#include "Queen.hpp"
#include "King.hpp"

typedef array<ChessPiece*, 16> ChessSide;
typedef ChessSide::iterator ChessSideIterator;
typedef ChessSide::const_iterator ChessSideConstIterator;

class ChessSet {

    private:
        ChessSide whites;
        ChessSide blacks;

        // Method: initSide
        // ================
        void initSide(Color color);

    public:

        // Constructor: Default
        // ====================
        ChessSet();

        // Destructor:
        // ===========
        ~ChessSet();

        // Method: getSide
        // ===============
        const ChessSide* getSide(const Color& color) const;

        // Method: getWhites
        // =================
        const ChessSide* getWhites() const;

        // Method: getBlacks
        // =================
        const ChessSide* getBlacks() const;

        // Method: print
        // =============
        void print() const;
};

#endif
