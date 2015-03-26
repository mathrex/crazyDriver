
#pragma once
#include "Object3D.h"
#include "Circle2D.h"
#include "Point2D.h"
#include "Visual2D.h"
#include "Sphere.h"
#include "Transform3D.h"
#include "DrawingWindow.h"

#define PI 3.14159265358979323846

// Obstacol mobil
class Enemy {

public:	Object3D *car, *contour_car;
		Object3D *wheels_enemy[3];
		float current_pos_x, current_pos_y, current_pos_z, dist;
		Point3D *points_wheels_enemy[3];

	Enemy(Point3D p, Color c) {

	vector <Point3D*> vertices;
	vector <Face*> faces;
	
	//varfurile de jos
	vertices.push_back(new Point3D(0, 0, 0));
	vertices.push_back(new Point3D(-0.2, 0, 0));
	vertices.push_back(new Point3D(-0.2, 0, -0.2));
	vertices.push_back(new Point3D(0, 0, -0.2));
	//varfurile de sus
	vertices.push_back(new Point3D(0, -0.2, 0));
	vertices.push_back(new Point3D(-0.2, -0.2, 0));
	vertices.push_back(new Point3D(-0.2, -0.2, -0.2));
	vertices.push_back(new Point3D(0, -0.2, -0.2));
	
	//cele 6 fete
	vector <int> contour;
	//fata jos
	contour.clear();
	contour.push_back(0);
	contour.push_back(1);
	contour.push_back(2);
	contour.push_back(3);
	faces.push_back(new Face(contour));
	//fata sus
	contour.clear();
	contour.push_back(4);
	contour.push_back(5);
	contour.push_back(6);
	contour.push_back(7);
	faces.push_back(new Face(contour));
	//fata fata
	contour.clear();
	contour.push_back(0);
	contour.push_back(1);
	contour.push_back(5);
	contour.push_back(4);
	faces.push_back(new Face(contour));
	//fata dreapta
	contour.clear();
	contour.push_back(1);
	contour.push_back(2);
	contour.push_back(6);
	contour.push_back(5);
	faces.push_back(new Face(contour));
	//fata spate
	contour.clear();
	contour.push_back(2);
	contour.push_back(3);
	contour.push_back(7);
	contour.push_back(6);
	faces.push_back(new Face(contour));
	//fata stanga
	contour.clear();
	contour.push_back(3);
	contour.push_back(0);
	contour.push_back(4);
	contour.push_back(7);
	faces.push_back(new Face(contour));
	
	car = new Object3D(vertices,faces,c,true);
	contour_car = new Object3D(vertices,faces,Color(1,1,1),false);

	vertices.clear();
	//varfurile de jos
	vertices.push_back(new Point3D(0, 0, 0));
	vertices.push_back(new Point3D(-0.1 , 0, 0));
	vertices.push_back(new Point3D(-0.1, 0, -0.1));
	vertices.push_back(new Point3D(0, 0, -0.1));
	//varfurile de sus
	vertices.push_back(new Point3D(0, -0.2, 0));
	vertices.push_back(new Point3D(-0.1, -0.2, 0));
	vertices.push_back(new Point3D(-0.1, -0.2, -0.1));
	vertices.push_back(new Point3D(0, -0.2, -0.1));
	
	//cele 6 fete
	
	//fata jos
	contour.clear();
	contour.push_back(0);
	contour.push_back(1);
	contour.push_back(2);
	contour.push_back(3);
	faces.push_back(new Face(contour));
	//fata sus
	contour.clear();
	contour.push_back(4);
	contour.push_back(5);
	contour.push_back(6);
	contour.push_back(7);
	faces.push_back(new Face(contour));
	//fata fata
	contour.clear();
	contour.push_back(0);
	contour.push_back(1);
	contour.push_back(5);
	contour.push_back(4);
	faces.push_back(new Face(contour));
	//fata dreapta
	contour.clear();
	contour.push_back(1);
	contour.push_back(2);
	contour.push_back(6);
	contour.push_back(5);
	faces.push_back(new Face(contour));
	//fata spate
	contour.clear();
	contour.push_back(2);
	contour.push_back(3);
	contour.push_back(7);
	contour.push_back(6);
	faces.push_back(new Face(contour));
	//fata stanga
	contour.clear();
	contour.push_back(3);
	contour.push_back(0);
	contour.push_back(4);
	contour.push_back(7);
	faces.push_back(new Face(contour));

	wheels_enemy[0] = new Object3D(vertices, faces, Color(0.6, 0.6, 0.6), true);
	wheels_enemy[1] = new Object3D(vertices, faces, Color(0.6, 0.6, 0.6), true);
	wheels_enemy[2] = new Object3D(vertices, faces, Color(0.6, 0.6, 0.6), true);
	wheels_enemy[3] = new Object3D(vertices, faces, Color(0.6, 0.6, 0.6), true);

	points_wheels_enemy[0] = new Point3D(0.03, -0.1, 0);
	points_wheels_enemy[1] = new Point3D(-0.15, -0.1, 0);
	points_wheels_enemy[2] = new Point3D(-0.2, -0.3, 0.2);
	points_wheels_enemy[3] = new Point3D(0.05, -0.3, 0.2);

	Transform3D :: loadIdentityProjectionMatrix();
	Transform3D :: perspectiveProjectionMatrix(p.x - 2,5, 4);
	Transform3D :: loadIdentityModelMatrix();
	Transform3D :: translateMatrix(p.x,p.y,p.z);
	Transform3D :: applyTransform(car);
	Transform3D :: applyTransform(contour_car);
	
	int i;
	for(i = 0; i < 4; i++) {
		Transform3D :: loadIdentityModelMatrix();
		Transform3D :: translateMatrix(p.x + points_wheels_enemy[i]->x,p.y + points_wheels_enemy[i]->y, p.z + points_wheels_enemy[i]->z);
		Transform3D :: applyTransform(wheels_enemy[i]);


	}
	if (p.x < -0.25)
				dist = -0.005;
			else
				if(p.x < 0)
					dist = -0.001;
				else
					if(p.x < 0.25)
						dist = 0.001;
					else
						dist = 0.004;

	current_pos_x = p.x;
	current_pos_y = p.y;
	current_pos_z = p.z;

	}

	void addObst_to_Visual2D (Visual2D *context) {
	
			DrawingWindow :: addObject3D_to_Visual2D(wheels_enemy[0], context);
			DrawingWindow :: addObject3D_to_Visual2D(wheels_enemy[1], context);
			

		DrawingWindow :: addObject3D_to_Visual2D(car, context);
		DrawingWindow :: addObject3D_to_Visual2D(contour_car, context);
		
	
	}
	void move_car(int direction, int level){
	
		int i;

		if (direction == 1)	{	//sus
			current_pos_y += 0.01*level;
			current_pos_x -= dist/3 *level;
		}
		else { //jos
			current_pos_y -= 0.03*level;
			current_pos_x += dist *level;
		}
			Transform3D :: loadIdentityProjectionMatrix();
			Transform3D :: perspectiveProjectionMatrix(current_pos_x - 1, 5, 4);
			Transform3D :: loadIdentityModelMatrix();
			Transform3D :: translateMatrix(current_pos_x, current_pos_y, current_pos_z);
			Transform3D :: applyTransform(car);
			Transform3D :: applyTransform(contour_car);

			for(i = 0; i < 2; i++) {
				Transform3D :: loadIdentityModelMatrix();
				Transform3D :: translateMatrix(points_wheels_enemy[i]->x + current_pos_x, current_pos_y + points_wheels_enemy[i]->y, current_pos_z + points_wheels_enemy[i]->z);
				Transform3D :: applyTransform(wheels_enemy[i]);

			}

		
	}
	void remove_car(Visual2D *context) {
		
		DrawingWindow :: removeObject3D_from_Visual2D(car, context);
		DrawingWindow :: removeObject3D_from_Visual2D(contour_car, context);

			DrawingWindow :: removeObject3D_from_Visual2D(wheels_enemy[0], context);
			DrawingWindow :: removeObject3D_from_Visual2D(wheels_enemy[1], context);

	}
	~Enemy(){}
};