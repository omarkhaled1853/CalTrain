#include <pthread.h>
#include "caltrain.h"



void
station_init(struct station *station)
{
	station->number_of_empty_seats = 0;
	station->number_of_waitting_passengers = 0;
	station->number_of_passengers_walking_in_the_train = 0;

	pthread_mutex_init(&(station->mutex), NULL);
	pthread_cond_init(&(station->cond_train_is_ready_to_move), NULL);
	pthread_cond_init(&(station->cond_train_arrived_with_at_least_one_empty_seat), NULL);
}

void
station_load_train(struct station *station, int count)
{
	// lock
	pthread_mutex_lock(&station->mutex);
	// wait untill last passengers seat
	while(count != 0 && station->number_of_waitting_passengers != 0){
		// signal all passengers waiting for train with at least one empty seat
		station->number_of_empty_seats = count;

		pthread_cond_broadcast(&station->cond_train_arrived_with_at_least_one_empty_seat);
		// wait untill all passengers seat on the train
		pthread_cond_wait(&station->cond_train_is_ready_to_move, &station->mutex);
        break;
	}
	// unlock
	pthread_mutex_unlock(&station->mutex);

}

void
station_wait_for_train(struct station *station)
{
	// lock
	pthread_mutex_lock(&station->mutex);
	station->number_of_waitting_passengers++;
	// wait until train arrived with at least one empty seat
	while(station->number_of_empty_seats == 0){
		pthread_cond_wait(&station->cond_train_arrived_with_at_least_one_empty_seat, &station->mutex);
	}
	station->number_of_waitting_passengers--;
	station->number_of_empty_seats--;
	station->number_of_passengers_walking_in_the_train++;
	// unlock
	pthread_mutex_unlock(&station->mutex);
}

void
station_on_board(struct station *station)
{
	// lock
	pthread_mutex_lock(&station->mutex);
	station->number_of_passengers_walking_in_the_train--;
	// if(full train) -> move
	if(station->number_of_passengers_walking_in_the_train == 0){
		if(station->number_of_empty_seats == 0 || station->number_of_waitting_passengers == 0){
			pthread_cond_signal(&station->cond_train_is_ready_to_move);
		}
	}
	// unlock
	pthread_mutex_unlock(&station->mutex);
}