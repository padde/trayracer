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
#include <phong.hpp>
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
		Material* red    = new Phong("bling", 0.8, 1.0, 1.0, 2, rgb(0.9, 0.2, 0.1));
		Material* yellow = new Phong("bling", 0.8, 1.0, 1.0, 2, rgb(1.0, 0.9, 0.3));
		Material* green  = new Phong("bling", 0.8, 1.0, 1.0, 2, rgb(0.1, 0.7, 0.3));
		Material* blue   = new Phong("bling", 0.8, 1.0, 1.0, 2, rgb(0.1, 0.2, 1.0));
		Material* white  = new Phong("bling", 0.8, 1.0, 1.0, 2, rgb(0.9, 0.9, 0.7));
		
		// create objects
		Shape* s1 = new Sphere ("s1", Point(   0,   0,-1500), 350, white );
		Shape* s2 = new Sphere ("s2", Point( 200, 200,-1600), 320, yellow);
		Shape* s3 = new Sphere ("s3", Point(-300,-100,-1400), 280, red   );
		Shape* s4 = new Sphere ("s4", Point(   0,-200,-1500), 300, blue  );
		Shape* s5 = new Sphere ("s5", Point( 400,-150,-1500), 250, green );
		Shape* s6 = new Sphere ("s6", Point(   0, -80,-1250), 150, yellow);
		Shape* s7 = new Sphere ("s7", Point(  80, 300,-1600), 300, red   );
		
		// set background color
		rgb bgcolor(0.01,0.01,0.01);
		
		// store shapes in composite
		CompositeShape* shapes = new CompositeShape("shapes");
		shapes->push(s1);
		// shapes->push(s2);
		// shapes->push(s3);
		// shapes->push(s4);
		// shapes->push(s5);
		// shapes->push(s6);
		// shapes->push(s7);
		
		// define ambient light, must be of type AmbientLight*
		AmbientLight* amb = new AmbientLight ("amb", 0.2, rgb(1,1,1));
		
		// define point light
		Light* p1 = new PointLight ("p1", 0.6, rgb(1.0,1.0,1.0), Point(-500, 500,-1000));
		Light* p2 = new PointLight ("p2", 1.0, rgb(1.0,0.3,0.3), Point( 500,-500,-1200));
		Light* p3 = new PointLight ("p3", 1.0, rgb(0.1,0.5,0.9), Point( 500, 500,-1000));
		
		// make a camera
		Camera* cam = new Camera ("cam", gw.width(), gw.height(), 80);
		
		// add elements to scene
		Scene* scene = new Scene();
		scene->push(shapes);
		scene->set(bgcolor);
		scene->set(amb);
		scene->push(p1);
		scene->push(p2);
		scene->push(p3);
		scene->set(cam);
		
		// preparations for filename
		time_t      t = time(NULL);
		struct tm* lt = localtime(&t);
		char time_str [80];
		strftime(time_str,80,"%Y-%m-%d__%H-%M-%S",lt);
		std::string filename = "images/raytrace__" + std::string(time_str) + ".png";
		
		// render the scene
		cam->render(filename);
	}
	
	
	void cornell_box() const
	{
		// get glwindow instance (for size)
		glutwindow& gw = glutwindow::instance();
		
		// create materials
		Material* red    = new Matte("", 1.0, 1.0, rgb(0.9, 0.2, 0.1));
		Material* green  = new Matte("", 1.0, 1.0, rgb(0.1, 0.7, 0.3));
		Material* white  = new Matte("", 1.0, 1.0, rgb(1.0, 1.0, 1.0));
		
		Material* ivory  = new Phong("", 1.0, 1.0, 1.0, 3, rgb(1.0, 1.0, 0.98));
		
		// walls
		Shape* wall_right   = new Box("", Point( 500,-550,    0), Point( 550, 550, -1000), green);
		Shape* wall_left    = new Box("", Point(-500,-550,    0), Point(-550, 550, -1000), red  );
		Shape* wall_top     = new Box("", Point(-500, 500,    0), Point( 500, 550, -1000), white);
		Shape* wall_bottom  = new Box("", Point(-500,-500,    0), Point( 500,-550, -1000), white);
		Shape* wall_back    = new Box("", Point(-550,-550,-1000), Point( 550, 550, -1050), white);
		Shape* sphere_left  = new Sphere("", Point(-300,-320,-600), 180, ivory);
		Shape* sphere_right = new Sphere("", Point( 250,-300,-300), 200, ivory);
		
		Shape* triangle = new Triangle ( "", Point(-300,-300,-300), Point(0,300,-1200), Point(300,-200,-130) ,green);
		
		
		// set background color
		rgb bgcolor(0.03,0.03,0.03);
		
		// store shapes in composite
		CompositeShape* shapes = new CompositeShape("shapes");
		shapes->push(wall_left);
		shapes->push(wall_right);
		shapes->push(wall_top);
		shapes->push(wall_bottom);
		shapes->push(wall_back);
		shapes->push(sphere_left);
		shapes->push(sphere_right);
		//shapes->push(triangle);
		
		// define ambient light, must be of type AmbientLight*
		AmbientLight* amb = new AmbientLight ("amb", 0.2, rgb(1,1,0.9));
		
		// define point light
		Light* p1 = new PointLight ("", 1.0, rgb(1.0,1.0,0.9), Point(   0, 300,-500));
		
		// make a camera
		Camera* cam = new Camera ("cam", gw.width(), gw.height(), 31);
		
		// add elements to scene
		Scene* scene = new Scene();
		scene->push(shapes);
		scene->set(bgcolor);
		scene->set(amb);
		scene->push(p1);
		scene->set(cam);
		
		// preparations for filename
		time_t      t = time(NULL);
		struct tm* lt = localtime(&t);
		char time_str [80];
		strftime(time_str,80,"%Y-%m-%d__%H-%M-%S",lt);
		std::string filename = "images/raytrace__" + std::string(time_str) + ".png";
		
		// render the scene
		cam->render(filename);
	}
	
	
	void color_shadows() const
	{
		// get glwindow instance (for size)
		glutwindow& gw = glutwindow::instance();
		
		// create materials
		Material* white  = new Matte ("", 1, 1, rgb(1,1,1));
		
		// walls
		Shape* wall_back = new Box    ("", Point(-1000,-1000,-1000), Point( 1000, 1000, -1050), white);
		Shape* sphere    = new Sphere ("", Point(    0, -500, -800),                       180, white);
		
		// set background color
		rgb bgcolor(0,0,0);
		
		// store shapes in composite
		CompositeShape* shapes = new CompositeShape("");

		shapes->push(wall_back);
		shapes->push(sphere);
		
		// define ambient light, must be of type AmbientLight*
		AmbientLight* amb = new AmbientLight ("", 0, rgb(1,1,1));
		
		// define point light
		Light* p1 = new PointLight ("", 1, rgb(1,0,0), Point(   0, 200,-300));
		Light* p2 = new PointLight ("", 1, rgb(0,1,0), Point( 200,-200,-300));
		Light* p3 = new PointLight ("", 1, rgb(0,0,1), Point(-200,-200,-300));
		
		// make a camera
		Camera* cam = new Camera ("", gw.width(), gw.height(), 30);
		
		// add elements to scene
		Scene* scene = new Scene();
		scene->push(shapes);
		scene->set(bgcolor);
		scene->set(amb);
		scene->push(p1);
		scene->push(p2);
		scene->push(p3);
		scene->set(cam);
		
		// preparations for filename
		time_t      t = time(NULL);
		struct tm* lt = localtime(&t);
		char time_str [80];
		strftime(time_str,80,"%Y-%m-%d__%H-%M-%S",lt);
		std::string filename = "images/raytrace__" + std::string(time_str) + ".png";
		
		// render the scene
		cam->render(filename);
	}
	
};





int main(int argc, char* argv[])
{
	const std::size_t width = 500;
	const std::size_t height = 500;
	
	glutwindow::init(width, height, 100, 100, "Raytracer", argc, argv);
	
	rt_application app;
	boost::thread thr(boost::bind(&rt_application::cornell_box, &app));
	
	glutwindow::instance().run();
	
	thr.join();
	return 0;
}