// Ligne de compilation : gcc -o cam testCam.c `pkg-config --cflags opencv --libs opencv` -ldl -lm
#include <pthread.h>
#include "Information.h"
#include "Picture.h"
#include "Follow.h"

int main(int argc, char** argv) {

	/*
	./cam.out c pour démarrer le tracking de couleur (par défaut)
	./cam.out h pour démarrer le tracking de POI (Harris)
	./cam.out g pour démarrer le tracking de POI (gradient)
	*/

	char type = 'c';
	if(argc >= 2) {
		type = argv[1][0];
	}

	Info* info = malloc(sizeof(Info));
	pthread_t picture, follow;

	info->x = malloc(sizeof(int));
	info->y = malloc(sizeof(int));
	info->isEnd = calloc(1, sizeof(int));
	info->reset = calloc(1, sizeof(int));
	info->sizeX = NULL;
	info->sizeY = NULL;
	info->type = type;


	pthread_create(&picture, NULL, launch_picture, info);
	pthread_create(&follow, NULL, launch_follow, info);

	pthread_join(picture, NULL);
	pthread_join(follow, NULL);

	return 0;
}
