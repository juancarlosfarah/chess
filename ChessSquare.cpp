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

// Constructor:
// ============
ChessSquare::ChessSquare() {}

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
bool ChessSquare::isValidFile(char file) {
    return (file >= 65 && file <= 72);  //TODO: Make case insensitive!
}

// TODO: Eliminate!
// Private Method: isValidRank
// ===========================
// Takes a char and returns a bool indicating if it is a valid symbol
// for a file, i.e. if it is an integer between 1 and 8, inclusive.
bool ChessSquare::isValidRank(char rank) {
    if (!isdigit(rank)) return false;
    int rankAsInt = rank - '0';
    return isValidRank(rankAsInt);
}

// Private Method: isValidRank
// ===========================
// Takes an int and returns a bool indicating if it is a valid symbol
// for a file, i.e. if it is an integer between 1 and 8, inclusive.
bool ChessSquare::isValidRank(int rank) {
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

    // Calculate the Euclidean distance between the coordinates.
    // If the distance is less than 2 (i.e. sqrt(1) or sqrt(2)),
    // then the squares are adjacent.
    int fileDiff = (this->file - other.file);
    int rankDiff = (this->rank - other.rank);
    int squareSum = pow(fileDiff, 2) + pow(rankDiff, 2);

    return (sqrt(squareSum) < 2);
}

// Public Method: isDirectlyBelowDiagonally
// ========================================
bool ChessSquare::isDirectlyBelowDiagonally(const ChessSquare& other)
                                            const {

    // Return true if rank is directly below (i.e. difference is 1) and
    // file is to the right or left (i.e. absolute difference is 1).
    int fileDiff = (this->file - other.file);
    int rankDiff = (this->file - other.file);
    return ((rankDiff == 1) && (abs(fileDiff) == 1));
}

// Public Method: isDirectlyAboveDiagonally
// ========================================
bool ChessSquare::isDirectlyAboveDiagonally(const ChessSquare& other)
                                            const {

    // Return true if rank is directly above (i.e. difference is -1)
    // and file is to the right or left (i.e. absolute difference is 1).
    int fileDiff = (this->file - other.file);
    int rankDiff = (this->file - other.file);
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
ostream& operator<<(ostream& os, const ChessSquare square) {
    os << square.file << square.rank;
    return os;
}
