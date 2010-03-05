#include "camera.hpp"

// project header
#include <ray.hpp>
#include <pixel.hpp>
#include <point.hpp>
#include <vector.hpp>
#include <glutwindow.hpp>
#include <scene.hpp>

// system header
#include <string>
#include <cmath>
#include <GL/glut.h>
#include <png++/image.hpp>
#include <png++/rgb_pixel.hpp>



namespace {
	
	double
	deg_to_rad(double angle)
	{
		// a deg -> a*(180/pi) rad
		return angle * 0.0174533;
	}
}


Camera::Camera ( std::string name, std::size_t width, std::size_t height, float angle_deg ) :
	name_   ( name   ),
	width_  ( width  ),
	height_ ( height )
{	
	// convert angle from deg to rad
	angle_ = deg_to_rad(angle_deg);
	
	// compute view plane distance
	vpd_ = abs ( (width_ / 2) / tan(angle_ / 2 ) );
}

Camera::~Camera ()
{}

void
Camera::render ( std::string filename ) const
{
	glutwindow& gw = glutwindow::instance();
	std::size_t width  = gw.width();
	std::size_t height = gw.height();
	float gamma = 2.0;
	
	png::image< png::rgb_pixel > png(width,height);
	
	// loop through all pixels of the viewplane
	for (std::size_t y = 0; y < height; ++y)
	{
		for (std::size_t x = 0; x < width; ++x)
		{
			// create pixel
			pixel p (x,y);
			
			// create ray
			Point  origin    = Point  ( 0, 0, 1800 );
			Vector direction = Vector ( p.x - 0.5 * (width_ ), /* x value */
			                            p.y - 0.5 * (height_), /* y value */
			                            - vpd_ );              /* z value */
			Ray ray( origin, direction );
			
			p.color = scene_ptr->tracer_ptr->trace(ray);
			
			// add gamma, clamp colors
			p.color *= gamma;
			p.color.max_to_one();
			
			// write pixel to window
			gw.write(p);
			
			// write pixel to png file
			int r = p.color[rgb::r] * 255;
			int g = p.color[rgb::g] * 255;
			int b = p.color[rgb::b] * 255;
			png[height-y-1][x] = png::rgb_pixel(r,g,b);
			
			
		}
	}
	
	// save png image
	png.write(filename);
	std::cout << "image saved as " << filename << std::endl;
}