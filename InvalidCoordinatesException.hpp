// ==========================================
// File:    InvalidCoordinateException.hpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#include <exception>
using namespace std;

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
