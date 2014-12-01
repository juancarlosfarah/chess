// ==========================================
// File:    ChessSquare.cpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#include <cctype>
#include <iostream>
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
