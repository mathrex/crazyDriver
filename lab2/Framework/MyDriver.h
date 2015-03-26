
#pragma once
#include "Object3D.h"
#include "Circle2D.h"
#include "Point2D.h"
#include "Visual2D.h"
#include "Sphere.h"

#define PI 3.14159265358979323846

class MyDriver {

public:	Object3D *car, *contour_car;
		Object3D *wheels[3];
		float x_projection, y_projection, z_projection;
		float x_trans_right, x_trans_left, z_trans;
		float current_pos_x, current_pos_y, current_pos_z;
		Point3D *points_wheels[3];
	MyDriver() {

	vector <Point3D*> vertices;
	vector <Face*> faces;
	
	//varfurile de jos
	vertices.push_back(new Point3D(0, 0, 0));
	vertices.push_back(new Point3D(-0.3, 0, 0));
	vertices.push_back(new Point3D(-0.3, 0, -0.4));
	vertices.push_back(new Point3D(0, 0, -0.4));
	//varfurile de sus
	vertices.push_back(new Point3D(0, -0.3, 0));
	vertices.push_back(new Point3D(-0.3, -0.3, 0));
	vertices.push_back(new Point3D(-0.3, -0.3, -0.4));
	vertices.push_back(new Point3D(0, -0.3, -0.4));
	
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
	
	car = new Object3D(vertices,faces,Color(0,0.3,0.5),true);
	contour_car = new Object3D(vertices,faces,Color(1,0.3,0.5),false);

	//cele 4 roti ale masinii
	vertices.clear();
	//varfurile de jos
	vertices.push_back(new Point3D(0, 0, 0));
	vertices.push_back(new Point3D(-0.15, 0, 0));
	vertices.push_back(new Point3D(-0.15, 0, -0.15));
	vertices.push_back(new Point3D(0, 0, -0.15));
	//varfurile de sus
	vertices.push_back(new Point3D(0, -0.15, 0));
	vertices.push_back(new Point3D(-0.15, -0.15, 0));
	vertices.push_back(new Point3D(-0.15, -0.15, -0.15));
	vertices.push_back(new Point3D(0, -0.15, -0.15));
	
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

	wheels[0] = new Object3D(vertices, faces,Color(1,1,1), true);
	wheels[1] = new Object3D(vertices, faces,Color(1,1,1), true);
	wheels[2] = new Object3D(vertices, faces,Color(1,1,1), true);
	wheels[3] = new Object3D(vertices, faces,Color(1,1,1), true);

	points_wheels[0] = new Point3D(0.03, -0.3, 0);
	points_wheels[1] = new Point3D(-0.25, -0.3, 0);
	points_wheels[2] = new Point3D(-0.25, -0.3, -0.6);
	points_wheels[3] = new Point3D(0.05, -0.3, -0.6);

	Transform3D :: loadIdentityProjectionMatrix();
	Transform3D :: perspectiveProjectionMatrix(0.1,-1, 2.5);
	Transform3D :: loadIdentityModelMatrix();
	Transform3D :: translateMatrix(0,-4,0);
	Transform3D :: applyTransform(car);
	Transform3D :: applyTransform(contour_car);
	
	int i;
	for(i = 0; i < 4; i++) {
		Transform3D :: loadIdentityModelMatrix();
		Transform3D :: translateMatrix(points_wheels[i]->x,-4 + points_wheels[i]->y, points_wheels[i]->z);
		Transform3D :: applyTransform(wheels[i]);


	}
	
	
	x_trans_right = 0;
	x_trans_left = 0;
	current_pos_x = 0.1;
	current_pos_y = -5;
	current_pos_z = 2.5;

	}

	void addCar_to_Visual2D (Visual2D *context) {
	
		int i;
		
		for(i = 0; i < 4; i++)
			DrawingWindow :: addObject3D_to_Visual2D(wheels[i], context);

		DrawingWindow :: addObject3D_to_Visual2D(car, context);
		DrawingWindow :: addObject3D_to_Visual2D(contour_car, context);
		
	
	}
	void move_car(int direction){
	
		int i;

		if (direction == 1)	{	//dreapta
			x_trans_left = x_trans_right;
			x_trans_right += 0.2;
			if (x_trans_right >= 2.3) {
				x_trans_right -= 0.2;
				x_trans_left = x_trans_right + 0.2;
			}

			Transform3D :: loadIdentityProjectionMatrix();
			Transform3D :: perspectiveProjectionMatrix(0.1,-1, 2.5);
			Transform3D :: loadIdentityModelMatrix();
			Transform3D :: translateMatrix(x_trans_right,-4,0);
			Transform3D :: applyTransform(car);
			Transform3D :: applyTransform(contour_car);

			for(i = 0; i < 4; i++) {
				Transform3D :: loadIdentityModelMatrix();
				Transform3D :: translateMatrix(points_wheels[i]->x + x_trans_right,-4 + points_wheels[i]->y, points_wheels[i]->z);
				Transform3D :: applyTransform(wheels[i]);

	}

		}
		else {	//stanga
			x_trans_right = x_trans_left;
			
			x_trans_left -= 0.2;
			if (x_trans_left <= -2.3) {
				x_trans_left += 0.2;
				x_trans_right = x_trans_left - 0.2;
			}
			Transform3D :: loadIdentityProjectionMatrix();
			Transform3D :: perspectiveProjectionMatrix(0.1,-1, 2.5);
			Transform3D :: loadIdentityModelMatrix();
			Transform3D :: translateMatrix(x_trans_left,-4,0);
			Transform3D :: applyTransform(car);
			Transform3D :: applyTransform(contour_car);


			for(i = 0; i < 4; i++) {
				Transform3D :: loadIdentityModelMatrix();
				Transform3D :: translateMatrix(points_wheels[i]->x + x_trans_left,-4 + points_wheels[i]->y, points_wheels[i]->z);
				Transform3D :: applyTransform(wheels[i]);

			}

		}

	}
	void remove_car(Visual2D *context) {
		int i;
		DrawingWindow :: removeObject3D_from_Visual2D(car, context);
		DrawingWindow :: removeObject3D_from_Visual2D(contour_car, context);

		for(i = 0; i < 4; i++)
			DrawingWindow :: removeObject3D_from_Visual2D(wheels[i], context);
	}
};