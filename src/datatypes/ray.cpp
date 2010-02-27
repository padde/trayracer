// i/f header
#include "ray.hpp"

// system header
#include <ostream>

// project header
#include <point.hpp>
#include <vector.hpp>
#include <matrix.hpp>


Ray::Ray () :
	origin_(0,0,0), dir_(0,0,0)
{}

Ray::Ray ( const Ray& r ) :
	origin_(r.origin_), dir_(r.dir_)
{}

Ray::Ray ( const Point& origin, const Point& target ) :
	origin_(origin), dir_( target - origin )
{}

Ray::Ray ( const Point& origin, const Vector& dir ) :
	origin_(origin), dir_(dir)
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

Ray
Ray::transform ( const Matrix& trans ) const
{
	return Ray( trans * origin_, trans * dir_ );
}

Point
Ray::point_at_parameter ( const Ray::scalar_t& param )
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


