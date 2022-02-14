CXX = clang++
CXXFLAGS = -Wall -g -std=c++11
COMPILER = ${CXX} ${CPPFLAGS} ${CXXFLAGS} ${LDFLAGFS}
EXEC = example

All: ${EXEC}

# ${EXEC}: example.cpp 
# 	${COMPILER} test.cpp -o ${EXEC}

clean:
	rm -f ${wildcard *.o} ${EXEC}
