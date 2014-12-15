// ==========================================
// File:    ChessSquare.cpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#include <cctype>
#include <iostream>
#include <cmath>
using namespace std;

#include "ChessSquare.hpp"
#include "Settings.hpp"

// Constructor: Default
// ====================
ChessSquare::ChessSquare() {}

// Constructor: Copy
// =================
ChessSquare::ChessSquare(const ChessSquare& other) {
    this->rank = other.rank;
    this->file = other.file;
}

// Constructor: Copy
// =================
ChessSquare::ChessSquare(ChessSquare* other) {
    this->rank = other->rank;
    this->file = other->file;
}

// Constructor:
// ============
// This constructor takes a string containing a chess coordinate
// pair (e.g. H1), and parses it to its corresponding char
// and int elements, with which it constructs the respective
// ChessSquare object. If the string passed in is invalid, the
// constructor throws an InvalidCoordinatesException.
ChessSquare::ChessSquare(string coordinates)
                         throw(InvalidCoordinatesException&) {

    // Allowing char input to be lowercase
    // so always convert it to uppercase.
    char file = toupper(coordinates[0]);

    // Subtract int value of '0' to get real int value not ASCII code.
    int rank = coordinates[1] - '0';

    // Parse the first and second characters in the string and ensure
    // that they are valid. If so set the properties accordingly.
    if (this->isValidFile(file) && this->isValidRank(rank)) {
        this->file = file;
        this->rank = rank;
    } else {
        throw InvalidCoordinatesException();
    }
}

// Constructor:
// ============
// This constructor takes a char file and an int rank and constructs
// the respective ChessSquare object. If the arguments are invalid,
// it throws an InvalidCoordinatesException.
ChessSquare::ChessSquare(char file, int rank)
                         throw(InvalidCoordinatesException&) {

    // Allowing char input to be lowercase
    // so always convert it to uppercase.
    file = toupper(file);

    // Ensure that the input is valid.
    if (this->isValidFile(file) && this->isValidRank(rank)) {
        this->file = file;
        this->rank = rank;
    } else {
        throw InvalidCoordinatesException();
    }
}

// Destructor:
// ===========
ChessSquare::~ChessSquare() {}


// Public Method: getFile
// ======================
// Returns the file property of this ChessSquare.
char ChessSquare::getFile() const {
    return this->file;
}

// Public Method: getRank
// ======================
// Returns the rank property of this ChessSquare.
int ChessSquare::getRank() const {
    return this->rank;
}

// Private Method: isValidFile
// ===========================
// Takes a char and returns a bool indicating if it is a valid symbol
// for a file, i.e. if it is a letter between A and H, inclusive.
// This method is case insensitive.
bool ChessSquare::isValidFile(char file) const {
    return (file >= LEFTMOST_FILE && file <= RIGHTMOST_FILE);
}

// Private Method: isValidRank
// ===========================
// Takes an int and returns a bool indicating if it is a valid symbol
// for a file, i.e. if it is an integer between 1 and 8, inclusive.
bool ChessSquare::isValidRank(int rank) const {
    return (rank >= BOTTOM_RANK && rank <= TOP_RANK);
}

// Public Method: isDiagonalFrom
// =============================
// This method takes a ChessSquare and returns a bool indicating
// whether or not it is on the same diagonal as this ChessSquare.
bool ChessSquare::isDiagonalFrom(const ChessSquare& other) const {

    // If squares are the same, return false.
    if (*this == other) return false;

    // Calculate absolute differences of the coordinates of both
    // squares. If both are equal, then they are on the same diagonal.
    int fileDiff = abs(this->file - other.file);
    int rankDiff = abs(this->rank - other.rank);
    return (fileDiff == rankDiff);
}

// Public Method: isAdjacent
// =========================
// This method takes a ChessSquare and returns a
// bool indicating if it is adjacent to this square.
bool ChessSquare::isAdjacent(const ChessSquare& other) const {

    // If squares are the same, return false.
    if (*this == other) return false;

    // Calculate the distance between the squares. If the
    // distance is zero then the squares are adjacent.
    return (this->distance(other) == 0);
}

// Public Method: isDirectlyBelow
// ==============================
// This method takes a ChessSquare and returns a bool
// indicating if it is directly below this square.
bool ChessSquare::isDirectlyBelow(const ChessSquare& other) const {

    // Return true if rank is directly below (i.e. difference
    // is 1) and file is the same (i.e. difference is 0).
    int fileDiff = (this->file - other.file);
    int rankDiff = (this->rank - other.rank);
    return ((rankDiff == 1) && (fileDiff == 0));

}

// Public Method: isDirectlyAbove
// ==============================
// This method takes a ChessSquare and returns a bool
// indicating if it is directly above this square.
bool ChessSquare::isDirectlyAbove(const ChessSquare& other) const {

    // Return true if rank is directly above (i.e. difference
    // is -1) and file is the same (i.e. difference is 0).
    int fileDiff = (this->file - other.file);
    int rankDiff = (this->rank - other.rank);
    return ((rankDiff == -1) && (fileDiff == 0));

}

// Public Method: isDirectlyBelowDiagonally
// ========================================
// This method takes a ChessSquare and returns a bool indicating
// if it is directly below-left or below-right of this square.
bool ChessSquare::isDirectlyBelowDiagonally(const ChessSquare& other)
                                            const {

    // Return true if rank is directly below (i.e. difference is 1) and
    // file is to the right or left (i.e. absolute difference is 1).
    int fileDiff = (this->file - other.file);
    int rankDiff = (this->rank - other.rank);
    return ((rankDiff == 1) && (abs(fileDiff) == 1));
}

// Public Method: isDirectlyAboveDiagonally
// ========================================
// This method takes a ChessSquare and returns a bool indicating
// if it is directly above-left or above-right of this square.
bool ChessSquare::isDirectlyAboveDiagonally(const ChessSquare& other)
                                            const {

    // Return true if rank is directly above (i.e. difference is -1)
    // and file is to the right or left (i.e. absolute difference is 1).
    int fileDiff = (this->file - other.file);
    int rankDiff = (this->rank - other.rank);
    return ((rankDiff == -1) && (abs(fileDiff) == 1));
}

// Public Method: isKnightHopFrom
// ==============================
// This method takes a ChessSquare and returns a bool indicating
// if it is offset by 1 and then 2 (in all eight possible vertical
// and horizontal combinations) from this square.
bool ChessSquare::isKnightHopFrom(const ChessSquare& other) const {
    int fileDiff = abs(this->file - other.file);
    int rankDiff = abs(this->rank - other.rank);
    return ((rankDiff == 1 && fileDiff == 2) ||
            (rankDiff == 2 && fileDiff == 1));
}

// Public Method: distance
// =======================
// This method takes a ChessSquare and returns the integer
// number of squares between this square and the given square.
int ChessSquare::distance(const ChessSquare& other) const {

    // In a ChessBoard, the number of squares between one square and
    // another is indicated by the maximum of the differences minus 1.
    int fileDiff = abs(this->file - other.file);
    int rankDiff = abs(this->rank - other.rank);
    return (max(fileDiff, rankDiff) - 1);
}

// Public Method: getAdjacentSquares
// =================================
// This method takes a ChessSquare and returns a set of
// ChessSquare objects containing all of its adjacent squares.
set<ChessSquare> ChessSquare::getAdjacentSquares() const {

    // Define a set of empty squares and the offset to
    // be 1, indicating that it is an adjacent square.
    set<ChessSquare> squares;
    int offset = 1;

    // These flags allow for checks to only be done
    // once and then these can be used for diagonals.
    bool isValidAbove = false,
         isValidBelow = false,
         isValidRight = false,
         isValidLeft = false;

    char newFile;
    int newRank;

    // Check if squares directly above and below are valid.
    // If so, add them to the set and set the flags to true.
    if (this->isValidRank(newRank = this->rank - offset)) {
        squares.insert(ChessSquare(this->file, newRank));
        isValidAbove = true;
    }
    if (isValidRank(newRank = this->rank + offset)) {
        squares.insert(ChessSquare(this->file, newRank));
        isValidBelow = true;
    }

    // Check if squares directly left and right are valid.
    // If so, add them to the set and set the flags to true.
    if (isValidFile(newFile = this->file - offset)) {
        squares.insert(ChessSquare(newFile, this->rank));
        isValidLeft = true;
    }
    if (isValidFile(newFile = this->file + offset)) {
        squares.insert(ChessSquare(newFile, this->rank));
        isValidRight = true;
    }

    // Check if adjacent diagonals are valid using
    // the flags. If so, add them to the set.
    if (isValidAbove && isValidRight) {
        squares.insert(ChessSquare(this->file + offset,
                                   this->rank - offset));
    }
    if (isValidAbove && isValidLeft) {
        squares.insert(ChessSquare(this->file - offset,
                                   this->rank - offset));
    }
    if (isValidBelow && isValidRight) {
        squares.insert(ChessSquare(this->file + offset,
                                   this->rank + offset));
    }
    if (isValidBelow && isValidLeft) {
        squares.insert(ChessSquare(this->file - offset,
                                   this->rank + offset));
    }

    return squares;
}

// Public Method: getSquaresBetween
// ================================
// This method takes a ChessSquare and returns a set of ChessSquare
// objects containing all of the squares directly between this square
// and the given square. Note that if the squares are not in the
// same rank, file or diagonal this method returns the empty set.
set<ChessSquare> ChessSquare::getSquaresBetween(const ChessSquare& other)
                                                const {

    // By default, return an empty set of squares.
    set<ChessSquare> squares;

    // If squares are on the same rank.
    if (this->rank == other.rank) {
        int displacement = this->file - other.file;
        int distance = abs(displacement) - 1;
        while (distance > 0) {
            ChessSquare cs(*this);
            if (displacement < 0) {
                cs.file += distance;
            } else {
                cs.file -= distance;
            }
            squares.insert(cs);
             --distance;
        }
    }

    // If squares are on the same file.
    if (this->file == other.file) {
        int displacement = this->rank - other.rank;
        int distance = abs(displacement) - 1;
        while (distance > 0) {
            ChessSquare cs(*this);
            if (displacement < 0) {
                cs.rank += distance;
            } else {
                cs.rank -= distance;
            }
            squares.insert(cs);
            --distance;
        }
    }

    // If squares are on the same diagonal.
    if (this->isDiagonalFrom(other)) {
        int verticalDisplacement = this->rank - other.rank;
        int horizontalDisplacement = this->file - other.file;
        int distance = this->distance(other);
        while (distance > 0) {
            int newRank = this->rank;
            char newFile = this->file;
            if (verticalDisplacement < 0)  {
                newRank += distance;
            } else {
                newRank -= distance;
            }
            if (horizontalDisplacement < 0) {
                newFile += distance;
            } else {
                newFile -= distance;
            }
            ChessSquare cs(newFile, newRank);
            squares.insert(cs);
            --distance;
        }
    }

    return squares;
}

// Operator: <
// ===========
// A square is less than another square if its rank is greater than the
// other square's rank. And if their ranks are equal, then if its file
// is less than the other square's file. This ensures that when printing
// the board, the squares are printed from left to right, top to bottom.
bool ChessSquare::operator<(const ChessSquare& other) const {
    return (this->rank > other.rank) ||
           ((this->rank == other.rank) && (this->file < other.file));
}

// Operator: ==
// ============
// Two squares are equal if both their rank and file properties are equal.
bool ChessSquare::operator==(const ChessSquare& other) const {
    return ((this->rank == other.rank) && (this->file == other.file));
}

// Friend Operator: <<
// ===================
// Output the file followed by the rank (e.g. A1).
ostream& operator<<(ostream& os, const ChessSquare& square) {
    os << square.file << square.rank;
    return os;
}
