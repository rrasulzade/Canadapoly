CXX = g++
CXXFLAGS = -Wall -MMD -std=c++17
EXEC = canadopoly
OBJECTS = main.o player.o gameBoard.o textDisplay.o controller.o slot.o collectible.o property.o service.o railroad.o chance.o redCross.o dice.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
