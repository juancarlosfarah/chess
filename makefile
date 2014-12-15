PIECE_OBJ := Pawn.o Knight.o Bishop.o Rook.o Queen.o King.o
COMMON_OBJ := $(PIECE_OBJ) ChessBoard.o ChessSet.o ChessPiece.o ChessSquare.o
EXE_OBJ = $(COMMON_OBJ) ChessMain.o
EXE = chess
INC = *.d
OBJ = *.o
GCC = g++
CFLAGS = -Wall -g -MMD -std=c++11

$(EXE): $(EXE_OBJ)
	$(GCC) $(CFLAGS) $(EXE_OBJ) -o $(EXE)

%.o: %.cpp
	$(GCC) $(CFLAGS) -c $< -o $@

-include $(OBJ:.o=.d)

clean:
	rm -f $(OBJ) $(INC) $(EXE)
