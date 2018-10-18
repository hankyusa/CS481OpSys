race: race.c
	gcc -pthread -o race race.c

raceWithMutex: raceWithMutex.c
	gcc -pthread -o raceWithMutex raceWithMutex.c

raceWithMutexAndProcesses: raceWithMutexAndProcesses.c
	gcc -pthread -o raceWithMutexAndProcesses raceWithMutexAndProcesses.c

raceWithSemaphoresAndProcesses: raceWithSemaphoresAndProcesses.c
	gcc -lrt -o raceWithSemaphoresAndProcesses raceWithSemaphoresAndProcesses.c

test_race: race
	./race
	./race
	./race
	./race
	./race
	./race
	./race
	./race
	./race
	./race
	./race
	./race
	./race
	./race
	./race

test_raceWithMutex: raceWithMutex
	./raceWithMutex
	./raceWithMutex
	./raceWithMutex
	./raceWithMutex
	./raceWithMutex
	./raceWithMutex
	./raceWithMutex
	./raceWithMutex
	./raceWithMutex
	./raceWithMutex
	./raceWithMutex
	./raceWithMutex
	./raceWithMutex
	./raceWithMutex
	./raceWithMutex

test_raceWithMutexAndProcesses: raceWithMutexAndProcesses
	./raceWithMutexAndProcesses
	./raceWithMutexAndProcesses
	./raceWithMutexAndProcesses
	./raceWithMutexAndProcesses
	./raceWithMutexAndProcesses
	./raceWithMutexAndProcesses
	./raceWithMutexAndProcesses
	./raceWithMutexAndProcesses
	./raceWithMutexAndProcesses
	./raceWithMutexAndProcesses
	./raceWithMutexAndProcesses
	./raceWithMutexAndProcesses
	./raceWithMutexAndProcesses
	./raceWithMutexAndProcesses
	./raceWithMutexAndProcesses

test_raceWithSemaphoresAndProcesses: raceWithSemaphoresAndProcesses
	./raceWithSemaphoresAndProcesses
	./raceWithSemaphoresAndProcesses
	./raceWithSemaphoresAndProcesses
	./raceWithSemaphoresAndProcesses
	./raceWithSemaphoresAndProcesses
	./raceWithSemaphoresAndProcesses
	./raceWithSemaphoresAndProcesses
	./raceWithSemaphoresAndProcesses
	./raceWithSemaphoresAndProcesses
	./raceWithSemaphoresAndProcesses
	./raceWithSemaphoresAndProcesses
	./raceWithSemaphoresAndProcesses
	./raceWithSemaphoresAndProcesses
	./raceWithSemaphoresAndProcesses
	./raceWithSemaphoresAndProcesses