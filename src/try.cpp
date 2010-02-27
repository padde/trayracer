#include <glutwindow.hpp>
#include <ppmwriter.hpp>
#include <pixel.hpp>

#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <GL/glut.h>

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
		glutwindow& gw = glutwindow::instance();
		
		HitRecord rec;
		float tmax;
		const float fmax = std::numeric_limits<float>::max();
		Vector viewdir(0,0,-1);
		
		// some basic scene elements
		Matrix trans( make_translation(-250,-250,1000) );
		Matrix scale( make_scale(0.5,1.2,1.5) );
		
		Shape* sphere = new Sphere( 150 );
		sphere->transform(trans);
		sphere->transform(scale);
		
		Shape* triangle = new Triangle( Point(300,600,-800), Point(0,100,-1000), Point(450,20,-1000) );
		
		// storing elements in composite
		CompositeShape shapes;
		shapes.push( sphere );
		shapes.push( triangle );
		
		// background color;
		rgb bgcolor(0,0,0);
		
		
		// for all pixels of the window
		for (std::size_t y = 0; y < gw.height(); ++y)
		{
			for (std::size_t x = 0; x < gw.width(); ++x)
			{
				pixel p(x,y);
				
				Ray ray( Point(x,y,0), viewdir ); // current ray
				tmax = fmax;                      // reset tmax
				
				if ( shapes.hit( ray, 0, tmax, rec) )
				{
					p.color = rec.color;
					tmax = rec.t;
				}
				else p.color = bgcolor;
				
				gw.write(p);
			}
		}
	}
	
};





int main(int argc, char* argv[])
{
	const std::size_t width = 500;
	const std::size_t height = 500;
	
	glutwindow::init(width, height, 100, 100, "Raytracer", argc, argv);
	
	rt_application app;
	boost::thread thr(boost::bind(&rt_application::raytrace, &app));
	glutwindow::instance().run();
	
	thr.join();
	
	return 0;
}