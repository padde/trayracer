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


Camera::Camera ( std::string name, std::size_t hres, std::size_t vres, float angle_deg ) :
	name_ ( name ),
	hres_ ( hres ),
	vres_ ( vres )
{
	// get width and height
	glutwindow& gw = glutwindow::instance();
	hres_ = gw.width();
	vres_ = gw.height();
	
	// convert angle from deg to rad
	angle_ = deg_to_rad(angle_deg);
	
	// compute view plane distance
	vpd_ = abs ( (hres_ / 2) / tan(angle_ / 2 ) );
}

Camera::~Camera ()
{}

void
Camera::render ( std::string filename ) const
{
	glutwindow& gw = glutwindow::instance();
	float gamma = 1/1.6;
	float s = 1.0; // pixel size
	int num_samples = 9;
	int n = std::size_t(sqrt(float(num_samples)));
	Point origin = Point ( 0, 0, 1800 );
	
	png::image< png::rgb_pixel > png(hres_,vres_);
	
	// loop through all pixels of the viewplane
	for (std::size_t y = 0; y < hres_; ++y)
	{
		for (std::size_t x = 0; x < vres_; ++x)
		{
			// create pixel
			pixel p (x,y);
			
			for (int i=0; i<n; ++i)
			{
				for (int j=0; j<n; ++j)
				{
					Vector direction = Vector ( s * (p.x - 0.5 * hres_ + ( j + 0.5) / n ),
					                            s * (p.y - 0.5 * vres_ + ( i + 0.5) / n ),
					                            - vpd_ );
					direction.unify();                     
					Ray ray( origin, direction );
					
					p.color += scene_ptr->tracer_ptr->trace(ray, 0);
				}
			}
			p.color /= num_samples;
			/*
			if ( x > 425 and x < 435 and y > 140 and y < 150 )
			{
				std::cout << "x=" << x << ", y=" << y << ", color=" << p.color << std::endl;
			}
			*/
			// add gamma, clamp colors
			if (gamma != 1)
				p.color.powc(gamma);
			// p.color *= 2;
			p.color.max_to_one();
			
			// write pixel to window
			gw.write(p);
			
			// write pixel to png file
			int r = p.color[rgb::r] * 255;
			int g = p.color[rgb::g] * 255;
			int b = p.color[rgb::b] * 255;
			png[vres_-y-1][x] = png::rgb_pixel(r,g,b);
			
			
		}
	}
	
	// save png image
	png.write(filename);
	std::cout << "image saved as " << filename << std::endl;
}

std::string
Camera::name () const
{
	return name_;
}