#include <pthread.h>
#include "caltrain.h"



void
station_init(struct station *station)
{
	station->number_of_empty_seats = 0;
	station->number_of_passengers_walking_in_the_train = 0;
	station->number_of_waitting_passengers = 0;

	// station->mutex = PTHREAD_MUTEX_INITIALIZER;
}

void
station_load_train(struct station *station, int count)
{
	station->number_of_empty_seats = count;
	// lock
	// wait untill last passengers seat
	while(station->number_of_empty_seats != 0){
		// wait
	}
	// unlock
}

void
station_wait_for_train(struct station *station)
{
	// lock
	station->number_of_waitting_passengers++;
	// wait until train arrived with at least one empty seat
	while(station->number_of_empty_seats == 0){
		// wait
	}
	station->number_of_empty_seats--;
	station->number_of_passengers_walking_in_the_train++;
	// unlock
}

void
station_on_board(struct station *station)
{
	// lock
	station->number_of_passengers_walking_in_the_train--;
	// if(full train) -> move
	while(station->number_of_empty_seats != 0){
		// wait
	}
	// unlock
}
