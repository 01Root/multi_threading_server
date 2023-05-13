client : File.o ThreadSafeQueue.o serverSocket.o Task.o server.o
	g++ File.o ThreadSafeQueue.o serverSocket.o Task.o server.o -o server.exe -pthread

File.o : ./utils/File.cpp ./utils/File.h
	g++ -c ./utils/File.cpp -o File.o

ThreadSafeQueue.o : ./utils/ThreadSafeQueue.cpp ./utils/ThreadSafeQueue.h
	g++ -c ./utils/ThreadSafeQueue.cpp -o ThreadSafeQueue.o

serverSocket.o : serverSocket.cpp serverSocket.h
	g++ -c serverSocket.cpp -o serverSocket.o

server.o : server.cpp
	g++ -c server.cpp -o server.o

Task.o : Task.cpp Task.h
	g++ -c Task.cpp -o Task.o

clean:
	rm -f *.o
	rm -rf ./utils/*.o

