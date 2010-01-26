#include <glutwindow.hpp>
#include <ppmwriter.hpp>
#include <pixel.hpp>

#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <GL/glut.h>

#include <shape.hpp>
#include <sphere.hpp>
#include <triangle.hpp>

class rt_application 
{
public :
	void raytrace() const 
	{
		glutwindow& gw = glutwindow::instance();
		
		HitRecord rec;
		bool is_hit;
		Vector viewdir(0,0,-1);
		
		Sphere sphere( Point(250,250,-1000), 150 );
		Triangle triangle( Point(300,600,-800), Point(0,100,-1000), Point(450,20,-1000) );
		
		
		for (std::size_t y = 0; y < gw.height(); ++y)
		{
			for (std::size_t x = 0; x < gw.width(); ++x)
			{
				pixel p(x,y);
				///////////////////////////////////////////////////////////
				
				Ray ray( Point(x,y,0), viewdir );
				is_hit = false;
				float tmax = 9999999999;
				
				if ( sphere.hit( ray, 0, tmax, rec) ) {
				//if ( sphere.shadow_hit( ray, 0.00001f, tmax) ) {
					p.color = rgb(0.2,0.2,0.8);
					tmax = rec.t;
					is_hit = true;
				}
				
				if ( triangle.hit( ray, 0, tmax, rec) ) {
				//if ( triangle.shadow_hit( ray, 0.00001f, tmax) ) {
					p.color = rgb(0.8,0.8,0.2);
					tmax = rec.t;
					is_hit = true;
				}
				
				if ( ! is_hit ) p.color = rgb(0,0,0);
				
				
				///////////////////////////////////////////////////////////
				gw.write(p);
			}
		}
	}
	
private : // attributes
	
	// you may add a scene description here

};





int main(int argc, char* argv[])
{
	// set resolution and checkersize
	const std::size_t width = 500;
	const std::size_t height = 500;
	
	// create output window
	glutwindow::init(width, height, 100, 100, "CheckerBoard", argc, argv);
	
	// create a ray tracing application
	rt_application app;
	
	// start computation in thread
	boost::thread thr(boost::bind(&rt_application::raytrace, &app));
	
	// start output on glutwindow
	glutwindow::instance().run();
	
	// wait on thread
	thr.join();
	
	return 0;
	
}