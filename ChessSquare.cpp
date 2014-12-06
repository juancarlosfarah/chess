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

// Constructor: Default
// ====================
ChessSquare::ChessSquare() {}

// Constructor: Copy
// =================
ChessSquare::ChessSquare(const ChessSquare& other) {
    this->rank = other.rank;
    this->file = other.file;
}

// Constructor:
// ============
ChessSquare::ChessSquare(string coords)
                         throw(InvalidCoordinatesException&) {

    char file = coords[0];
    int rank = coords[1] - '0';

    // Parse the first and second characters in the string and ensure
    // that they are valid. If so set the properties accordingly.
    if (isValidFile(file) && isValidRank(rank)) {
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

    if (isValidFile(file) && isValidRank(rank)) {
        this->file = file;
        this->rank = rank;
    } else {
        throw InvalidCoordinatesException();
    }
}

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
    return (file >= 65 && file <= 72);  //TODO: Make case insensitive!
}

// Private Method: isValidRank
// ===========================
// Takes an int and returns a bool indicating if it is a valid symbol
// for a file, i.e. if it is an integer between 1 and 8, inclusive.
bool ChessSquare::isValidRank(int rank) const {
    return (rank >= 1 && rank <= 8);
}

// Public Method: isDiagonalFrom
// =============================
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
// Takes a const ChessSquare by reference and returns a
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
bool ChessSquare::isDirectlyBelow(const ChessSquare& other) const {

    // Return true if rank is directly below (i.e. difference
    // is 1) and file is the same (i.e. difference is 0).
    int fileDiff = (this->file - other.file);
    int rankDiff = (this->rank - other.rank);
    return ((rankDiff == 1) && (fileDiff == 0));

}

// Public Method: isDirectlyAbove
// ==============================
bool ChessSquare::isDirectlyAbove(const ChessSquare& other) const {

    // Return true if rank is directly above (i.e. difference
    // is -1) and file is the same (i.e. difference is 0).
    int fileDiff = (this->file - other.file);
    int rankDiff = (this->rank - other.rank);
    return ((rankDiff == -1) && (fileDiff == 0));

}


// Public Method: isDirectlyBelowDiagonally
// ========================================
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
// Takes a const ChessSquare by reference and returns a bool indicating
// if it is offset by 1 and then 2 (in all eight possible vertical and
// horizontal combinations) from this square.
bool ChessSquare::isKnightHopFrom(const ChessSquare& other) const {
    int fileDiff = abs(this->file - other.file);
    int rankDiff = abs(this->rank - other.rank);
    return ((rankDiff == 1 && fileDiff == 2) ||
            (rankDiff == 2 && fileDiff == 1));
}

// Public Method: distance
// =======================
// Takes a const ChessSquare by reference and returns an int indicating
// the number of squares between this square and that square.
int ChessSquare::distance(const ChessSquare& other) const {

    // In a ChessBoard, the number of squares between one square and
    // another is indicated by the maximum of the differences minus 1.
    int fileDiff = abs(this->file - other.file);
    int rankDiff = abs(this->rank - other.rank);
    return (max(fileDiff, rankDiff) - 1);
}

// Public Method: getAdjacentSquares
// =================================
//
set<ChessSquare> ChessSquare::getAdjacentSquares() const {

    // Define a set of empty squares and the offset to
    // be 1, indicating that it is an adjacent square.
    set<ChessSquare> squares;
    int offset = 1;
    bool isValidAbove = false,
         isValidBelow = false,
         isValidRight = false,
         isValidLeft = false;

    int newFile, newRank;

    // Check if squares directly above and below are valid.
    if (isValidFile(newFile = this->file + offset)) {
        squares.insert(ChessSquare(this->rank, newFile));
        isValidAbove = true;
    }
    if (isValidFile(newFile = this->file - offset)) {
        squares.insert(ChessSquare(this->rank, newFile));
        isValidBelow = true;
    }

    // Check if squares directly left and right are valid.
    if (isValidFile(newRank = this->rank + offset)) {
        squares.insert(ChessSquare(this->file, newRank));
        isValidRight = true;
    }
    if (isValidFile(newRank = this->rank - offset)) {
        squares.insert(ChessSquare(this->file, newRank));
        isValidLeft = true;
    }

    // Check if adjacent diagonals are valid.
    if (isValidAbove && isValidRight) {
        squares.insert(ChessSquare(this->file + offset,
                                   this->rank + offset));
    }
    if (isValidAbove && isValidLeft) {
        squares.insert(ChessSquare(this->file + offset,
                                   this->rank - offset));
    }
    if (isValidBelow && isValidRight) {
        squares.insert(ChessSquare(this->file - offset,
                                   this->rank + offset));
    }
    if (isValidBelow && isValidLeft) {
        squares.insert(ChessSquare(this->file - offset,
                                   this->rank - offset));
    }

    return squares;
}

// Public Method: getSquaresBetween
// ================================
// Note that if the squares are not in the same rank, file or diagonal
// this method returns the empty set.
set<ChessSquare> ChessSquare::getSquaresBetween(const ChessSquare& other)
                                                const {

    // By default, return an empty set of squares.
    set<ChessSquare> squares;

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
            // TODO: Remove debugging code.
            // cout << newFile << newRank << endl;
            ChessSquare cs(newFile, newRank);
            squares.insert(cs);
            --distance;
        }
    }

    return squares;
}

// Operator: <
// ===========
bool ChessSquare::operator<(const ChessSquare& other) const {
    return (this->rank > other.rank) ||
           ((this->rank == other.rank) && (this->file < other.file));
}

// Operator: ==
// ============
bool ChessSquare::operator==(const ChessSquare& other) const {
    return ((this->rank == other.rank) && (this->file == other.file));
}

// Friend Operator: <<
// ===================
ostream& operator<<(ostream& os, const ChessSquare& square) {
    os << square.file << square.rank;
    return os;
}
