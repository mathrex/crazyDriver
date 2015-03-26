#pragma once
#include "Object3D.h"
#include "Point3D.h"
#include "Line3D.h"
#include "Visual2D.h"
#include "DrawingWindow.h"
#include "Transform3D.h"

class Disc_Line3D
{

	Line3D *lines[15];
	float dist_y, trans_y, trans_z; //daca este discontinua, lungimea fiecarei bucati continue
							// trans_y cu cat este translatata banda
public:
	
	Disc_Line3D(Point3D p1, Point3D p2, Color _color)
	{
		int i;
		dist_y = (p2.y - p1.y) / 14;
		for(i = 0; i <= 14; i+=2)
			lines[i/2] = new Line3D(Point3D(p1.x,p2.y - i*dist_y, p2.z + p1.z/14*i), Point3D(p2.x, p2.y - (i + 1)*dist_y, p2.z + p1.z/14*(i+1)), _color);
		trans_z = 0;
		trans_y = 0;
	}
	void perspective_Disc_Line3D (float x, float y, float z ) {

		int i;

		Transform3D :: loadIdentityModelMatrix();
		Transform3D :: loadIdentityProjectionMatrix();
		Transform3D :: perspectiveProjectionMatrix(x,y,z);

		for (i = 0; i < 8; i++) {
			Transform3D :: applyTransform(lines[i]);
		}
	}

	void addDisc_Line3D_to_Visual2D(Visual2D *context) {
		int i;
		for (i = 0; i <= 7; i++)
			DrawingWindow :: addObject3D_to_Visual2D(lines[i],context);
	}
	void move(float level, float x, float y, float z) {

		
		int i;
		trans_y -= 0.002*level;
		trans_z += 0.0004*level;

		if (trans_y + dist_y < 0) {
			trans_y = 0;
			trans_z = 0;
		}

		Transform3D :: loadIdentityModelMatrix();
		Transform3D :: translateMatrix(0,trans_y,trans_z);
		Transform3D :: loadIdentityProjectionMatrix();
		Transform3D :: perspectiveProjectionMatrix(x,y,z);

		for (i = 0; i < 8; i++) {
			Transform3D :: applyTransform(lines[i]);
		}
	}
	~Disc_Line3D(){}

};