race: race.c
	gcc -pthread -o race race.c

raceWithMutex: raceWithMutex.c
	gcc -pthread -o raceWithMutex raceWithMutex.c

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
