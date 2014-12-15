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

#include "Settings.hpp"
#include "ChessPiece.hpp"
#include "Pawn.hpp"
#include "Bishop.hpp"
#include "Knight.hpp"
#include "Rook.hpp"
#include "Queen.hpp"
#include "King.hpp"

// Type: ChessSide & Iterators
// ===========================
// The ChessSide is an array of pointers to ChessPiece objects. This
// container is used to refer to a side (Whites, Blacks), during a
// game of chess. Each ChessSet object has two ChessSide containers
// and each ChessSide has pointers to the ChessPiece objects needed
// by default on each side.
typedef array<ChessPiece*, PIECES_PER_SIDE> ChessSide;
typedef ChessSide::iterator ChessSideIterator;
typedef ChessSide::const_iterator ChessSideConstIterator;

// Class: ChessSet
// ===============
// This class defines the data members and methods associated with the
// ChessSet object. The ChessSet is primarily concerned with initialising
// the arrays of pointers to ChessPiece objects (ChessSide) that will be
// used to access the pieces that are used to play. It also ensures that
// each ChessSide contains the right number of each piece.
class ChessSet {

    private:

        ChessSide whites;
        ChessSide blacks;

        // Method: initSide
        // ================
        // This method initialises the array of pieces that will be used
        // by one ChessSide. It ensures that it has the right number and
        // type of pieces according to the rules of chess.
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
        // This method takes a Color and returns a pointer to the
        // ChessSide in this ChessSet matching the given Color.
        const ChessSide* getSide(const Color& color) const;

        // Method: getWhites
        // =================
        // This method returns a pointer to the
        // whites property of this ChessSet.
        const ChessSide* getWhites() const;

        // Method: getBlacks
        // =================
        // This method returns a pointer to the
        // blacks property of this ChessSet.
        const ChessSide* getBlacks() const;
};

#endif
