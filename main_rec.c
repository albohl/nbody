#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "star.h"

#ifdef ANIMATE
#include <X11/Xlib.h>
#include <X11/Xutil.h>

//Size of the window
#define X_SIZE 800
#define Y_SIZE 800
#endif

#define prec float
#define PI 3.14159265359
#define G 1

//Delta time
static prec gdt = 0.3;


static void update_position(struct star* str, prec time_unit)
{
  prec xacc = readXForce(str) / readMass(str);
  prec xSpeedIncrease = xacc * time_unit;
  prec yacc = readYForce(str) / readMass(str);
  prec ySpeedIncrease = yacc * time_unit;
  prec newXSpeed = readXSpeed(str) + xSpeedIncrease;
  prec newYSpeed = readYSpeed(str) + ySpeedIncrease;
  newSpeed(str, newXSpeed, newYSpeed);
  prec xPosIncrease = readXSpeed(str) * time_unit + yacc * pow(time_unit, 2.0)/2;
  prec yPosIncrease = readYSpeed(str) * time_unit + yacc * pow(time_unit, 2.0)/2;
  prec newXPos = readXPos(str) + xPosIncrease;
  prec newYPos = readYPos(str) + yPosIncrease;
  newPos(str, newXPos, newYPos);
}


static void resetForce(struct star* str) {
  newForce(str, 0, 0);
} 

static void addForce(struct star* star_A, struct star* star_B)
{
  prec dx = readXPos(star_A) - readXPos(star_B);
  prec dy = readYPos(star_A) - readYPos(star_B);
  prec distance = (double)sqrt(pow(dx, 2.0) + pow(dy, 2.0));
  prec force = (prec)(G * (double)readMass(star_A) * (double)readMass(star_B) / distance);
  prec fx = force * dx / distance;
  prec fy = force * dy / distance;
  prec newXForceA = readXForce(star_A) + fx;
  prec newXForceB = readXForce(star_B) - fx;
  prec newYForceA = readYForce(star_A) + fy;
  prec newYForceB = readYForce(star_B) - fy;
  newForce(star_A, newXForceA, newYForceA);
  newForce(star_B, newXForceB, newYForceB);
}

// Generates a pseudo-random number in the interval 0 to 1
static prec newRand() 
{
  prec r = (prec)((double)rand()/(double)RAND_MAX);
  return r;
}


void generate_init_values(int number_of_stars, struct star* star_array)
{
  time_t t;
  srand((unsigned) time(&t));
  for(int i = 0; i < number_of_stars; ++i){
    star_array[i] = makeStar();
    prec angle = 360 * newRand();
    prec radius = 100 * newRand();
    newPos(&star_array[i],  radius * cos(angle) + 350, 0.5 * radius * sin(angle) + 350);
    newSpeed(&star_array[i], 0.4*(star_array[i].ypos - 350), (-0.4)*(star_array[i].xpos - 350));
    newMass(&star_array[i], 2*newRand() + 2);
  }

}

static void resetForces(int number_of_stars, struct star* star_array)
{
  for(int i = 0; i < number_of_stars; ++i){
    resetForce(&star_array[i]);
  }
}

static void updateForces(int firstStar, int secondStar, struct star* star_array)
{
  if (firstStar > 0){
    if (secondStar > 1){
    addForce(&star_array[firstStar],&star_array[secondStar]);
    updateForces(firstStar, secondStar - 1, star_array);
    }else{
      updateForces(firstStar - 1, firstStar - 2, star_array);
    }
  }
}

// Manually copy coordinates from stars into points (to be drawn).
// Look at the manual file for XPoint to see which 
// format XPoint accepts its coordinates in.
#ifdef ANIMATE
static void copyToXBuffer(struct star* star_array, XPoint* points, int number_of_stars)
{
  for(int i = 0; i < number_of_stars; ++i){
    points[i].x = readXPos(&star_array[i]);
    points[i].y = readYPos(&star_array[i]);
  }

}
#endif

int main(int argc, char* argv[]) {

  int number_of_stars = 200;
  int iterations = 1000;
  prec time_unit = gdt;

  if(argc == 3)
    {
      number_of_stars = atoi(argv[1]);
      iterations = atoi(argv[2]);
    }
  struct star* star_array = malloc(sizeof(struct star) * number_of_stars);
  generate_init_values(number_of_stars, star_array);
  
  
  
  
  
#ifdef ANIMATE
  XPoint* points = malloc(sizeof(XPoint)*number_of_stars);
  Display* disp;
  Window window, rootwin;
  int screen;

  disp = XOpenDisplay(NULL);
  screen = DefaultScreen(disp);
  rootwin = RootWindow(disp,screen);
  window = XCreateSimpleWindow(disp,rootwin,
                               0,0,X_SIZE,Y_SIZE,1,0,0);
  GC gc = XCreateGC(disp, window, 0, 0);
  XSetForeground(disp, gc, WhitePixel(disp, screen));
  XSetBackground(disp, gc, BlackPixel(disp, screen));
  XMapWindow(disp,window);

  XClearWindow(disp,window);	
	
  copyToXBuffer(star_array, points, number_of_stars);
  XDrawPoints(disp, window, gc, points, number_of_stars, 0);

  XFlush(disp);

#endif

  clock_t start = clock();
  for(int i = 0; i < iterations; i++)
    {

#ifndef ANIMATE
      
      resetForces(number_of_stars, star_array);
      updateForces(number_of_stars, number_of_stars - 1, star_array);
      for(int j = 0; j < number_of_stars; ++j){
        update_position(&star_array[j], time_unit);
      }

#endif
     
#ifdef ANIMATE

      resetForces(number_of_stars, star_array);
      updateForces(number_of_stars, number_of_stars - 1, star_array);
      for(int j = 0; j < number_of_stars; ++j){
        update_position(&star_array[j], time_unit);


        copyToXBuffer(star_array, points,number_of_stars );
        XDrawPoints(disp, window, gc, points, number_of_stars, CoordModeOrigin);
	

      }
      XClearWindow(disp,window);

    
#endif
 
    }
  clock_t stop = clock();
  float diff = (float)(stop - start)/CLOCKS_PER_SEC;
  printf("Total: %lf seconds\n",diff);
  printf("Bodies: %d\n",number_of_stars);
  printf("Iterations: %d\n", iterations);

#ifdef ANIMATE
  free(points);
  XCloseDisplay(disp);
#endif
  free(star_array);
  return 0;
}
