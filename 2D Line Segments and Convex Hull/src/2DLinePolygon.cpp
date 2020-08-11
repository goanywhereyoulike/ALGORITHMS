#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctime>
#include <assert.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <memory>
#include <random>

#ifdef WIN32
#include <windows.h>
#endif

#ifndef MACOSX
#include <GL/gl.h>
#include <GL/glu.h>
#else
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

#include "wcode/fssimplewindow.h"
#include "wcode/fswin32keymap.h"
#include "bitmapfont\ysglfontdata.h"

#include "vectors.h"
#include "Matrices.h"

typedef enum
{
	eIdle = -2,
	eStop = -1,
	eStart = 0,
	eSpeedUp,
	eSpeedDown,
} changeType;

enum class eLineMode : char
{
	eSegment, // mode for testing line segment intersection
	eClosedPath, // mode for testing closed path algorithm for a collection of points.
	eConvexHull  // mode for testing convex hull generation for a collection of points
};

eLineMode eMode = eLineMode::eSegment;

using namespace std;
namespace {
	size_t num_segments{ 2 };
	float iSpeed{ 3.0 };
	constexpr float PI{ 3.1415926f };

	int numPoints = 10; // number of points used in polygon mode.
	const unsigned frameRate = 30; // 30 frame per second is the frame rate.
	const int timeSpan = 1000 / frameRate; // milliseconds
	const double timeInc = (double)timeSpan * 0.001; // time increment in seconds

	size_t WinWidth{ 800 }, WinHeight{ 600 };

	///////////////////// physics stuff ///////////////////
	struct Segment
	{
		Segment(float2D a, float2D b) :p1(a), p2(b) {}
		float2D p1, p2;
		float2D v1, v2;
		Vector3d<unsigned> color;
		bool intersect(Segment const & rhs) { return false; }
		
		void const draw(Vector3d<unsigned> const & col) const
		{
			glLineWidth(4);
			glColor3ub(col.x, col.y, col.z);
			glBegin(GL_LINE_STRIP);
				glVertex2f(p1.x, p1.y);
				glVertex2f(p2.x, p2.y);
			glEnd();
			//draw end points;
			glPointSize(7);
			glColor3ub(0, 0, 120);
			glBegin(GL_POINTS);
			  glVertex2d(p1.x, p1.y);
			  glVertex2d(p2.x, p2.y);
			glEnd();
		}
	};

	std::vector<Segment> Segs;

	std::vector<float2D> IntersectionPoints; // at every frame, clear this vector and fill it up with all 
											// intersection points you discover.

	void FindIntersectionPoints()
	{
		IntersectionPoints.clear();

		// compute all segment-pair intersection points
		//draw the points;
		glPointSize(7);
		glColor3ub(122, 0, 0);
		glBegin(GL_POINTS);
		for (auto const &pt : IntersectionPoints)
		{
			glVertex2d(pt.x, pt.y);
		}
		glEnd();

	}
	struct Polygon
	{
		std::vector<float2D> points;
		std::vector<Segment> sides;
		void constructPoly() {}
		void draw() const;
		//bool cmp(float2D a, float2D b);
		//double cross(float2D a, float2D b, float2D c);
		void generateClosedPath(); // clears sides vector, then set it so it constructs a simple closed path, as described in class.
		void generateConvexHull();  // clears sides vector, then set it so it constructs a convex Hull(shrink wrap) as described in class.
		void clear() { sides.clear(); }

	} poly;
	////////////////////////////////////////////////////////

	double cross(float2D a, float2D b, float2D c)
	{
		return ((b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x));
	}



	double distance(float2D a, float2D b)
	{
		return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
	
	}

	bool cmp1(float2D a, float2D b)
	{
		if (a.y == b.y)
			return a.x < b.x;
		else
			return a.y > b.y;
	}

	bool cmp(float2D a, float2D b)
	{
		int m = cross(poly.points[0], a, b);
		if (m < 0) 
			return 1;
		else if (m == 0 && (distance(poly.points[0], a) < distance(poly.points[0], b)))
			return 1;
		else 
			return 0;

	
	}


	void Polygon::generateClosedPath()
	{
		// dummy generation of path. JUst connection consecutive points together!
		//sides.clear();
		sort(points.begin(), points.end(), cmp1);
		sort(points.begin()+1, points.end(),cmp);
		//sides.push_back(Segment(points[0], points[1]));
		for (int i = 0; i < points.size(); ++i)
		{
			if (i < (points.size() - 1))
			{
				sides.push_back(Segment(points[i], points[i + 1]));
				

			}
			
			else
			   sides.push_back(Segment(points[i], points[0]));
		}
	}
	void Polygon::generateConvexHull()
	{
		std::vector<float2D> outpoints;
		
		int arrsize = 2;
		sort(points.begin(), points.end(), cmp1);
		sort(points.begin() + 1, points.end(), cmp);
		outpoints.push_back(points[0]);
		outpoints.push_back(points[1]);
		outpoints.push_back(points[2]);
		//sides.push_back(Segment(outpoints[0], outpoints[1]));

		for (int i = 3; i < points.size(); ++i)
		{
			while (arrsize > 0 && cross(outpoints[arrsize - 1], points[i], outpoints[arrsize] ) < 0)
			{
				outpoints.pop_back();
				arrsize--;

			}
			outpoints.push_back(points[i]);
			arrsize++;


		}

		for (int i = 0; i <= arrsize; ++i)
		{
			if (i < arrsize )
			{
				sides.push_back(Segment(outpoints[i], outpoints[i + 1]));


			}

			else
				sides.push_back(Segment(outpoints[i], outpoints[0]));
		}




	}
	void Polygon::draw() const
	{
		glPointSize(7);
		const Vector3d<unsigned> col{ 0, 0, 0 };
		for (auto const &side : sides)
		{
			side.draw(side.color);
		}

		// draw vertices:
		glLineWidth(5);
		glColor3ub(128, 0, 0);
		glBegin(GL_POINTS);
		for (auto const& pnt : points)
		{
			glVertex2d(pnt.x, pnt.y);
		}
		glEnd();
	}
	//////////////////////////////////////////////////////////////////////////////////////////////
	int Menu(void)
	{
		int r = eIdle, key;
		while (r != eStop && r != eStart)
		{
			FsPollDevice();
			key = FsInkey();
			switch (key)
			{
			case FSKEY_G:
				r = eStart;
				break;
			case FSKEY_ESC:
				r = eStop;
				break;
			case FSKEY_UP:
				if (eMode == eLineMode::eSegment)
					++iSpeed;
				else
					++numPoints;
				break;
			case FSKEY_DOWN:
				iSpeed = max(FLT_EPSILON, iSpeed - 1);
				break;
			case FSKEY_P:
				eMode = eLineMode::eClosedPath;
				break;
			case FSKEY_C:
				eMode = eLineMode::eConvexHull;
				break;
			case FSKEY_L:
				eMode = eLineMode::eSegment;
				break;
			case FSKEY_LEFT:
				num_segments = max(1, num_segments);
				break;
			case FSKEY_RIGHT:
				++num_segments;
				break;
			}

			int wid, hei;
			FsGetWindowSize(wid, hei);

			glViewport(0, 0, wid, hei);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(-0.5, (GLdouble)wid - 0.5, (GLdouble)hei - 0.5, -0.5, -1, 1);

			glClearColor(0.0, 0.0, 0.0, 0.0);
			glClear(GL_COLOR_BUFFER_BIT);
			char sBallCnt[128];
			sprintf(sBallCnt, "Segment count is %d. Use Right/Left keys to change it!\n", num_segments);
			char sSpeed[128];
			sprintf(sSpeed, "segment speed/number of points is %d. Use Up/Down keys to change it!\n", 
				eMode == eLineMode::eSegment ? (int)iSpeed : numPoints);
			char sLineMode[128];
			sprintf(sLineMode, " Mode = %s. Type L for linesegment mode, P for Points closed Path, C for convexHull!\n", 
				eMode == eLineMode::eSegment ? "Line Segment" : eMode == eLineMode::eClosedPath ? "Closed Path" : "Convex Hull");

			glColor3ub(255, 255, 255);

			glRasterPos2i(32, 32);
			glCallLists(strlen(sBallCnt), GL_UNSIGNED_BYTE, sBallCnt);
			glRasterPos2i(32, 64);
			glCallLists(strlen(sSpeed), GL_UNSIGNED_BYTE, sSpeed);
			glRasterPos2i(32, 96);
			glCallLists(strlen(sLineMode), GL_UNSIGNED_BYTE, sLineMode);

			const char *msg1 = "G.....Start Game\n";
			const char *msg2 = "ESC...Exit";
			glRasterPos2i(32, 160);
			glCallLists(strlen(msg1), GL_UNSIGNED_BYTE, msg1);
			glRasterPos2i(32, 192);
			glCallLists(strlen(msg2), GL_UNSIGNED_BYTE, msg2);

			FsSwapBuffers();
			FsSleep(10);
		}

		// create balls and polys
		if (r == eStart)
		{
			Segs.clear();
			Segs.reserve(num_segments);

			poly.clear();
		}
		return r;
	}

	////////////////////////////////////////////
	//detects if ball j collides with  ball i
	bool segsIntersect(int i, int j)
	{
//		if (i != j)
//			if (Balls[j]->distSq(*Balls[i]) <= (Balls[j]->radius + Balls[i]->radius) * (Balls[j]->radius + Balls[i]->radius))
			{
//				return true;
			}

		return false;
	}
	//////////////////////////////////////////////////////////////
	void SegsCollisionCheck()
	{
		glPointSize(7);
		glColor3ub(255, 0, 255);
		glBegin(GL_POINTS);
		for (int i = 0; i<Segs.size(); ++i)
		{
			for (int j = i + 1; j < Segs.size(); ++j)
			{
				if (Segs[i].intersect(Segs[j]))
				{
					//set color of both seg to red
					Segs[i].color = Segs[j].color = { 200, 0, 0 };
				}
				else
				{
					// set the color of both segments to be green
					Segs[i].color = Segs[j].color = { 0, 200, 0 };
				}
				
			}
		}
		glEnd();
	}
	/////////////////////////////////////////////////////////////////////
	void updatePhysics(double timeInc)
	{
		////////////First update balls position and rotation//////////////////
		for_each(Segs.begin(), Segs.end(), [timeInc](Segment& obj) {
			obj.p1 += obj.v1 * timeInc;
			obj.p2 -= obj.v2 * timeInc;
		});

		///// next check collisions ///////////////////////
		if(eMode == eLineMode::eSegment)
			SegsCollisionCheck();
	}

	//////////////////////////////////////////////////////
	void renderScene()
	{
		////// render balls ///////////////////
		for (auto const &seg : Segs)
		{
			seg.draw(seg.color);
		}

		////// render polygons ///////////////
		poly.draw();

		////  swap //////////
		FsSwapBuffers();
	}

	int randomRange(int low, int high)
	{
		std::random_device rd; // obtain a random number from hardware
		std::mt19937 eng(rd()); // seed the generator
		std::uniform_int_distribution<> distr(low, high); // define the range

		return distr(eng);
	}
	//////////////////////////////////////////////////////////////
	void initPhysics()
	{
		int width = 0, height = 0;
		FsGetWindowSize(width, height);
		int xdist = width / 5;
		int ydist = height / 5;
		if (eMode == eLineMode::eSegment)
		{
			// create line segments at random locations:
			int pointCount = 2 * num_segments;
			for (int i = 0; i < pointCount; i++)
			{
				float X1 = randomRange(10, width - 10);  
				float Y1 = randomRange(10, height - 10);  
				++i;
				float X2 = width - X1;
				float Y2 = height - Y1;
				if ((i / 2) % 2 == 1)
				{
					Y1 = (height - ydist - Y1) > 0.f ? height - ydist - Y1 : 50;
					Y2 = (height - ydist - Y2) > 0.f ? height - ydist - Y2 : 50;
				}
				Segs.push_back({ float2D(X1, Y1), float2D(X2, Y2) });
				float angle = atan((X1 - X2) / (Y2 - Y1));
				if ((i / 2) % 2 == 1)
				{
					angle = atan((Y2 - Y1) / (X2 - X1));
				}
				float speed = iSpeed *(1. + float(randomRange(0, pointCount)) / float(pointCount));
				float Vx1 = speed * cos(angle + 4);
				float Vy1 = speed * sin(angle + 4);
				float Vx2 = speed * cos(angle);
				float Vy2 = speed * sin(angle);
				int lastSegment = Segs.size() - 1;
				Segs[lastSegment].v1.set(Vx1, Vy1);
				Segs[lastSegment].v2.set(Vx2, Vy2);
				Segs[lastSegment].color = { (unsigned)randomRange(0,255),  (unsigned)randomRange(0,255),  (unsigned)randomRange(0,255) };
			}
		}
		else // polygon generator
		{
			int pointCount = numPoints;
			std::srand(std::time(0)); /* seed random number generator */
			for (int i = 0; i < pointCount; i++)
			{
				float X1 = randomRange(10, width-10);
				float Y1 = randomRange(10, height-10);
				poly.points.push_back(float2D(X1, Y1));
			}

			if (eMode == eLineMode::eClosedPath)
				poly.generateClosedPath();
			else
				poly.generateConvexHull();
		}
	}

	//////////////////////////////////////////////////////////////////////////////
	int Game(void)
	{
		DWORD passedTime = 0;
		FsPassedTime(true);

		int width = 0, height = 0;
		FsGetWindowSize(width, height);
		WinWidth = width;
		WinHeight = height;
		//////////// setting up the scene ////////////////////////////////////////	
		initPhysics();

		glViewport(0, 0, WinWidth, WinHeight);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-0.5, (GLdouble)WinWidth - 0.5, (GLdouble)WinHeight - 0.5, -0.5, -1, 1);

		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		////////////////////// main simulation loop //////////////////////////
		while (1)
		{
			glClear(GL_COLOR_BUFFER_BIT);
			int lb, mb, rb, mx, my;

			FsPollDevice();
			FsGetMouseState(lb, mb, rb, mx, my);
			int key = FsInkey();
			if (key == FSKEY_ESC)
				break;

			renderScene();

			////// update time lapse /////////////////
			passedTime = FsPassedTime();
			int timediff = timeSpan - passedTime;

			/////////// update physics /////////////////
			int maxPossible_dt = 2;
			int numOfIterations = timediff / maxPossible_dt + 1;	// Calculate Number Of Iterations To Be Made At This Update Depending On maxPossible_dt And dt
			double inc = (double)(timediff) / (double)numOfIterations * 0.001;
			for (int i = 0; i < numOfIterations; i++)
				updatePhysics(inc);

			//	printf("\inc=%f, numOfIterations=%d, timediff=%d", inc, numOfIterations, timediff);
			while (timediff >= timeSpan / 3)
			{
				FsSleep(1);
				passedTime = FsPassedTime();
				timediff = timeSpan - passedTime;
				//	printf("--passedTime=%d, timediff=%d", passedTime, timediff);
			}
			passedTime = FsPassedTime(true);
		}
		return 0;
	}

	////////////////////////////////////////////////////////////////
	void GameOver(int score)
	{
		int r = 0;

		FsPollDevice();
		while (FsInkey() != 0)
		{
			FsPollDevice();
		}

		while (FsInkey() == 0)
		{
			FsPollDevice();

			int wid, hei;
			FsGetWindowSize(wid, hei);

			glViewport(0, 0, wid, hei);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);

			glClearColor(0.0, 0.0, 0.0, 0.0);
			glClear(GL_COLOR_BUFFER_BIT);

			const char *msg1 = "Game Over";
			char msg2[256];
			glColor3ub(255, 255, 255);
			glRasterPos2i(32, 32);
			glCallLists(strlen(msg1), GL_UNSIGNED_BYTE, msg1);

			sprintf_s(msg2, "Your score is %d", score);

			glRasterPos2i(32, 48);
			glCallLists(strlen(msg2), GL_UNSIGNED_BYTE, msg2);

			FsSwapBuffers();
			FsSleep(10);
		}
	}

} // anonymous namespace


	/////////////////////////////////////////////////////////////////////////////////////////
	int main(void)
	{
		int menu;
		FsOpenWindow(32, 32, WinWidth, WinHeight, 1); // 800x600 pixels, useDoubleBuffer=1

		int listBase;
		listBase = glGenLists(256);
		YsGlUseFontBitmap8x12(listBase);
		glListBase(listBase);

		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);
		glDepthFunc(GL_ALWAYS);

		while (1)
		{
			menu = Menu();
			if (menu == eStart)
			{
				int score;
				score = Game();
				GameOver(score);
			}
			else if (menu == eStop)
			{
				break;
			}
		}

		return 0;
	}
