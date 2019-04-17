
CXX = g++
CV = `pkg-config --cflags --libs opencv`

bin/UDP.o: UDP.cpp
	$(CXX) -c -o bin/UDP.o UDP.cpp $(CV)

bin/Target.o: Target.cpp
	$(CXX) -c -o bin/Target.o Target.cpp $(CV)

bin/PostProcessor.o: PostProcessor.cpp
	$(CXX) -c -o bin/PostProcessor.o PostProcessor.cpp $(CV)

Main: bin/PostProcessor.o bin/Target.o bin/UDP.o
	$(CXX) -o Main Main.cpp bin/PostProcessor.o bin/Target.o bin/UDP.o $(CV)

clean:
	rm Main
	rm bin/*