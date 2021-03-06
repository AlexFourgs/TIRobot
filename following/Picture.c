// #include "Picture.h"
// #include "ti_alex.h"
//
// void* waitSecond(void* end_void){
// 	int* end = (int*) end_void;
// 	sleep(10);
// 	*end = 1;
// 	pthread_exit(NULL);
// }
//
// // Fonction lié au clic. Renvoi la position du pixel et sa couleur.
// void mouseEvent(int evt, int x, int y, int flags, void* param) {
// 	Color_pixel* color = (Color_pixel*) param ;
//
// 	// On récupére la couleur du pixel sur lequel on clique.
// 	if(evt==CV_EVENT_LBUTTONDOWN) {
// 		color->r = color->cam->imageData[((x*3)+(y*color->cam->widthStep))+2] ;
// 		color->g = color->cam->imageData[((x*3)+(y*color->cam->widthStep))+1] ;
// 		color->b = color->cam->imageData[((x*3)+(y*color->cam->widthStep))] ;
//
// 		/*pthread_t t;
// 		pthread_create(&t, NULL, waitSecond, color->isEnd);*/
// 	}
//
// }
//
// int colorTracking (IplImage* cap, Color_pixel color, int i, uchar pixel_blue, uchar pixel_green, uchar pixel_red) {
//
// 	// Si les pixels sont de la couleur on les met en rouge.
// 	if ((pixel_blue >= (color.b)-TOLERANCE_B) && (pixel_blue <= (color.b)+TOLERANCE_B) && (pixel_green >= (color.g)-TOLERANCE_G)
// 			&& (pixel_green <= (color.g)+TOLERANCE_G) && (pixel_red >= (color.r)-TOLERANCE_R)	&& (pixel_red <= (color.r)+TOLERANCE_R)){
//
// 		cap->imageData[i] = 0 ;
// 		cap->imageData[i+1] = 0 ;
// 		cap->imageData[i+2] = 255 ;
//
// 		return 1 ;
// 	}
//
// 	return 0 ;
// }
//
// Barycenter barycenterCalculation (int *barycenter_x, int *barycenter_y, int size_x, int size_y, int coefficient, int* isVisible) {
// 	Barycenter coordonnees ;
// 	coordonnees.x = coordonnees.y = 0 ;
//
// 	int i;
// 	int nombre_x = 0 ;
// 	int nombre_y = 0 ;
// 	int compte_x = 0 ;
// 	int compte_y = 0 ;
//
// 	for (i = 0 ; i < size_x/coefficient ; i++){
// 		nombre_x = nombre_x + (i*barycenter_x[i]);
// 		compte_x = compte_x + barycenter_x[i];
// 	}
//
// 	for (i = 0 ; i < size_y/coefficient ; i++){
// 		nombre_y = nombre_y + (i*barycenter_y[i]);
// 		compte_y = compte_y + barycenter_y[i];
// 	}
//
// 	if ((compte_x != 0) && (compte_y != 0)){
// 		coordonnees.x = ((size_x/2) - ((size_x/2)/coefficient)) + nombre_x/compte_x;
// 		coordonnees.y = ((size_y/2) - ((size_y/2)/coefficient)) + nombre_y/compte_y ;
// 		*isVisible = 1;
// 	}
// 	else{
// 		coordonnees.x = size_x/2;
// 		coordonnees.y = size_y/2;
// 		*isVisible = 0;
// 	}
//
// 	return coordonnees ;
// }
//
// void* launch_picture(void* info_void) {
// 	Info* info = (Info*) info_void;
// 	CvPoint* center = malloc(sizeof(CvPoint));
// 	//coefficient
// 	int coefficient = 1;
// 	int isVisible = 0;
//
// 	Color_pixel color ;
// 	color.r = 0 ;
// 	color.g = 255 ;
// 	color.b = 0 ;
// 	//color.isEnd = info->isEnd;
//
// 	Barycenter barycentre_coordonnees ;
// 	barycentre_coordonnees.x = barycentre_coordonnees.y = 0 ;
//
// 	int *barycenter_x ;
// 	int *barycenter_y ;
//
// 	// Déclaration d'un caractère pour la fermeture des fenêtres
// 	char key;
// 	int i, j = 0 ;
//
// 	// Déclaration des images
// 	IplImage* cap ;
// 	IplImage* prev_cap;
//
// 	// Déclaration de l'élément de capture à partir de la webcam
// 	CvCapture *capture ;
//
// 	// Déclaration des différents noms de fenêtres
// 	const char* window_title = "Original Camera" ;
// 	const char* window_title_2 = "Gradient" ;
//
// 	// On choisis la source pour l'image (webcam).
// 	capture = cvCreateCameraCapture (CAMERA);
//
// 	// Si la capture d'image échoue, on arrête le programme avec un message.
// 	if (!capture) {
// 		printf("Ouverture du flux video impossible !\n") ;
// 		*info->isEnd = 1;
// 		pthread_exit(NULL);
// 	}
//
// 	// Création de la fenêtre.
// 	cvNamedWindow (window_title, CV_WINDOW_AUTOSIZE);
//         cvNamedWindow ("win2", CV_WINDOW_AUTOSIZE);
//
// 	uchar pixel_blue ;
// 	uchar pixel_green ;
// 	uchar pixel_red ;
//
// 	// On alloue la mémoire pour nos tableaux de calcul du barycentre
// 	cap = cvQueryFrame(capture);
//         prev_cap = cvQueryFrame(capture);
//
// 	int sizeXCam = cap->width;
// 	int sizeYCam = cap->height;
// 	info->sizeX = &sizeXCam;
// 	info->sizeY = &sizeYCam;
//
// 	//center->x = *info->sizeX/2;
// 	//center->y = *info->sizeY/2;
//
// 	int inSmallMinX = ((*info->sizeX/2) - ((*info->sizeX/2)/COEFFICIENT_MAX));
// 	int inSmallMaxX = ((*info->sizeX/2) + ((*info->sizeX/2)/COEFFICIENT_MAX));
// 	int inSmallMinY = ((*info->sizeY/2) - ((*info->sizeY/2)/COEFFICIENT_MAX));
// 	int inSmallMaxY = ((*info->sizeY/2) + ((*info->sizeY/2)/COEFFICIENT_MAX));
//
// 	/*barycenter_x = calloc(cap->width, sizeof(int));
// 	barycenter_y = calloc(cap->height, sizeof(int));*/
//
// 	// Variable certif
// 	//int click = 0 ;
// 	int nbImage = 0 ;
// 	// Tant qu'on appuie pas sur q le on continu la boucle.
// 	key = cvWaitKey(1);
//
// 	int** norme_grad = (int**)malloc((cap->height-2)*sizeof(int*));
// 	// Gradient sur Y, montre les lignes horizontales
// 	int** img_sobel_vert = (int**)malloc((cap->height-2)*sizeof(int*));
// 	// Gradient sur X, montre les lignes verticales
// 	int** img_sobel_hori = (int**)malloc((cap->height-2)*sizeof(int*));
// 	int** h = (int**)malloc((cap->height-4)*sizeof(int*));
//
// 	for(i = 0 ; i < cap->height-4 ; i++) {
// 		norme_grad[i] = (int*)malloc((cap->width-2)*sizeof(int));
//         	img_sobel_vert[i] = (int*)malloc((cap->width-2)*sizeof(int));
//         	img_sobel_hori[i] = (int*)malloc((cap->width-2)*sizeof(int));
// 		h[i] = (int*)malloc((cap->width-4)*sizeof(int));
// 	}
//
// 	for(i = cap->height-4 ; i < cap->height-2 ; i++) {
// 		norme_grad[i] = (int*)malloc((cap->width-2)*sizeof(int));
//         	img_sobel_vert[i] = (int*)malloc((cap->width-2)*sizeof(int));
//         	img_sobel_hori[i] = (int*)malloc((cap->width-2)*sizeof(int));
// 	}
//
// 	CvPoint* corners = (CvPoint*) malloc(cap->height * cap->width * sizeof(CvPoint));;
// 	CvPoint* corners1 = (CvPoint*) malloc(prev_cap->height * prev_cap->width * sizeof(CvPoint));;
//
//
// 	int corners_nb;
//
// 	int harris_threshold = 500000, harris_lambda = 230;
// 	int lambda_divider = 1000;
//
// 	cvCreateTrackbar("Seuil Harris", "Original Camera", &harris_threshold, 2000000, NULL);
// 	cvCreateTrackbar("Lambda Harris", "Original Camera", &harris_lambda, 250, NULL);
//
// 	nbImage++ ;
//         corners_nb = 0;
// 	int corners_nb1 = 0;
// 	Vector vector;
// 	uchar** image1_gr;
// 	uchar** image2_gr;
//
//         prev_cap = cvQueryFrame(capture);
// 	Match* matches = malloc(500*sizeof(Match));
//
//         // TODO: optimiser img_sobel pour pas malloc à chaque fois
// 	// Ca marche, je sais pas trop pourquoi il faut inverser, mais bon
// 	grad(prev_cap, prev_cap->height, prev_cap->width, &norme_grad, &img_sobel_vert, &img_sobel_hori);
//
//         //gradient_corner_detection(img_sobel_hori, img_sobel_vert, prev_cap->width, prev_cap->height, (float) harris_lambda/lambda_divider, harris_threshold, &corners1, &corners_nb1, &h);
// 	harris(img_sobel_hori, img_sobel_vert, cap->width, cap->height, (float) harris_lambda/lambda_divider,harris_threshold, &corners, &corners_nb, &h);
//
//
//
//         // printf("corners_nb=%d\n", corners_nb);
//         for(i=0 ; i<corners_nb1 ; i++) {
//         	cvCircle(prev_cap, corners1[i], 1, CV_RGB(0,0,255), -1, 8, 0);
//         }
//
// 	//CvPoint* center;
// 	CvPoint* vectors = malloc(sizeof(CvPoint));
// 	CvSize size= {2,2};
// 	while ((key != 'q') && (key != 'Q') && (*info->isEnd == 0)){
// 		//nbImage++ ;
// 		corners_nb = 0;
//
// 		cap = cvQueryFrame(capture);
// 		// TODO: optimiser img_sobel pour pas malloc à chaque fois
//
// 		// Ca marche, je sais pas trop pourquoi il faut inverser, mais bon
// 		grad(cap, cap->height, cap->width, &norme_grad, &img_sobel_vert, &img_sobel_hori);
// 		harris(img_sobel_hori, img_sobel_vert, cap->width, cap->height, (float) harris_lambda/lambda_divider, harris_threshold, &corners, &corners_nb, &h);
//
// 		for(i=0 ; i<corners_nb ; i++) {
// 			cvCircle(cap, corners[i], 1, CV_RGB(0,0,255), -1, 8, 0);
// 		}
//
// 		//calcul le vecteur deplcement
// 		image1_gr = greyscale_img(prev_cap, prev_cap->height, prev_cap->width);
//         image2_gr = greyscale_img(cap, cap->height, cap->width);
//
// 		vector = find_all_matches(image1_gr, image2_gr,cap->height, cap->width, corners1, corners,50,3,matches, corners_nb1, corners_nb);
//
// 		center->x = prev_cap->height/2;
// 		center->y = prev_cap->width/2;
//
// 		vectors->x = center->x + vector.dx;
// 		vectors->y = center->y + vector.dy;
//
// 		cvLine(cap, *center, *vectors,cvScalar(200,200,0,20),6,8,0);
// 		cvShowImage(window_title, cap);
//
// 		cvShowImage("win2", prev_cap);
// 		prev_cap = cvCloneImage(cap);
// 		memcpy(corners1, corners,cap->height * cap->width);
// 		corners_nb1 = corners_nb;
// 		key = cvWaitKey(1);
// 	}
//
// 	/* Tracking rouge
// 	while ((key != 'q') && (key != 'Q') && (*info->isEnd == 0)){
// 		nbImage++ ;
//
// 		if(key == 'r'){
// 			color.r = 0 ;
// 			color.g = 255 ;
// 			color.b = 0 ;
// 			*info->reset = 1;
// 		}
// 		barycenter_x = calloc(cap->width/coefficient, sizeof(int));
// 		barycenter_y = calloc(cap->height/coefficient, sizeof(int));
//
//
// 		// On met la capture de la webcam dans l'attribut cap.
// 		cap = cvQueryFrame(capture);
//
// 		// Si on traite en BGR
// 		color.cam = cap;
//
// 		// Gradient sur Y, montre les lignes horizontales
// 		int** img_sobel_vert = NULL;
// 		// Gradient sur X, montre les lignes verticales
// 		int** img_sobel_hori = NULL;
//
// 		CvPoint* corners = malloc((*info->sizeX) * (*info->sizeY) * sizeof(Point));
// 		int corners_nb = 0;
//
// 		// TODO: optimiser img_sobel pour pas malloc à chaque fois
//
// 		grad(cap, *info->sizeY, *info->sizeX, &img_sobel_vert, &img_sobel_hori);
// 		// printf("%d\n", img_sobel_vert[0][0]);
// 		int** h = harris(img_sobel_hori, img_sobel_vert, *info->sizeX, *info->sizeY, 0.5, &corners, &corners_nb);
//
// 		printf("corners_nb=%d\n", corners_nb);
// 		for(i=0 ; i<corners_nb ; i++) {
// 			cvCircle(cap, corners[i], 5, CV_RGB(0,0,255), -1, 8, 0);
// 		}
// 		if(count == 0) {
// 			printf("%d\n", h[0][0]);
// 		}
//
// 		count ++;
//
// 		//
//
//
// 		// On parcours notre image (les pixels).
// 		int widthMin = ((*info->sizeX/2) - ((*info->sizeX/2)/coefficient));
// 		int widthMax = ((*info->sizeX/2) + ((*info->sizeX/2)/coefficient));
// 		int heightMin = ((*info->sizeY/2) - ((*info->sizeY/2)/coefficient));
// 		int heightMax = ((*info->sizeY/2) + ((*info->sizeY/2)/coefficient));
// 		for (i = widthMin; i < widthMax; i++) {
// 			for (j = heightMin; j < heightMax; j++) {
//
// 				// Pixels B,G,R en fonction de la position.
// 				pixel_blue = (uchar)(cap->imageData[((i*3)+(j*cap->widthStep))]) ;
// 				pixel_green = (uchar)(cap->imageData[((i*3)+(j*cap->widthStep))+1]) ;
// 				pixel_red = (uchar)(cap->imageData[((i*3)+(j*cap->widthStep))+2]) ;
//
// 				// Tracking des pixels en fonction de la couleur.
// 				if(colorTracking(cap, color, ((i*3)+(j*cap->widthStep)), pixel_blue, pixel_green, pixel_red)){
// 					//printf("y = %d, x = %d\n", i/((cap->width)*3), i%((cap->width)*3));
// 					//printf("x = %d, y = %d\n", i/3, j);
// 					barycenter_y[j-heightMin]++ ;
//
// 					barycenter_x[i-widthMin]++ ;
// 				}
// 			}
// 		}
//
// 		// On calcul le barycentre.
// 		barycentre_coordonnees = barycenterCalculation (barycenter_x, barycenter_y, cap->width, cap->height, coefficient, &isVisible) ;
//
// 		// printf("barycentre x main = %d, barycentre y main = %d\n", barycentre_coordonnees.x, barycentre_coordonnees.y);
// 		CvPoint p;
// 		//printf("Barycentre update\n");
// 		p.x = barycentre_coordonnees.x ;
// 		p.y = barycentre_coordonnees.y ;
// 		*info->x = barycentre_coordonnees.x;
// 		*info->y = barycentre_coordonnees.y;
//
// 		cvCircle(cap, p, 5, CV_RGB(0,0,255), -1, 8, 0);
// 		#ifdef DEBUG
// 			cvCircle(cap, center, TOLERANCE_CENTRE, CV_RGB(0,255,0), -1, 8, 0);
// 		#else
// 			cvCircle(cap, center, 10, CV_RGB(0,255,0), -1, 8, 0);
// 		#endif
//
// 		// On affiche la webcam normalement.
// 		cvShowImage(window_title, cap);
// 		// cvShowImage(window_title_2, grad);
// 		cvSetMouseCallback(window_title, mouseEvent, &color);
//
// 		//On modifie si besoin le coefficient
// 		if(isVisible){
// 			if((*info->x > inSmallMinX) && (*info->x < inSmallMaxX) && (*info->y > inSmallMinY) && (*info->y < inSmallMaxY)){
// 				coefficient = COEFFICIENT_MAX;
// 			}
// 		}
// 		else{
// 			coefficient = 1;
// 		}
//
// 		// On réinitialise les barycentres
// 		free(barycenter_x);
// 		free(barycenter_y);
// 		key = cvWaitKey(1);
//
// 		//printf("t2-t1 : %d\n", (int) ((t2-t1)/CLOCKS_PER_SEC));
// 	}
// 	*/
//
// 	//printf("Pour 10 secondes, on a traité %d images.\n", (int)nbImage);
//
//
//     for(i = 0 ; i < cap->height-4 ; i++) {
// 		free(norme_grad[i]);
// 		free(img_sobel_vert[i]);
// 		free(img_sobel_hori[i]);
// 		free(h[i]);
// 	}
//
// 	for(i = cap->height-4 ; i < cap->height-2 ; i++) {
// 		free(norme_grad[i]);
// 		free(img_sobel_vert[i]);
// 		free(img_sobel_hori[i]);
// 		free(h[i]);
// 	}
//
// 	free(norme_grad);
// 	free(img_sobel_vert);
// 	free(img_sobel_hori);
// 	free(h);
// 	free(corners);
//
// 	cvReleaseCapture(&capture);
// 	// cvWaitKey(0);
// 	cvDestroyWindow(window_title);
//
// 	*info->isEnd = 1;
// 	pthread_exit(NULL);
// }
