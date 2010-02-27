// system header
#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <GL/glut.h>

// project header
#include <glutwindow.hpp>
#include <ppmwriter.hpp>
#include <pixel.hpp>
#include <rgb.hpp>
#include <shape.hpp>
#include <sphere.hpp>
#include <triangle.hpp>
#include <matrix.hpp>
#include <compositeshape.hpp>


class rt_application 
{
public :
	void raytrace() const 
	{
		// open a new GLUT window
		glutwindow& gw = glutwindow::instance();
		
		HitRecord rec;
		float tmax;
		const float fmax = std::numeric_limits<float>::max();
		Vector viewdir(0,0,-1);
		
		// scene elements
		Shape* sphere = new Sphere( 150 );
		Matrix translate( make_translation(250,250,-1000) );
		sphere->transform(translate);
		
		Shape* triangle = new Triangle( Point(300,600,-800), Point(0,100,-1000), Point(450,20,-1000) );
		Matrix rotate( make_rotation( Vector(0,0,1), 0.1 ) );
		// Matrix rotate( make_rotation_z(0.1) );
		triangle->transform(rotate);
		
		rgb bgcolor(0,0,0);
		
		// storing elements in composite
		CompositeShape shapes;
		shapes.push( sphere );
		shapes.push( triangle );
		
		while(true) {
		triangle->transform(rotate);
		// for all pixels of the window
		for (std::size_t y = 0; y < gw.height(); ++y) {
			for (std::size_t x = 0; x < gw.width(); ++x) {
				pixel p(x,y);
				
				/*
				// with antialiasing
				for (int i=1; i<=5; ++i)
				{
					for (int j=1; j<=5; ++j)
					{
						float newx = x+(i-2)*0.2;
						float newy = y+(j-2)*0.2;
						
						Ray ray( Point(newx,newy,0), viewdir ); // current ray
						tmax = fmax;                          // reset tmax
						
						int index = (i+3*j);
							
						if ( shapes.hit( ray, 0, tmax, rec) ) {
							p.color = (p.color * (index-1) + rec.color) / index;
							tmax = rec.t;
						} else {
							p.color = (p.color * (index-1) + bgcolor) / index;
						}
					}
				}
				*/
				
				Ray ray( Point(x,y,0), viewdir ); // current ray
				tmax = fmax;                      // reset tmax
				
				if ( shapes.hit( ray, 0, tmax, rec) ) {
					p.color = rec.color;
					tmax = rec.t;
				} else {
					p.color = bgcolor;
				}
				
				gw.write(p);
			}
		}}
	}
	
};





int main(int argc, char* argv[])
{
	// set window size
	const std::size_t width = 500;
	const std::size_t height = 500;
	
	// initialize glut window
	glutwindow::init(width, height, 100, 100, "Raytracer", argc, argv);
	
	// run raytracer in own thread so we can display pixels
	// before the whole picture is computed
	rt_application app;
	boost::thread thr(boost::bind(&rt_application::raytrace, &app));
	
	// run window in parent thread
	glutwindow::instance().run();
	
	// join threads and exit
	thr.join();
	return 0;
}