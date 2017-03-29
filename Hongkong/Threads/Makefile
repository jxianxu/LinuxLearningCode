eventthread:main.o event.o base.o priority.o timer.o notify.o mutex.o
	g++ main.o event.o base.o priority.o timer.o notify.o mutex.o -o eventthread -pthread -g 
main.o:main.cpp EventLoopThread.h
	g++ -c main.cpp -o main.o -pthread -g
event.o:EventLoopThread.cpp PriorityQueue.h NotifyEvent.h EventLoopThread.h TimerManager.h BaseThread.h common.h
	g++ -c EventLoopThread.cpp -o event.o -pthread -g
priority.o:PriorityQueue.cpp PriorityQueue.h Mutex.h
	g++ -c PriorityQueue.cpp -o priority.o -pthread -g
timer.o:TimerManager.cpp TimerManager.h BaseThread.h Mutex.h
	g++ -c TimerManager.cpp -o timer.o -pthread -g
mutex.o:Mutex.cpp Mutex.h
	g++ -c Mutex.cpp -o mutex.o -pthread -g
base.o:BaseThread.cpp BaseThread.h errorCodes.h
	g++ -c BaseThread.cpp -o base.o -pthread -g
notify.o:NotifyEvent.cpp NotifyEvent.h errorCodes.h
	g++ -c NotifyEvent.cpp -o notify.o -pthread -g
clean:
	rm -rf *.o eventthread
	
