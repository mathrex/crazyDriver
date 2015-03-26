
#pragma once
#include "Object3D.h"
#include "Point3D.h"
#include <math.h>

class Sphere:public Object3D
{
	
public:
	Sphere(Point3D center, float radius)
	{
	}

	Sphere(Point3D center, float radius, Color _color, bool _fill)
	{
		fill = _fill;
		color.r = _color.r;
		color.g = _color.g;
		color.b = _color.b;
		
		vector <int> contour;

		float u;
		float du = 30;
		float u_rad;
		float teta, teta_rad;
		int i = 0;
		Point3D *p = new Point3D();
		
		for(teta = 0; teta <= 360; teta+=du) {
			contour.clear();
			teta_rad  = teta * 3.14159 / 180;
			for (u = 0; u <= 360; u+=du)
			{
				u_rad = u * 3.14159 / 180;
				p->x = center.x + radius * cos(teta_rad)*sin(u_rad);
				p->y = center.y +  radius*cos(u_rad); 
				p->z = center.z + radius * sin(teta_rad)*sin(u_rad);
				vertices.push_back(new Point3D(p->x,p->y,p->z));
				transf_vertices.push_back(new Point3D(p->x,p->y,p->z));
				contour.push_back(i);
				i++;
		}
		faces.push_back(new Face(contour));
		}
	}
	
	~Sphere(){}
};