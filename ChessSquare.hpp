// ==========================================
// File:    ChessSquare.hpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#ifndef CHESS_SQUARE_HPP
#define CHESS_SQUARE_HPP

#include <string>
#include <utility>
using namespace std;

#include "InvalidCoordinatesException.hpp"

class ChessSquare {

    private:
        
        // Coordinate Pair
        char file;
        int rank;

        // Method: isValidFile
        // ===================
        // Takes a char and returns a bool indicating if it is a valid
        // symbol for a file, i.e. if it is a letter between A and H,
        // inclusive. Note this method is case insensitive.
        bool isValidFile(char file);

        // TODO: Eliminate!
        // Method: isValidRank
        // ===================
        // Takes a char and returns a bool indicating if it is a valid
        // symbol for a rank, i.e. if it is an integer between 1 and 8,
        // inclusive.
        bool isValidRank(char rank);

        // Method: isValidRank
        // ===================
        // Takes an int and returns a bool indicating if it is a valid
        // symbol for a file, i.e. it's an int between 1 and 8, inclusive.
        bool isValidRank(int rank);

    public:

        // Constructor: Default
        // ====================
        ChessSquare();

        // Constructor:
        // ============
        // This constructor takes a string containing a chess coordinate
        // pair (e.g. H1), and parses it to its corresponding char
        // and int elements, with which it constructs the respective
        // ChessSquare object. If the string passed in is invalid, the
        // constructor throws an InvalidCoordinatesException.
        ChessSquare(string coords) throw(InvalidCoordinatesException&);

        // Constructor:
        // ============
        // This constructor takes a char file and an int rank and
        // constructs the respective ChessSquare object. If the arguments
        // are invalid, it throws an InvalidCoordinatesException.
        ChessSquare(char file, int rank)
                    throw(InvalidCoordinatesException&);

        // Method: getFile
        // ===============
        // Returns the file property of this ChessSquare.
        char getFile() const;

        // Method: getRank
        // ===============
        // Returns the rank property of this ChessSquare.
        int getRank() const;

        // Operator: <
        // ===========
        bool operator<(const ChessSquare& other) const;

        // Operator: ==
        // ============
        bool operator==(const ChessSquare& other) const;

        // Operator: <<
        // ============
        friend ostream& operator<<(ostream& os, const ChessSquare square);
};

#endif
