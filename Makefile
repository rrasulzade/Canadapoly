CXX = g++
CXXFLAGS = -Wall -MMD -std=c++17
EXEC = bb7k
OBJECTS = main.o player.o gameBoard.o textDisplay.o controller.o slot.o ownable.o academic.o gym.o residence.o slc.o needleshall.o dice.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
