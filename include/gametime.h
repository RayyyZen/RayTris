#ifndef GAMETIME_H
#define GAMETIME_H

#include "library.h"

#define MINSPEED 100 //in ms (milliseconds)
#define MAXSPEED 50

typedef struct{
    time_t start;
    int elapsedTime;
    int speed; //in ms (milliseconds) in order to give it as an argument to wtimeout()
}Timer;

#endif