// ==========================================
// File:    ChessSet.hpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#ifndef CHESS_SET_HPP
#define CHESS_SET_HPP

#include <unordered_set>
using namespace std;

#include "ChessPiece.hpp"

class ChessSet {

    private:
        unordered_set<int> set;

    public:

        // Constructor: Default
        // ====================
        ChessSet();
};

#endif
