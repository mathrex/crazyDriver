
#pragma once
#include "..\dependente\freeglut.h"
#include <iostream>
#include "Framework/Object3D.h"
#include "Framework/Obstacle.h"
#include "Framework/MyDriver.h"
#include "Framework/Collision.h"
#include <math.h>



int InsidePolygon (Point3D *p, Object3D *poligon) {

	int counter = 0;
	int i, n;
	Point3D *p1, *p2;
	float newx;

	n = poligon->transf_vertices.size();
	p1 = poligon->transf_vertices[0];
	
	for (i = 1; i <= n; i++) {
		
		p2 = poligon->transf_vertices[i % n];

		if (p->x == p2->x && p->y == p2->y)
			return INSIDE;

		if (p->y > MIN (p1->y,p2->y)) {

			if (p->y <= MAX (p1->y, p2->y)) {

				if (p->x <= MAX(p1->x, p2->x)) {

					newx = (p->y - p1->y) * (p2->x - p1->x) / (p2->y - p1->y) + p1->x;
					if (p1->x == p2->y || p->x <= newx)
						counter ++;
				}
			}
		}

		p1 = p2;
	}

	if (counter % 2 == 0)
		return(OUTSIDE);
	else
		return (INSIDE);

}


int isAttacking(Object3D *car, Object3D *o) {

		int i,j;

		for(j = 0; j < car->transf_vertices.size(); j++) 

			if (InsidePolygon(car->transf_vertices[j], o) == INSIDE) {
				return 1;
			
				
			}

		return 0;
	}

