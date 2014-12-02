PIECE_OBJ := Pawn.o Knight.o Bishop.o Rook.o Queen.o King.o
COMMON_OBJ := $(PIECE_OBJ) ChessBoard.o ChessSet.o ChessPiece.o ChessSquare.o
EXE_OBJ = $(COMMON_OBJ) ChessMain.o
TEST_OBJ = $(COMMON_OBJ) Test.o
EXE = chess
TEST = test
INC = *.d
OBJ = *.o
GCC = g++
CFLAGS = -Wall -g -MMD -std=c++11

$(EXE): $(EXE_OBJ)
	$(GCC) $(CFLAGS) $(EXE_OBJ) -o $(EXE)

$(TEST): $(TEST_OBJ)
	$(GCC) $(CFLAGS) $(TEST_OBJ) -o $(TEST)

%.o: %.cpp
	$(GCC) $(CFLAGS) -c $< -o $@

-include $(OBJ:.o=.d)

clean:
	rm -f $(OBJ) $(INC) $(EXE)
