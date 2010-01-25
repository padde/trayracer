// i/f header
#include "ray.hpp"

// system header
#include <ostream>

// project header
#include <point.hpp>
#include <vector.hpp>


Ray::Ray () :
	origin_(0,0,0),
	dir_   (0,0,0)
{}

Ray::Ray ( const Ray& r ) :
	origin_(r.origin_),
	dir_   (r.dir_)
{}

Ray::Ray ( const Point& p, const Vector& v ) :
	origin_(p),
	dir_   (v)
{}

Ray::~Ray ()
{}

const Point&
Ray::origin () const
{
	return origin_;
}

Point&
Ray::origin ( const Point& p )
{
	origin_ = p;
	return origin_;
}

const Vector&
Ray::dir () const
{
	return dir_;
}

Vector&
Ray::dir ( const Vector& v )
{
	dir_ = v;
	return dir_;
}

Point
Ray::point_at_parameter ( const float& param )
{
	return origin_ + dir_ * param;
}

void
Ray::print_on (std::ostream& os) const
{
	os << "Ray ( Origin: " << origin_ << ", Direction: " << dir_ << " )";
}

/* friend */ std::ostream&
operator<< (std::ostream& os, Ray const& r)
{
	std::ostream::sentry const cerberus(os);
	if (cerberus) r.print_on(os);
	return os;
}


