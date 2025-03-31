# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g
VALFLAGS = --leak-check=full --show-leak-kinds=all --error-exitcode=99 --track-origins=yes --verbose --log-file=valgrind-out.txt

# Source files
SRC = main.cpp Graph.cpp Algorithms.cpp DataStructures.cpp
TEST_SRC = test.cpp Graph.cpp Algorithms.cpp DataStructures.cpp

# Executables
EXEC = Main
TEST_EXEC = test

# Default build
all: $(EXEC)

# Main program
$(EXEC): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(SRC)

# Test target using doctest
test: $(TEST_EXEC)

$(TEST_EXEC): $(TEST_SRC)
	$(CXX) $(CXXFLAGS) -o $(TEST_EXEC) $(TEST_SRC)

run-tests: test
	@echo "🔍 Running tests..."
	@./$(TEST_EXEC) || { echo '❌ Tests failed!'; exit 1; }
	@echo "✅ All tests passed."


# Run with valgrind
valgrind: $(EXEC)
	valgrind $(VALFLAGS) ./$(EXEC)

# Clean build files
clean:
	rm -f $(EXEC) $(TEST_EXEC) *.o valgrind-out.txt

.PHONY: all test valgrind clean
