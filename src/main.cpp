// system header
#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <GL/glut.h>
#include <ctime>

// project header
#include <sdfloader.hpp>
#include <glutwindow.hpp>
#include <pixel.hpp>
#include <rgb.hpp>
#include <scene.hpp>
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
#include <reflective.hpp>
#include <transparent.hpp>
#include <light.hpp>
#include <ambientlight.hpp>
#include <pointlight.hpp>


/*! \mainpage Raytracer by Patrick Gombert, Patrick Oscity and Frank Urbainsky
 * \htmlonly
 * <center> <a href="UML2.pdf">UML diagramm of the tracer</a> </center>
 * \endhtmlonly
 *
 * \section intro_sec How to use
 *
 * \subsection step1 Step 1: Place an .sdf file in the ./sdf folder for the raytracer to notice it
 * \subsection step2 Step 2: 'make' the project or run your compiled binary
 * \subsection step3 Step 3: select your sdf file
 * \section step4 Enjoy!
 *
 * \image html cornell_box__2010-03-14__20-43-37.png Cornell Box with glass spheres
 */


int main(int argc, char* argv[])
{
	const std::size_t width = 500;
	const std::size_t height = 500;
	
	glutwindow::init(width, height, 100, 100, "Raytracer", argc, argv);
	
	sdfloader sl;
	boost::thread thr(boost::bind(&sdfloader::load, &sl));
	// rt_application rt;
	// boost::thread thr(boost::bind(&rt_application::cornell_box, &rt));
	
	glutwindow::instance().run();
	
	thr.join();
	return 0;
}
