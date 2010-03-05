// i/f header
#include "point.hpp"

// system header
#include <ostream>
#include <cassert>

// project header
#include <vector.hpp>


Point::Point ()
{
	data_[0] = 0;
	data_[1] = 0;
	data_[2] = 0;
}

Point::Point (const Point& p)
{
	data_[0] = p.data_[0];
	data_[1] = p.data_[1];
	data_[2] = p.data_[2];
}

Point::Point (const Vector& v)
{
	data_[0] = v[0];
	data_[1] = v[1];
	data_[2] = v[2];
	
}

Point::Point (const Point::value_t& x, const Point::value_t& y, const Point::value_t& z)
{
	data_[0] = x;
	data_[1] = y;
	data_[2] = z;
}

Point::~Point ()
{}

Point::value_t&
Point::operator[](unsigned int index)
{
	assert ( index >= 0 && index < 3 );
	return data_[index];
}

const Point::value_t&
Point::operator[](unsigned int index) const
{
	assert ( index >= 0 && index < 3 );
	return data_[index];
}

Point&
Point::operator= (const Point& p)
{
	Point tmp(p);
	swap(tmp);
	return *this;
}

void
Point::operator+= (const Point& p)
{
	data_[0] += p.data_[0];
	data_[1] += p.data_[1];
	data_[2] += p.data_[2];
}

void
Point::operator-= (const Point& p)
{
	data_[0] -= p.data_[0];
	data_[1] -= p.data_[1];
	data_[2] -= p.data_[2];
}

Point&
Point::operator= (const Vector& v)
{
	Point tmp(v[0], v[1], v[2]);
	swap(tmp);
	return *this;
}

void
Point::operator+= (const Vector& v)
{
	data_[0] += v[0];
	data_[1] += v[1];
	data_[2] += v[2];
}

void
Point::operator-= (const Vector& v)
{
	data_[0] -= v[0];
	data_[1] -= v[1];
	data_[2] -= v[2];
}

void
Point::swap (Point& p)
{
	std::swap(data_[0], p.data_[0]);
	std::swap(data_[1], p.data_[1]);
	std::swap(data_[2], p.data_[2]);
}

void
Point::print_on (std::ostream& os) const
{
	os << "Point (" << data_[0] << "," << data_[1] << "," << data_[2] << ")"; 
}

/* friend */ Vector
operator+ (const Point& lhs, const Point& rhs)
{
	Vector tmp(lhs);
	tmp += rhs;
	return tmp;
}

/* friend */ Vector
operator- (const Point& lhs, const Point& rhs)
{
	Vector tmp(lhs);
	tmp -= rhs;
	return tmp;
}

/* friend */ Point
operator+ (const Point& p, const Vector& v)
{
	Point tmp(p);
	tmp += v;
	return tmp;
}

/* friend */ Point
operator- (const Point& p, const Vector& v)
{
	Point tmp(p);
	tmp -= v;
	return tmp;
}

/* friend */ bool
operator== (const Point& lhs, const Point& rhs)
{
	return (
		lhs.data_[0] == rhs.data_[0] &&
		lhs.data_[1] == rhs.data_[1] &&
		lhs.data_[2] == rhs.data_[2] );
}

/* friend */ bool
operator!= (const Point& lhs, const Point& rhs)
{
	if ( lhs == rhs )
		return false;
	else
		return true;
}

/* friend */ std::ostream&
operator<< (std::ostream& os, Point const& p)
{
	std::ostream::sentry const cerberus(os);
	if (cerberus) p.print_on(os);
	return os;
}


