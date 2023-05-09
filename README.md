# MultiThreaded-Server
A multi threaded server made using C++ thread libary 

## Description:
A multithreaded server that creates a thread pool with N threads.
When a new client request arrives, the server should add it to a queue of connections.
The threads should remove one connection from the queue and handle the request. If the
connection queue does not have a connection available, the thread should “sleep” until a
connection is ready. The connection queue is shared among all threads and thus requires
synchronization to protect access to the connection queue.
Program should not use busy waiting.

## Purpose:
1. Learn how to use the c++ thread library to manage threads 
2. Understand how to create a multi-threaded server 
3. Understand how and where to use basic thread synchronization 
4. Gain practice with client software that can issue multiple requests over a socket.



