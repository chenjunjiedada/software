OBJ = message.o
CXXFLAGS = -std=c++11

akuna: $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

.o: .cpp

clean:
	rm $(OBJ) akuna

