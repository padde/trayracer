// system header
#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <GL/glut.h>
#include <png++/image.hpp>
#include <png++/rgb_pixel.hpp>
#include <ctime>

// project header
#include <glutwindow.hpp>
#include <ppmwriter.hpp>
#include <pixel.hpp>
#include <rgb.hpp>
#include <shape.hpp>
#include <sphere.hpp>
#include <triangle.hpp>
#include <box.hpp>
#include <matrix.hpp>
#include <compositeshape.hpp>


class rt_application 
{
public :
	void raytrace() const 
	{
		// open a new GLUT window and a new PNG image
		glutwindow& gw = glutwindow::instance();
		std::size_t width  = gw.width();
		std::size_t height = gw.height();
		png::image< png::rgb_pixel > png(width,height);
		
		// initial variables
		HitRecord rec;
		const float fmax = std::numeric_limits<float>::max();
		float       tmax = fmax;
		float       tmin = 0.0;
		Vector viewdir(0,0,-1);
		
		
		///////////////////// scene elements ////////////////////////
		
		// objects
		Shape* sphere   = new Sphere   ( Point(250,250,-1000), 150);
		Shape* triangle = new Triangle ( Point(300,450, -800), Point(0  ,100,-1000), Point(450,20,-1000) );
		Shape* box      = new Box      ( Point(100,100,-750 ), Point(350,350,-1050) );
		
		Matrix m = make_rotation( Vector (1,2,-1), 10 );
		Matrix r = make_rotation( Vector (225,225,-900), 10 );
		Matrix n = make_translation( 100,0,-90 );
		box->transform(m);
		box->transform(n);
		
		
		// background color
		rgb bgcolor(0.1,0.1,0.1);
		
		// store elements in composite
		CompositeShape* shapes = new CompositeShape;
		shapes->push( sphere );
		shapes->push( triangle );
		shapes->push( box );
		
		////////////// actual raytracing happens here ///////////////
		
		for (std::size_t y = 0; y < height; ++y) {
			for (std::size_t x = 0; x < width; ++x) {
				pixel p(x,y);
				
				// without antialiasing
				Ray ray( Point(x,y,0), viewdir ); // current ray
				tmax = fmax;                      // reset tmax
				
				if ( shapes->hit(ray,tmin,tmax,rec) )
					p.color = rec.color;
				else
					p.color = bgcolor;
				
				/*
				// with antialiasing
				for (int i=1; i<=5; ++i) {
					for (int j=1; j<=5; ++j) {
						float newx = x+(i-2)*0.2;
						float newy = y+(j-2)*0.2;
						Ray ray( Point(newx,newy,0), viewdir );
						tmax = fmax;
						int index = (i+3*j);
						
						if ( shapes->hit(ray,tmin,tmax,rec) )
							p.color = (p.color*(index-1)+rec.color)/index;
						else
							p.color = (p.color*(index-1)+bgcolor)/index;
					}
				}
				*/
				
				// write pixel to window
				gw.write(p);
				
				// set pixel in png
				int r = p.color[rgb::r] * 255;
				int g = p.color[rgb::g] * 255;
				int b = p.color[rgb::b] * 255;
				std::size_t new_y = height - y - 1;
				png[new_y][x] = png::rgb_pixel(r,g,b);
			}	
		}
		
		// specify filename for png output
		time_t t = time (NULL);
		struct tm * lt = localtime ( &t );
		char time_str [80];
		strftime(time_str,80,"%Y-%m-%d__%H-%M-%S",lt);
		std::string filename = "images/raytrace__" + std::string(time_str) + ".png";
		
		// write pixels to png image
		png.write(filename);
		std::cout << "image saved as " << filename << std::endl;
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