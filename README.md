# CPU-usage-tracker

A simple application for retrieving, processing and displaying CPU usage data from proc/stat file in Ubuntu, Linux.
The goal of this project was to showcase a multi-threaded program based on the pthread.h library in C.

There are 3 main threads - a reader, analyzer, and printer, which handle the necessary data and display the core usage in a user-friendly way.
Two additional cores, the logger and the watchdog, are implemented for additional features. The logger thread creates a .log file, 
whereas the supervises all the other threads and terminates the program if an issue was detected.

For the purpose of safe data exchange between threads, two queue types were implemented - a ring buffer queue, and a linked list queue based on atomic operations.
