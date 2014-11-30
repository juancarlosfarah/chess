// ==========================================
// File:    ChessSet.hpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#ifndef CHESS_SET_HPP
#define CHESS_SET_HPP

#include <array>
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

class ChessSet {

    private:
        ChessSide whites;
        ChessSide blacks;

        // Method: initSide
        // ================
        void initSide(Color color);

        // Method: getSide
        // ===============
        ChessSide* getSide(Color color);

    public:

        // Constructor: Default
        // ====================
        ChessSet();

        // Method: getWhites
        // =================
        ChessSide* getWhites();

        // Method: getBlacks
        // =================
        ChessSide* getBlacks();

        // Method: print
        // =============
        void print();
};

#endif
