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
#include <pixel.hpp>
#include <rgb.hpp>
#include <shape.hpp>
#include <sphere.hpp>
#include <triangle.hpp>
#include <box.hpp>
#include <matrix.hpp>
#include <compositeshape.hpp>
#include <scene.hpp>


class rt_application 
{
public :
	void raytrace() const
	{
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
		
		// add all elements to scene
		Scene scene;
		scene.push(shapes);
		scene.set(bgcolor);
		
		// make filename for png output
		time_t      t = time(NULL);
		struct tm* lt = localtime(&t);
		char time_str [80];
		strftime(time_str,80,"%Y-%m-%d__%H-%M-%S",lt);
		std::string filename = "images/raytrace__" + std::string(time_str) + ".png";
		
		// render the scene
		scene.render(filename);
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