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
		
		HitRecord rec; // store hit data
		bool is_hit;   // have we had a hit?
		float tmax;    // max distance that is checked for hits, for hidden surface determination 
		Vector viewdir(0,0,-1); // the direction that we are looking to
		
		// some basic scene elements
		Sphere sphere( Point(250,250,-1000), 150 );
		Triangle triangle( Point(300,600,-800), Point(0,100,-1000), Point(450,20,-1000) );
		
		// for all pixels of the window
		for (std::size_t y = 0; y < gw.height(); ++y)
		{
			for (std::size_t x = 0; x < gw.width(); ++x)
			{
				pixel p(x,y);
				
				Ray ray( Point(x,y,0), viewdir ); // current ray
				tmax = 100000;  // reset tmax
				is_hit = false; // reset is_hit
				
				// color spheres in blue
				if ( sphere.hit( ray, 0, tmax, rec) ) {
					p.color = rgb(0.2,0.2,0.8);
					tmax = rec.t;
					is_hit = true;
				}
				
				// color triangles in yellow
				if ( triangle.hit( ray, 0, tmax, rec) ) {
					p.color = rgb(0.8,0.8,0.2);
					tmax = rec.t;
					is_hit = true;
				}
				
				// if no hit => background. color black
				if ( ! is_hit ) p.color = rgb(0,0,0);
				
				// write pixel to screen
				gw.write(p);
			}
		}
	}
	
};





int main(int argc, char* argv[])
{
	const std::size_t width = 500;
	const std::size_t height = 500;
	
	glutwindow::init(width, height, 100, 100, "Debug Shapes", argc, argv);
	
	rt_application app;
	boost::thread thr(boost::bind(&rt_application::raytrace, &app));
	glutwindow::instance().run();
	
	thr.join();
	
	return 0;
}