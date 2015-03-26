#pragma once
#include "Object3D.h"
#include "Point3D.h"
#include <math.h>

class Circle3D:public Object3D
{
	
public:
	Circle3D(Point3D center, float radius)
	{
		color.r = color.b = color.g = 0;
		fill = false;
		vector <int> contour1, contour2;
		
		float dist_ = radius / 5, radius1;

		//construim lista de puncte tinand cont de centru si raza

		float u;
		float du = 10;
		float u_rad;
		int i = 0,j;
		i = 0;
		for(j = 0; j < 5; j++){
			
			radius1 = radius - j*radius/8;	
			for (u = 0; u <= 360; u+=du)
			{
				contour1.clear();
				contour2.clear();
				
				Point3D *p = new Point3D();
				u_rad = u * 3.14159 / 180;
				p->x = center.x + radius1 * cos(u_rad)*sin(u_rad);
				p->y = center.y + j*dist_ + radius1 * sin(u_rad)*sin(u_rad);
				p->z = center.z + radius1*cos(u_rad);
				vertices.push_back(p);
				transf_vertices.push_back(new Point3D(p->x,p->y,p->z));
				contour1.push_back(i);
				i++;
				p->x = center.x + radius1 * cos(u_rad)*sin(u_rad);
				p->y = center.y - j*dist_ + radius1 * sin(u_rad)*sin(u_rad);
				p->z = center.z + radius1*cos(u_rad);
				vertices.push_back(p);
				transf_vertices.push_back(new Point3D(p->x,p->y,p->z));
				contour2.push_back(i);
				i++;
		}
		faces.push_back(new Face(contour1));
		faces.push_back(new Face(contour2));
		}
	}

	Circle3D(Point3D center, float radius, Color _color, bool _fill)
	{
		fill = _fill;
		color.r = _color.r;
		color.g = _color.g;
		color.b = _color.b;
		
vector <int> contour1, contour2;
		
		float dist_ = radius / 8, radius1;

		//construim lista de puncte tinand cont de centru si raza

		float u;
		float du = 10;
		float u_rad;
		float teta, teta_rad;
		int i = 0,j;
		Point3D *p = new Point3D();
	//	for(j = 0; j < 7; j++){
			j = 0;
		//	radius1 = radius - j*radius/8;	
			contour1.clear();
			contour2.clear();
		for(teta = 0; teta <= 360; teta+=du) {
			teta_rad  = teta * 3.14159 / 180;
			for (u = 0; u <= 360; u+=du)
			{
				u_rad = u * 3.14159 / 180;
				p->x = center.x + radius * cos(teta_rad)*sin(u_rad);
				p->y = center.y +  radius*cos(u_rad); 
				p->z = center.z + radius * sin(teta_rad)*sin(u_rad);
				vertices.push_back(new Point3D(p->x,p->y,p->z));
				transf_vertices.push_back(new Point3D(p->x,p->y,p->z));
				contour1.push_back(i);
				i++;
			/*	p->y = center.y - j*dist_ + radius1 * sin(u_rad)*sin(u_rad);
				vertices.push_back(new Point3D(p->x,p->y,p->z));
				transf_vertices.push_back(new Point3D(p->x,p->y,p->z));
				contour2.push_back(i);
				i++;
*/		}
		faces.push_back(new Face(contour1));
		//faces.push_back(new Face(contour2));
		}
/*
		for(j = 0; j < 8; j++){
			//j = 0;
			radius1 = radius - j*radius/8;	
			contour1.clear();
			contour2.clear();
			for (u = 0; u <= 360; u+=du)
			{	
				u_rad = u * 3.14159 / 180;
				p->x = center.x + j*dist_ + radius1 * cos(u_rad)*sin(u_rad);
				p->y = center.y  + radius1 * sin(u_rad)*sin(u_rad);
				p->z = center.z + radius1*cos(u_rad);
				vertices.push_back(new Point3D(p->x,p->y,p->z));
				transf_vertices.push_back(new Point3D(p->x,p->y,p->z));
				contour1.push_back(i);
				i++;
				p->x = center.x - j*dist_ + radius1 * cos(u_rad)*sin(u_rad);
				vertices.push_back(new Point3D(p->x,p->y,p->z));
				transf_vertices.push_back(new Point3D(p->x,p->y,p->z));
				contour2.push_back(i);
				i++;
		}
		faces.push_back(new Face(contour1));
		faces.push_back(new Face(contour2));
		}
	*/
		/*
		for(j = 0; j < 8; j++){
			//j = 0;
			radius1 = radius - j*radius/8;	
			contour1.clear();
			contour2.clear();
			for (u = 0; u <= 360; u+=du)
			{	
				u_rad = u * 3.14159 / 180;
				p->x = center.x  + radius1 * cos(u_rad)*sin(u_rad);
				p->y = center.y  + radius1 * sin(u_rad)*sin(u_rad);
				p->z = center.z + j*dist_ + radius1*cos(u_rad);
				vertices.push_back(new Point3D(p->x,p->y,p->z));
				transf_vertices.push_back(new Point3D(p->x,p->y,p->z));
				contour1.push_back(i);
				i++;
				p->z = center.z - j*dist_ + radius1*cos(u_rad);
				vertices.push_back(new Point3D(p->x,p->y,p->z));
				transf_vertices.push_back(new Point3D(p->x,p->y,p->z));
				contour2.push_back(i);
				i++;
		}
		faces.push_back(new Face(contour1));
		faces.push_back(new Face(contour2));
		}
		*/
	}
	
	~Circle3D(){}
};