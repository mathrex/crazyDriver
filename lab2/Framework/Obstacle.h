
#pragma once
#include "Object3D.h"
#include "Point3D.h"
#include "Point2D.h"
#include "Transform3D.h"
#include "Visual2D.h"
#include "DrawingWindow.h"
#include "Transform2D.h"
#include "Sphere.h"

class Obstacle {

public:Object3D *ob;
	int type;	// 0 -piramida
				// 1 - sfera
				// 2 - obiect bonus
	float poz_x, poz_y, poz_z, scale, dist;
	float angle;
	bool is_removed;
	

	Obstacle(Point3D p, Color c, int _type) {
		
		type = _type;
		scale = 1;
		angle = 1;
		is_removed = false;
		vector <Point3D*> vertices;
		vector <Face*> faces;
		vector <int> contour;
		if (_type == 1) {
		
			
			//varfurile de jos
			vertices.push_back(new Point3D(0, 0, 0));
			vertices.push_back(new Point3D(0.1, 0, 0));
			vertices.push_back(new Point3D(0.1, 0, 0.1));
			vertices.push_back(new Point3D(0, 0, 0.1));
			//varful de sus
			vertices.push_back(new Point3D(0.025, 0.6, 0.025));
	
			//cele 5 fete
			
	
			contour.clear();
			contour.push_back(0);
			contour.push_back(1);
			contour.push_back(2);
			contour.push_back(3);
			faces.push_back(new Face(contour));

			contour.clear();
			contour.push_back(0);
			contour.push_back(3);
			contour.push_back(4);
			faces.push_back(new Face(contour));

			contour.clear();
			contour.push_back(2);
			contour.push_back(3);
			contour.push_back(4);
			faces.push_back(new Face(contour));

			contour.clear();
			contour.push_back(1);
			contour.push_back(2);
			contour.push_back(4);
			faces.push_back(new Face(contour));
	
			contour.clear();
			contour.push_back(0);
			contour.push_back(1);
			contour.push_back(4);
			faces.push_back(new Face(contour));
			ob = new Object3D(vertices,faces, c, false);
		}
		else
			if(type == 2)
			ob = new Sphere(Point3D(0,0,0), 0.1, c, false);
			else {

				vertices.clear();
				//varfurile de jos
				vertices.push_back(new Point3D(0, 0, 0));
				vertices.push_back(new Point3D(-0.05, 0, 0));
				vertices.push_back(new Point3D(-0.05, 0, -0.05));
				vertices.push_back(new Point3D(0, 0, -0.05));
				//varfurile de sus
				vertices.push_back(new Point3D(0, -0.05, 0));
				vertices.push_back(new Point3D(-0.05, -0.05, 0));
				vertices.push_back(new Point3D(-0.05, -0.05, -0.05));
				vertices.push_back(new Point3D(0, -0.05, -0.05));
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
				ob = new Object3D(vertices, faces, c, false);
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
	
	Transform3D :: loadIdentityModelMatrix();
	Transform3D :: translateMatrix(p.x, p.y, p.z);
	Transform3D :: loadIdentityProjectionMatrix();
	Transform3D :: perspectiveProjectionMatrix(0.1,-5,2.5);
	Transform3D :: applyTransform(ob);

	poz_x = p.x;
	poz_y = p.y;
	poz_z = p.z;
	}

	void addObstacle3D_to_Visual2D(Visual2D *context) {

		DrawingWindow :: addObject3D_to_Visual2D(ob, context);
	}
	void applyTransformP(float x, float y, float z) {

		Transform3D :: loadIdentityProjectionMatrix();
		Transform3D :: perspectiveProjectionMatrix(x, y, z);
		Transform3D :: applyTransform(ob);

	}
	void move(float level) {
	
		scale +=0.008*level;
		poz_y-= level*0.03;
		poz_x += level*dist;

		Transform3D :: loadIdentityModelMatrix();
		if (type == 1) {
			Transform3D :: translateMatrix(-0.05,-0.3,-0.05);
			Transform3D :: scaleMatrix(scale,scale,scale);
			Transform3D :: translateMatrix(0.05, 0.3, 0.05);
		}
		else 
			if (type == 2){
				Transform3D :: scaleMatrix(scale,scale,scale);
				Transform3D :: rotateMatrixOy(angle);
				angle+=level*0.02;
			}
			else {
				Transform3D :: translateMatrix(-0.025,-0.025,-0.025);
				Transform3D :: scaleMatrix(scale,scale,scale);
				Transform3D :: translateMatrix(0.025, 0.025, 0.025);
			}

		Transform3D :: translateMatrix(poz_x, poz_y, poz_z);
		Transform3D :: loadIdentityProjectionMatrix();
		Transform3D :: perspectiveProjectionMatrix(0.1,-1,5);
		Transform3D :: applyTransform(ob);
		
	
	Transform3D :: applyTransform(ob);
	}

	~Obstacle() {}
};