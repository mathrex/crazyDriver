#pragma once
#include "Line2D.h"
#include "Point2D.h"
#include "Object2D.h"
#include "Polygon2D.h"
#include "Visual2D.h"
#include "DrawingWindow.h"
#include "Circle2D.h"

class Heart {
	Circle2D *circle1, *circle2;
	Polygon2D *v;

public:	Heart(Point2D p, Color c) {

		circle1 = new Circle2D(p, 0.08, c, true);
		circle2 = new Circle2D(Point2D(p.x + 0.15, p.y), 0.08, c, true);
		v = new Polygon2D(c, true);
		v->addPoint(Point2D(p.x - 0.08, p.y - 0.04));
		v->addPoint(Point2D(p.x + 0.08, p.y - 0.3));
		v->addPoint(Point2D(p.x + 0.22, p.y - 0.04));
		

	}

	void addHeart_to_Visual2D(Visual2D *context) {

		DrawingWindow :: addObject2D_to_Visual2D(circle1, context);
		DrawingWindow :: addObject2D_to_Visual2D(circle2, context);
		DrawingWindow :: addObject2D_to_Visual2D(v, context);

	}
};