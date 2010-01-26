#include <glutwindow.hpp>
#include <ppmwriter.hpp>
#include <pixel.hpp>

#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <GL/glut.h>


#include <sphere.hpp>

class rt_application 
{
public :
	void raytrace() const 
	{
		glutwindow& gw = glutwindow::instance();
		
		Sphere sphere( Point(250,250,-1000), 150 );
		
		
		for (std::size_t y = 0; y < gw.height(); ++y)
		{
			for (std::size_t x = 0; x < gw.width(); ++x)
			{
				pixel p(x,y);
				///////////////////////////////////////////////////////////
				
				Ray ray( Point(x,y,0), Vector(0,0,-1) );
				
				if ( sphere.shadow_hit( ray, 0, 1000000) ) {
					p.color = rgb(0,0,1);
				}
				else {
					p.color = rgb(1,0,0);
				}
				
				
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
	const std::size_t width = 400;
	const std::size_t height = 400;
	
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