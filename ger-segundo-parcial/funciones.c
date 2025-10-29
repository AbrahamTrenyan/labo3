#include <stdlib.h>

int num_random(int desde, int hasta) {
	return rand()%(hasta-desde)+desde;
}

