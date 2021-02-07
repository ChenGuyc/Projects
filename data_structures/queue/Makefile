
Queue: queue_test.o queue.o
	gcc queue.o queue.o -o Queue

queue.o: queue.c
	gcc -c queue.c

queue.o: squeue.c queue.h
	gcc -c queue.c

clean:
	rm *.o queue 
