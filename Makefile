CXX = g++
CXXFLAGS = -Wall -MMD
EXEC = bb7k
OBJECTS = main.o player.o gameBoard.o textDisplay.o slot.o ownable.o academic.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
