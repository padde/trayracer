// system header
#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <GL/glut.h>
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
#include <tracer.hpp>
#include <barebone.hpp>
#include <raycast.hpp>
#include <material.hpp>
#include <matte.hpp>
#include <light.hpp>
#include <ambientlight.hpp>
#include <pointlight.hpp>


class rt_application 
{
public :
	void raytrace() const
	{
		// get glwindow instance (for size)
		glutwindow& gw = glutwindow::instance();
		
		// create materials
		Material* red    = new Matte("red"   , 1.0, 0.5, rgb(1,0,0));
		Material* blue   = new Matte("blue"  , 0.5, 0.5, rgb(1,1,1));
		Material* yellow = new Matte("yellow", 0.5, 1.0, rgb(1,1,0));
		
		// create objects
		Shape* sphere   = new Sphere (
			"sphere",             /* name     */
			Point(250,250,-1000), /* center   */
			150,                  /* radius   */
			blue                  /* material */
		);
		
		Shape* triangle = new Triangle (
			"triangle",
			Point(300,450, -800), /* point a  */
			Point(  0,100,-1000), /* point b  */
			Point(450, 20,-1000), /* point c  */
			yellow                /* material */
		);
		
		Shape* box = new Box (
			"box",                /* name     */
			Point(100,100, -750), /* point a  */
			Point(350,350,-1050), /* point b  */
			red                   /* material */
		);
		
		// create transformations
		Matrix m = make_rotation( Vector (1,2,-1), 10 );
		Matrix r = make_rotation( Vector (225,225,-900), 10 );
		Matrix n = make_translation( 100,0,-90 );
		
		// transform objects
		box->transform(m);
		box->transform(n);
		
		// set background color
		rgb bgcolor(0.03,0.03,0.03);
		
		// store shapes in composite
		CompositeShape* shapes = new CompositeShape("shapes");
		
		shapes->push( sphere );
		//shapes->push( triangle );
		//shapes->push( box );
		
		// define ambient light, must be of type AmbientLight*
		AmbientLight* ambient = new AmbientLight (
			"ambient", /* name      */
			0.1,       /* intensity */
			rgb(1,1,1) /* color     */
		);
		
		// define point light
		Light* pointlight = new PointLight (
			"plt",            /* name      */
			1,              /* intensity */
			rgb(1,0,0),   /* color     */
			Point(0,500,-700) /* position  */
		);
		
		Light* pointlight2 = new PointLight (
			"plt2",            /* name      */
			1,              /* intensity */
			rgb(0,0,1),   /* color     */
			Point(500,500,-500) /* position  */
		);
		
		Light* pointlight3 = new PointLight (
			"plt2",            /* name      */
			1,              /* intensity */
			rgb(0,1,0),   /* color     */
			Point(250,200,-500) /* position  */
		);
		
		// make a camera and use it
		Camera* cam = new Camera (
			"cam1",      /* name       */
			gw.width(),  /* x-res      */
			gw.height(), /* y-res      */
			20.0         /* view angle */
		);
		
		// add elements to scene
		Scene* scene = new Scene();
		scene->push(shapes);
		scene->set(bgcolor);
		scene->set(ambient);
		scene->push(pointlight);
		scene->push(pointlight2);
		scene->push(pointlight3);
		scene->set(cam);
		
		// use barebone tracer
		// Tracer* tracer = new BareBone(scene);
		// scene->set(tracer);
		
		// preparations for filename
		time_t      t = time(NULL);
		struct tm* lt = localtime(&t);
		char time_str [80];
		strftime(time_str,80,"%Y-%m-%d__%H-%M-%S",lt);
		std::string filename = "images/raytrace__" + std::string(time_str) + ".png";
		
		// render the scene
		scene->render(filename);
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