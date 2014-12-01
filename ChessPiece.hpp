// ==========================================
// File:    ChessPiece.hpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#ifndef CHESS_PIECE_HPP
#define CHESS_PIECE_HPP

#include <iostream>
#include <string>
using namespace std;

#include "ChessSquare.hpp"

enum Color {White, Black};

class ChessPiece {

    private:
        // Method: initSymbol
        // ==================
        void initSymbol(Color color);

    protected:

        Color color;
        string symbol;
        const ChessSquare* position;

    public:

        // Constructor:
        // ============
        ChessPiece();
        ChessPiece(Color color);
        ChessPiece(Color color, ChessSquare* position);

        // Destructor:
        // ===========
        virtual ~ChessPiece();


        // Method: setPosition
        // ===================
        // Takes a ChessSquare and sets it as the position
        // attribute of this ChessPiece.
        void setPosition(const ChessSquare* cs);

        // Method: getPosition
        // ===================
        // Returns the position attribute of this ChessPiece.
        const ChessSquare* getPosition();

        // Method: print
        // =============
        void print();

        // Method: isValidMove
        // ===================
        virtual bool isValidMove(ChessSquare& square);

        //// Method: getSymbol
        //// =================
        //virtual string getSymbol();

        // Operator: <<
        // ============
        friend ostream& operator<<(ostream& os, ChessPiece piece);
};

#endif
