

#include "Framework/DrawingWindow.h"
#include "Framework/Visual2D.h"
#include "Framework/Transform2D.h"
#include "Framework/Transform3D.h"
#include "Framework/Line2D.h"
#include "Framework/Rectangle2D.h"
#include "Framework/Circle2D.h"
#include "Framework/Polygon2D.h"
#include "Framework/Line3D.h"
#include "Framework/MyDriver.h"
#include "Framework/Obstacle.h"
#include "Framework/Heart.h"
#include "Framework/Collision.h"
#include "Framework/Disc_Line3D.h"
#include "Framework/Sphere.h"
#include "Framework/Enemy.h"
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <windows.h>


#define PI 3.14159265358979323846
#define inf 1000000
using namespace std;

Visual2D *v2d1, *cont2;
MyDriver *Mike;
Obstacle *obstacles[25];
int nr_obst = 0, life = 5, level = 1, total_obst = 0;
float x_coord[15] = {-0.8, -0.7, -0.5, -0.1, 0, 0.1, 0.4, 0.5, 0.7, 0.75}; //directii pt obstacole
Color colors[10] = {Color(0,0.8,0.4), Color(0,1,0.4), Color(1,0.8,0.4), Color(1,1,0.4), 
					Color(0.5,0.8,0.4), Color(0,1,0), Color(0,0,0.9), Color(1,0,0.4), Color(1,1,0), Color(0.1,0.3,0.4)};
clock_t  aux_time, time_prec_obstacle, timer_move_left, timer_move_right;
clock_t initial_time, collision_time = 0, timer_sphere, timer_obst_mobil;
int ok_r = 0, ok_l = 0, is_removed = 0, destination = 100;
int slow = 0, fast = 0, score = 0, sclip = -1;
Text *elapsed_time, *text_life, *text_score, *text_destination;
Heart *me;
Disc_Line3D *banda1, *banda2;
int bonus = 0;	//la 5 obiecte bonus luate se va da o viata
Enemy *obst_mobil;

int max (int a, int b) {

	return a > b ? a : b;
}
int min (int a, int b) {

	return a > b ? b : a;
}
//functia care permite adaugarea de obiecte
void DrawingWindow::init()
{
	int i, x;
	char string_life[5];
	time_prec_obstacle = clock();
	initial_time = clock();
	timer_sphere = initial_time;
	
	v2d1 = new Visual2D(-3,-6,3,6,0,0,DrawingWindow::width,DrawingWindow::height); 
	v2d1->tipTran(true);
	addVisual2D(v2d1);

	elapsed_time = new Text("0", Point2D(2,5), Color(0.8,0.5,1), BITMAP_HELVETICA_18);
	addText_to_Visual2D(elapsed_time, v2d1);
	
	i = rand()%10;
	obst_mobil = new Enemy(Point3D(x_coord[i], 3.5, -0.2), Color(0.8, 0.5, 0.6));
	obst_mobil->addObst_to_Visual2D(v2d1);
	timer_obst_mobil = clock();
 
	itoa(life, string_life+2, 10);
	string_life[0] = 'x';
	string_life[1] = ' ';
	
	text_life = new Text (string_life, Point2D(2.3, 4.4), Color(1,0.3,0.5), BITMAP_HELVETICA_18);
	addText_to_Visual2D(text_life, v2d1);
	
	text_score = new Text("Score: 0", Point2D(2.3, 4), Color(1,1,1), BITMAP_HELVETICA_18);
	addText_to_Visual2D(text_score, v2d1);
	
	text_destination = new Text("Destination: 100", Point2D(2,5.5), Color(1, 0.1, 1), BITMAP_HELVETICA_18);
	addText_to_Visual2D(text_destination, v2d1);

	me = new Heart(Point2D(2, 4.6), Color(1,0.3,0.5));
	me->addHeart_to_Visual2D(v2d1);

	//se adauga marginile si benzile soselei

	Line3D *margine1, *margine2;
	
	margine1 = new Line3D(Point3D(-0.8, -5, 1.75), Point3D(-0.8, 4.5, 0), Color(0,0.5,0.5));
	margine2 = new Line3D(Point3D(0.8, -5, 1.75), Point3D(0.8, 4.5, 0), Color(0,0.5,0.5));
	banda1 = new Disc_Line3D(Point3D(-0.25,-5, 1.75), Point3D(-0.25, 4.5, 0), Color(0,0.5,0.5));
	banda2 = new Disc_Line3D(Point3D(0.25,-5, 1.75), Point3D(0.25, 4.5, 0), Color(0,0.5,0.5));

	Transform3D :: loadIdentityProjectionMatrix();
	Transform3D :: loadIdentityModelMatrix();
	Transform3D :: perspectiveProjectionMatrix(0.1, -5, 2.5);
	Transform3D :: applyTransform(margine1);
	Transform3D :: applyTransform(margine2);
	banda1->perspective_Disc_Line3D(0.1, -5, 2.5);
	banda2->perspective_Disc_Line3D(0.1, -5, 2.5);


	addObject3D_to_Visual2D(margine1, v2d1);
	addObject3D_to_Visual2D(margine2, v2d1);
	banda1->addDisc_Line3D_to_Visual2D(v2d1);
	banda2->addDisc_Line3D_to_Visual2D(v2d1);

	
	Mike = new MyDriver();
	Mike->addCar_to_Visual2D(v2d1);
	
}


//functia care permite animatia
void DrawingWindow::onIdle()
{ 
	
	int i, x;
	int type_obst;
	char timer[20], string[25];
	if (life > 0 && destination >= 0) {
		if (ok_l) { // masinuta revine din rotatie dupa ce a fost deplasata la stanga
		
		aux_time = clock();
			if( ((float)aux_time - (float)timer_move_left)/1000.0F >= max(0.5 - level *0.1, 0.1)) {
				ok_l = 0;
				Transform3D :: loadIdentityModelMatrix();
				Transform3D :: translateMatrix(Mike->x_trans_left,-4,0);
				Transform3D :: loadIdentityProjectionMatrix();
				Transform3D :: perspectiveProjectionMatrix(0.1 + Mike->x_trans_left,-1,2.5);
				Transform3D :: applyTransform(Mike->car);
				Transform3D :: applyTransform(Mike->contour_car);
				
				for(i = 0; i < 4; i++) {

					Transform3D :: loadIdentityModelMatrix();
					Transform3D :: translateMatrix(Mike->points_wheels[i]->x + Mike->x_trans_left,-4 + Mike->points_wheels[i]->y, Mike->points_wheels[i]->z);
					Transform3D :: applyTransform(Mike->wheels[i]);
				}
	
			}
	}
	else 
		if(ok_r) {
			// masinuta revine din rotatie dupa ce a fost deplasata la dreapta
			aux_time = clock();
			if (((float)aux_time - (float)timer_move_right)/1000.0F >= max(0.5 - level *0.1, 0.1)) {
				ok_r = 0;
				Transform3D :: loadIdentityModelMatrix();
				Transform3D :: translateMatrix(Mike->x_trans_right,-4,0);
				Transform3D :: loadIdentityProjectionMatrix();
				Transform3D :: perspectiveProjectionMatrix(0.1 + Mike->x_trans_right,-1, 2.5);
				Transform3D :: applyTransform(Mike->car);
				Transform3D :: applyTransform(Mike->contour_car);

				for(i = 0; i < 4; i++) {
					Transform3D :: loadIdentityModelMatrix();
					Transform3D :: translateMatrix(Mike->points_wheels[i]->x + Mike->x_trans_right,-4 + Mike->points_wheels[i]->y, Mike->points_wheels[i]->z);
					Transform3D :: applyTransform(Mike->wheels[i]);

				}
			}
		}


		//miscare obstacol mobil
		
		if ( ((float)aux_time - (float)timer_obst_mobil) / 1000.0F < (1 - level*0.1) || ((float)aux_time - (float)timer_obst_mobil) / 1000.0F > (3 - level*0.1) ) {
			obst_mobil->move_car(0,level);
			if (obst_mobil->current_pos_y < -7) {
				i = rand()%10;
				if (i == 5 || i==6)
					i++;
				obst_mobil = new Enemy(Point3D(x_coord[i], 3.5, 0.4), Color(0.8, 0.5, 0.6));
				obst_mobil->addObst_to_Visual2D(v2d1);
				timer_obst_mobil = clock();
			}
		}
		else
			if ( ((float)aux_time - (float)timer_obst_mobil) / 1000.0F < (3 - level*0.1))
				obst_mobil->move_car(1, level);
			
			
	//se actualizeaza timpul scurs de la inceperea jocului si se afiseaza
	aux_time = clock();
	sprintf(timer, "%f", -((float)initial_time - (float)aux_time) / 1000.0F);
	removeText_from_Visual2D(elapsed_time, v2d1);
	elapsed_time = new Text(timer, Point2D(2,5), Color(0.6,0.6,0.6), BITMAP_HELVETICA_18);
	addText_to_Visual2D(elapsed_time, v2d1);
	//se actualizeaza distanta ramasa pana la destinatie
	destination = 100 - aux_time / 1000;
	removeText_from_Visual2D(text_destination, v2d1);
	strcpy(string, "Destination:  ");
	itoa(destination, string+13, 10);
	text_destination = new Text(string, Point2D(2,5.5), Color(0, 0.5, 1), BITMAP_HELVETICA_18);
	addText_to_Visual2D(text_destination, v2d1);


	//din 10 in 10 secunde se trece la nivelul urmator, osbtacolele vor avea viteza mai mare
	if (((float)aux_time - (float)initial_time) / 1000.0F > 10*level) {
		score += level * 20;
		removeText_from_Visual2D(text_score, v2d1);
		strcpy(string, "Score: ");
		itoa(score, string + 7, 10);
		text_score = new Text(string, Point2D(2.3, 4), Color(1,1,1), BITMAP_HELVETICA_18);
		addText_to_Visual2D(text_score, v2d1);
		level ++;
	}
	//dupa un interval de timp, in functie de level, apar obiecte
	// sfere, piramide sau obiecte bonus ce vor creste numarul de vieti
	// sferele vor aparea mai rar
	if( ((float)aux_time - (float)time_prec_obstacle) / 1000.0F >= max (1.1 - (level*0.2), 0.3)) {
		time_prec_obstacle = aux_time;
		if (nr_obst == 20)
			nr_obst = 0;
		i = rand()%10;
		if (((float)aux_time - (float)timer_sphere) / 1000.0F >= 5) {
			timer_sphere = clock();
			type_obst = 2;
		}
		else {
			if (i == 1 || i == 5 || i == 7)
			type_obst = 0; //type_obst = 1 piramida, 0 - obstacol bonus
			else
				type_obst = 1;
		}
		if (type_obst == 0) {
			x = rand()%10;
			obstacles[nr_obst] = new Obstacle(Point3D(x_coord[i],3.5,0.4),colors[x], type_obst);
		}
		else
			obstacles[nr_obst] = new Obstacle(Point3D(x_coord[i],3.5,0.4),Color(1,0,0), type_obst);
		obstacles[nr_obst]->addObstacle3D_to_Visual2D(v2d1);
		nr_obst++;
		if (total_obst < 20)
			total_obst ++;
	}
	// daca jucatorul a pierdut o viata, masina va dispare si apare inapoi
	if(sclip != -1)	
	if( ((float)aux_time - (float)collision_time) / 1000.0F < 0.6 && ((float)aux_time - (float)collision_time) / 1000.0F > 0.1*(float)sclip)
		if (is_removed) {

			is_removed = 0;
			sclip ++;
			Mike->addCar_to_Visual2D(v2d1);
		}
		else {
			is_removed = 1;
			sclip++;
			Mike->remove_car(v2d1);
		}
	else
		if (((float)aux_time - (float)collision_time) / 1000.0F > 0.8 && is_removed) {
			Mike->addCar_to_Visual2D(v2d1);
			is_removed = 0;
		}
	
	//slow > 0 daca s-a apasat tasta de franare
	// fast > 0 daca s-a apasat tasta de accelerare
	for(i = 0; i < total_obst; i++) {
		if (slow > 0) {
		obstacles[i]->move(level/2);
		banda1->move(level/2, 0.1, -5, 2.5);
		banda2->move(level/2, 0.1, -5, 2.5);
		time_prec_obstacle += 0.2;
		}
		else 
			if(fast > 0) {
				obstacles[i]->move(level*2);
				banda1->move(level*2, 0.1, -5, 2.5);
				banda2->move(level*2, 0.1, -5, 2.5);
				time_prec_obstacle -= 0.2;
				
			}
			else {
				obstacles[i]->move(level);
				banda1->move(level, 0.1, -5, 2.5);
				banda2->move(level, 0.1, -5, 2.5);
			}
	}
	slow --;
	fast --;

	//verificare coliziune masina-obstacol
	
	if (((float)aux_time - (float)collision_time) / 1000.0F > max (1.5 - level * 0.2, 0.6)) {
	for (i = 0; i < max(total_obst, nr_obst); i++) 
		if (!obstacles[i]->is_removed && isAttacking(Mike->car, obstacles[i]->ob)) {
			if (obstacles[i]->type == 0) {	//daca era un obstacol bonus, primesc puncte
				score += level * 10;
				bonus ++;
				removeText_from_Visual2D(text_score, v2d1);
				strcpy(string, "Score: ");
				itoa(score, string + 7, 10);
				text_score = new Text(string, Point2D(2.3, 4), Color(1,1,1), BITMAP_HELVETICA_18);
				addText_to_Visual2D(text_score, v2d1);
				obstacles[i]->is_removed = true;
				removeObject3D_from_Visual2D(obstacles[i]->ob, v2d1);
				if(bonus == 5) { //daca am adunat 5 obctacole bonus, primesc o viata
					bonus = 0;
					life ++;
					itoa(life, string+2, 10);
					string[0] = 'x';
					string[1] = ' ';
					removeText_from_Visual2D(text_life, v2d1);
					text_life = new Text (string, Point2D(2.3, 4.4), Color(1,0.3,0.5), BITMAP_HELVETICA_18);
					addText_to_Visual2D(text_life, v2d1);
				}

			}
			else
			{
			collision_time = clock();
			life --;
			itoa(life, string+2, 10);
			string[0] = 'x';
			string[1] = ' ';
			removeText_from_Visual2D(text_life, v2d1);
			text_life = new Text (string, Point2D(2.3, 4.4), Color(1,0.3,0.5), BITMAP_HELVETICA_18);
			addText_to_Visual2D(text_life, v2d1);
		
			sclip = 1;
		}
		}
		if (isAttacking(Mike->car, obst_mobil->car)) {
			collision_time = clock();
			life --;
			itoa(life, string+2, 10);
			string[0] = 'x';
			string[1] = ' ';
			removeText_from_Visual2D(text_life, v2d1);
			text_life = new Text (string, Point2D(2.3, 4.4), Color(1,0.3,0.5), BITMAP_HELVETICA_18);
			addText_to_Visual2D(text_life, v2d1);
		
			sclip = 1;
		}
		}
	}
	else
		if (destination < 0) {
			Text *over = new Text("~~~~~~You won the game!!!~~~~~~", Point2D(-1,0), Color (0,0.5,0.5), BITMAP_TIMES_ROMAN_24);
			addText_to_Visual2D(over, v2d1);
		}
		else {
			Text *over = new Text("Game over!!!", Point2D(0,0), Color (0,0.5,0.5), BITMAP_TIMES_ROMAN_24);
			addText_to_Visual2D(over, v2d1);
		}
		
}

//functia care se apeleaza la redimensionarea ferestrei
void DrawingWindow::onReshape(int width,int height)
{
	
	//v2d1->poarta(0,0,width,height); 
	

}

//functia care defineste ce se intampla cand se apasa pe tastatura
void DrawingWindow::onKey(unsigned char key)
{ int i;
	switch(key)
	{
	    case GLUT_KEY_LEFT:
			timer_move_left = clock();
			Mike->move_car(-1);
			ok_l = 1;
			ok_r = 0;
			Transform3D :: loadIdentityModelMatrix();
			Transform3D :: translateMatrix(0.15, 0.15, 0.2);
			Transform3D :: rotateMatrixOy(-PI/6);
			Transform3D :: translateMatrix(-0.15, -0.15, -0.2);
			Transform3D :: translateMatrix(Mike->x_trans_left,-4,0);
			Transform3D :: loadIdentityProjectionMatrix();
			Transform3D :: perspectiveProjectionMatrix(0.1 ,-1,2.5);
			Transform3D :: applyTransform(Mike->car);
			Transform3D :: applyTransform(Mike->contour_car);

			for(i = 0; i < 4; i++) {
				Transform3D :: loadIdentityModelMatrix();
				Transform3D :: translateMatrix(0.075, 0.075, 0.075);
				Transform3D :: rotateMatrixOy(-PI/6);
				Transform3D :: translateMatrix(-0.075, -0.075, -0.075);
				Transform3D :: translateMatrix(Mike->points_wheels[i]->x + Mike->x_trans_left,-4 + Mike->points_wheels[i]->y, Mike->points_wheels[i]->z);
				Transform3D :: applyTransform(Mike->wheels[i]);

			}
			break;

		case GLUT_KEY_RIGHT: 
			timer_move_right = clock();
			Mike->move_car(1);
			ok_r = 1;
			ok_l = 0;
			Transform3D :: loadIdentityModelMatrix();
			Transform3D :: translateMatrix(0.15, 0.15, 0.2);
			Transform3D :: rotateMatrixOy(PI/6);
			Transform3D :: translateMatrix(-0.15, -0.15, -0.2);
			Transform3D :: translateMatrix(Mike->x_trans_right,-4,0);
			Transform3D :: loadIdentityProjectionMatrix();
			Transform3D :: perspectiveProjectionMatrix(0.1 ,-1,2.5);
			Transform3D :: applyTransform(Mike->car);
			Transform3D :: applyTransform(Mike->contour_car);

			for(i = 0; i < 4; i++) {
				Transform3D :: loadIdentityModelMatrix();
				Transform3D :: translateMatrix(0.075, 0.075, 0.075);
				Transform3D :: rotateMatrixOy(PI/6);
				Transform3D :: translateMatrix(-0.075, -0.075, -0.075);
				Transform3D :: translateMatrix(Mike->points_wheels[i]->x + Mike->x_trans_right,-4 + Mike->points_wheels[i]->y, Mike->points_wheels[i]->z);
				Transform3D :: applyTransform(Mike->wheels[i]);

			}
			break;

		case GLUT_KEY_UP:	//la acceleratie va creste viteza de doua ori
			fast = 4;
			slow = 0;
			break;
		case GLUT_KEY_DOWN:
			slow = 4;
			fast = 0;
			break;
	}
}

//functia care defineste ce se intampla cand se da click pe mouse
void DrawingWindow::onMouse(int button,int state,int x, int y)
{
	
}


int main(int argc, char** argv)
{
	//creare fereastra
	DrawingWindow dw(argc, argv, 1050, 750, 0, 0, "Crazy Driver");
	//se apeleaza functia init() - in care s-au adaugat obiecte
	dw.init();
	//se intra in bucla principala de desenare - care face posibila desenarea, animatia si procesarea evenimentelor
	dw.run();
	return 0;

}