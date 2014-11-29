// ==========================================
// File:    ChessSquare.cpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#include "ChessSquare.hpp"

// Constructor:
// ============
ChessSquare::ChessSquare(string coords)
                         throw(InvalidCoordinatesException&) {

    char file = coords[0];
    char rank = coords[1];

    // Parse the first and second characters in the string and ensure
    // that they are valid. If so set the properties accordingly.
    if (isValidFile(file) && isValidRank(rank)) {
        this->file = file;
        this->rank = static_cast<int>(rank);
    } else {
        throw InvalidCoordinatesException();
    }
}

// Public Method: getFile
// ======================
// Returns the file property of this ChessSquare.
char ChessSquare::getFile() {
    return this->file;
}

// Public Method: getRank
// ======================
// Returns the rank property of this ChessSquare.
int ChessSquare::getRank() {
    return this->rank;
}

// Private Method: isValidFile
// ===========================
// Takes a char and returns a bool indicating if it is a valid symbol
// for a file, i.e. if it is a letter between A and H, inclusive.
// This method is case insensitive.
bool ChessSquare::isValidFile(char file) {
    return false;
}

// Private Method: isValidRank
// ===========================
// Takes a char and returns a bool indicating if it is a valid symbol
// for a file, i.e. if it is an integer between 1 and 8, inclusive.
bool ChessSquare::isValidRank(char rank) {
    return false;
}
