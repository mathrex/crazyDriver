#pragma once
#include "Line2D.h"
#include "Point2D.h"
#include "Object2D.h"
#include "Polygon2D.h"
#include "Visual2D.h"
#include "DrawingWindow.h"

class Life {

	public : Polygon2D *h;
			 Line2D *x1, *x2;
	Life(Point2D p, Color c) {

		h = new Polygon2D(c, true);
		h->addPoint(p);

		h->addPoint(Point2D(p.x + 0.05,p.y+0.1));
		h->addPoint(Point2D(p.x + 0.07,p.y+0.15));
		h->addPoint(Point2D(p.x + 0.1,p.y+0.15));
		h->addPoint(Point2D(p.x + 0.13,p.y+0.15));
		h->addPoint(Point2D(p.x + 0.15,p.y+0.1));
		h->addPoint(Point2D(p.x + 0.15,p.y+0.05));
		h->addPoint(Point2D(p.x + 0.15,p.y));
		h->addPoint(Point2D(p.x + 0.13,p.y-0.05));
		h->addPoint(Point2D(p.x + 0.12,p.y-0.1));
		h->addPoint(Point2D(p.x + 0.11,p.y-0.15));
		h->addPoint(Point2D(p.x + 0.1,p.y-0.2));
		h->addPoint(Point2D(p.x + 0.09,p.y-0.25));
		h->addPoint(Point2D(p.x + 0.08,p.y-0.3));
		h->addPoint(Point2D(p.x + 0.06,p.y-0.35));
		h->addPoint(Point2D(p.x + 0.04,p.y-0.4));
		h->addPoint(Point2D(p.x + 0.02,p.y-0.45));
		h->addPoint(Point2D(p.x,p.y-0.5));
		h->addPoint(Point2D(p.x - 0.02,p.y-0.45));
		h->addPoint(Point2D(p.x - 0.04,p.y-0.4));
		h->addPoint(Point2D(p.x - 0.06,p.y-0.35));
		h->addPoint(Point2D(p.x - 0.08,p.y-0.3));
		h->addPoint(Point2D(p.x - 0.09,p.y-0.25));
		h->addPoint(Point2D(p.x - 0.1,p.y-0.2));
		h->addPoint(Point2D(p.x - 0.11,p.y-0.15));
		h->addPoint(Point2D(p.x - 0.12,p.y-0.1));
		h->addPoint(Point2D(p.x - 0.13,p.y+0.15));
		h->addPoint(Point2D(p.x - 0.1,p.y+0.15));
		h->addPoint(Point2D(p.x - 0.07,p.y+0.15));
		h->addPoint(Point2D(p.x - 0.05,p.y+0.1));
		
		//// un X///
		x1 = new Line2D(Point2D(p.x + 0.3,p.y), Point2D(p.x+0.4, p.y - 0.25), c);
		x2 = new Line2D(Point2D(p.x + 0.4,p.y), Point2D(p.x+0.3, p.y - 0.25), c);



		/* ramane un stalp
		h->addPoint(Point2D(p.x + 0.05,p.y+0.1));
		h->addPoint(Point2D(p.x + 0.1,p.y+0.15));
		h->addPoint(Point2D(p.x + 0.15,p.y+0.15));
		h->addPoint(Point2D(p.x + 0.2,p.y+0.15));
		h->addPoint(Point2D(p.x + 0.25,p.y+0.1));
		h->addPoint(Point2D(p.x + 0.2,p.y+0.1));
		h->addPoint(Point2D(p.x + 0.15,p.y+0.05));
		h->addPoint(Point2D(p.x + 0.1,p.y-0.05));
		h->addPoint(Point2D(p.x + 0.05,p.y-0.1));
		h->addPoint(Point2D(p.x,p.y-0.15));
		h->addPoint(Point2D(p.x,p.y-3));
		*/



		
	}

	void addLife_to_Visual2D(Visual2D *context) {

		DrawingWindow :: addObject2D_to_Visual2D(h, context);
		DrawingWindow :: addObject2D_to_Visual2D(x1, context);
		DrawingWindow :: addObject2D_to_Visual2D(x2, context);

	}
};