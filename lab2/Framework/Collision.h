

#pragma once
#include "..\dependente\freeglut.h"
#include <iostream>
#include "Obstacle.h"
#include "Polygon2D.h"
#include "Object2D.h"
#include "Visual2D.h"
#include "MyDriver.h"
#include <math.h>

#define MIN(x,y) (x < y ? x : y)
#define MAX(x,y) (x > y ? x : y)
#define INSIDE 0
#define OUTSIDE 1

int InsidePolygon( Point3D *p, Object3D *poligon); // verifica daca un punct se afla in interiorul unui poligon
int isAttacking(Object3D *car, Object3D *o);    // verifica daca masina s-a intersectat cu un obstacol

