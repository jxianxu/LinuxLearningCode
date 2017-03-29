
mutextest:main.o Mutex.o
	g++ main.o Mutex.o -o mutextest -pthread
main.o: main.cpp Mutex.h
	g++ -c main.cpp -o main.o -g -pthread
Mutex.o: Mutex.cpp Mutex.h
	g++ -c Mutex.cpp -o Mutex.o -pthread

clean:
	rm -rf *.o mutextest
	
