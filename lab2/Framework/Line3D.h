
#pragma once
#include "Object3D.h"
#include "Point3D.h"

class Line3D:public Object3D
{
public:
	Line3D(Point3D p1, Point3D p2)
	{   
		color.r = color.b = color.g = 0;
	

		//adaug punctele la lista de puncte
		vertices.push_back(new Point3D(p1.x,p1.y,p1.z));
		vertices.push_back(new Point3D(p2.x,p2.y,p2.z));

		transf_vertices.push_back(new Point3D(p1.x,p1.y,p1.z));
		transf_vertices.push_back(new Point3D(p2.x,p2.y,p2.z));
		vector <int> contour;
		contour.clear();
		contour.push_back(0);
		contour.push_back(1);
		faces.push_back(new Face(contour));
	}

	Line3D(Point3D p1, Point3D p2, Color _color)
	{
		
		color.r = _color.r;
		color.g = _color.g;
		color.b = _color.b;

		vertices.push_back(new Point3D(p1.x,p1.y,p1.z));
		vertices.push_back(new Point3D(p2.x,p2.y,p2.z));
		vertices.push_back(new Point3D(p2.x+0.02,p2.y,p2.z));
		vertices.push_back(new Point3D(p1.x+0.02,p1.y+0.02,p1.z));

		transf_vertices.push_back(new Point3D(p1.x,p1.y,p1.z));
		transf_vertices.push_back(new Point3D(p2.x,p2.y,p2.z));
		transf_vertices.push_back(new Point3D(p2.x+0.02,p2.y,p2.z));
		transf_vertices.push_back(new Point3D(p1.x+0.02,p1.y+0.02,p1.z));
	
		vector <int> contour;
		contour.clear();
		contour.push_back(0);
		contour.push_back(1);
		contour.push_back(2);
		contour.push_back(3);

		faces.push_back(new Face(contour));
	}


	~Line3D(){}

};