#ifndef PHOTO_SENSOR
#define PHOTO_SENSOR

extern char photo[5];

void init_Photosenor();
int start_Photosensor();
double toVolt(int reading);
char *getPhotoreading(void);

#endif