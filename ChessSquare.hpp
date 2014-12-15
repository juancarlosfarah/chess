// ==========================================
// File:    ChessSquare.hpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#ifndef CHESS_SQUARE_HPP
#define CHESS_SQUARE_HPP

#include <string>
#include <set>
#include <utility>
using namespace std;

#include "InvalidCoordinatesException.hpp"

// Class: ChessSquare
// ==================
// This class defines the data members and methods belonging to the
// ChessSquare object. The ChessSquare consists of a Chess coordinate
// pair indicating its location on the board. The ChessBoard object
// will then construct 64 ChessSquare objects when populating its
// Board, one for each position a piece can take. Additionally, the
// ChessSquare class defines a number of methods that indicate the
// position of this ChessSquare in relation to other ChessSquare objects
// in the same Board. These methods are used when defining the way
// ChessPiece objects can move.
class ChessSquare {

    private:
        
        // Chess Coordinate Pair
        char file;                  // Column
        int rank;                   // Row

        // Method: isValidFile
        // ===================
        // Takes a char and returns a bool indicating if it is a valid
        // symbol for a file, i.e. if it is a letter between A and H,
        // inclusive. Note this method is case insensitive.
        bool isValidFile(char file) const;

        // Method: isValidRank
        // ===================
        // Takes an int and returns a bool indicating if it is a valid
        // symbol for a file, i.e. it's an int between 1 and 8, inclusive.
        bool isValidRank(int rank) const;

    public:

        // Constructor: Default
        // ====================
        ChessSquare();

        // Constructor: Copy
        // =================
        ChessSquare(const ChessSquare& other);
        ChessSquare(ChessSquare* other);

        // Constructor:
        // ============
        // This constructor takes a string containing a chess coordinate
        // pair (e.g. H1), and parses it to its corresponding char
        // and int elements, with which it constructs the respective
        // ChessSquare object. If the string passed in is invalid, the
        // constructor throws an InvalidCoordinatesException.
        ChessSquare(string coordinates)
                    throw(InvalidCoordinatesException&);

        // Constructor:
        // ============
        // This constructor takes a char file and an int rank and
        // constructs the respective ChessSquare object. If the arguments
        // are invalid, it throws an InvalidCoordinatesException.
        ChessSquare(char file, int rank)
                    throw(InvalidCoordinatesException&);

        // Destructor:
        // ===========
        virtual ~ChessSquare();

        // Method: getFile
        // ===============
        // Returns the file property of this ChessSquare.
        char getFile() const;

        // Method: getRank
        // ===============
        // Returns the rank property of this ChessSquare.
        int getRank() const;

        // Method: isDiagonalFrom
        // ======================
        // This method takes a ChessSquare and returns a bool indicating
        // whether or not it is on the same diagonal as this ChessSquare.
        bool isDiagonalFrom(const ChessSquare& other) const;

        // Method: isAdjacent
        // ==================
        // This method takes a ChessSquare and returns a
        // bool indicating if it is adjacent to this square.
        bool isAdjacent(const ChessSquare& other) const;

        // Method: isDirectlyAbove
        // =======================
        // This method takes a ChessSquare and returns a bool
        // indicating if it is directly above this square.
        bool isDirectlyAbove(const ChessSquare& other) const;

        // Method: isDirectlyBelow
        // =======================
        // This method takes a ChessSquare and returns a bool
        // indicating if it is directly below this square.
        bool isDirectlyBelow(const ChessSquare& other) const;

        // Method: isDirectlyAboveDiagonally
        // =================================
        // This method takes a ChessSquare and returns a bool indicating
        // if it is directly above-left or above-right of this square.
        bool isDirectlyAboveDiagonally(const ChessSquare& other) const;

        // Method: isDirectlyBelowDiagonally
        // =================================
        // This method takes a ChessSquare and returns a bool indicating
        // if it is directly below-left or below-right of this square.
        bool isDirectlyBelowDiagonally(const ChessSquare& other) const;

        // Method: isKnightHopFrom
        // =======================
        // This method takes a ChessSquare and returns a bool indicating
        // if it is offset by 1 and then 2 (in all eight possible vertical
        // and horizontal combinations) from this square.
        bool isKnightHopFrom(const ChessSquare& other) const;

        // Method: getSquaresBetween
        // =========================
        // This method takes a ChessSquare and returns a set of ChessSquare
        // objects containing all of the squares directly between this
        // square and the given square. If the squares are not in the same
        // rank, file or diagonal this method returns the empty set.
        set<ChessSquare> getSquaresBetween(const ChessSquare& other) const;

        // Method: getAdjacentSquares
        // ==========================
        // This method takes a ChessSquare and returns a set of
        // ChessSquare objects containing all of its adjacent squares.
        set<ChessSquare> getAdjacentSquares() const;

        // Method: distance
        // ================
        // This method takes a ChessSquare and returns the integer
        // number of squares between this square and the given square.
        int distance(const ChessSquare& other) const;

        // Operator: <
        // ===========
        // A square is less than another square if its rank is greater
        // than the other square's rank. And if their ranks are equal,
        // then if its file is less than the other square's file. This
        // ensures that when printing the board, squares are printed
        // from left to right, top to bottom.
        bool operator<(const ChessSquare& other) const;

        // Operator: ==
        // ============
        // Two ChessSquare objects are equal if both
        // their rank and file properties are equal.
        bool operator==(const ChessSquare& other) const;

        // Operator: <<
        // ============
        // Output the file followed by the rank (e.g. A1).
        friend ostream& operator<<(ostream& os, const ChessSquare& square);
};

#endif
