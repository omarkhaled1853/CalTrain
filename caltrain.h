#include <pthread.h>

struct station {
	int number_of_empty_seats;
	int number_of_waitting_passengers;
	int number_of_passengers_walking_in_the_train;

	pthread_mutex_t mutex;
	
	pthread_cond_t cond_train_is_ready_to_move;
	pthread_cond_t cond_train_arrived_with_at_least_one_empty_seat;
};

void station_init(struct station *station);

void station_load_train(struct station *station, int count);

void station_wait_for_train(struct station *station);

void station_on_board(struct station *station);