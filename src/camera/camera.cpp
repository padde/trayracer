#include "camera.hpp"

// project header
#include <ray.hpp>
#include <pixel.hpp>
#include <point.hpp>
#include <vector.hpp>

// system header
#include <string>
#include <cmath>



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

Ray
Camera::ray_for_pixel ( const pixel p ) const
{
	float s = 1; // pixel size
	
	Point  origin    = Point  ( 0, 0, 1800 );
	Vector direction = Vector ( s * ( p.x - 0.5 * (width_ )), /* x value */
	                            s * ( p.y - 0.5 * (height_)), /* y value */
	                            - vpd_ );                     /* z value */
	
	return Ray ( origin, direction );
}