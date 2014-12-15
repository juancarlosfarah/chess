// ==========================================
// File:    InvalidCoordinateException.hpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#include <exception>
using namespace std;

// Class: InvalidCoordinatesException
// ==================================
// This class extends the exception class to define
// a specific exception that is designed to be thrown
// whenever an operation in the Chess program fails
// due to coordinates that are not valid. It is
// implemented specifically in the ChessSquare constructor
// in order to avoid constructing invalid ChessSquares.
class InvalidCoordinatesException : public exception {

    private:
        const char* message;

    public:

        // Constructor: Default
        // ====================
        InvalidCoordinatesException() {
            this->message = "Invalid coordinates!";
        }

        // Constructor:
        // ============
        // Takes a C-style string and constructs an
        // InvalidCoordinatesException object.
        InvalidCoordinatesException(const char* m) : message(m) {}

        // Method: what
        // ============
        // Overrides the what method in the exception superclass.
        const char* what() const throw() {
            return this->message;
        }
};
