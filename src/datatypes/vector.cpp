// system header
#include <ostream>
#include <cmath>
#include <cassert>

// project header
#include "vector.hpp"
#include "point.hpp"


Vector::Vector ()
{
	data_[0] = 0;
	data_[1] = 0;
	data_[2] = 0;
}

Vector::Vector (const Vector& v)
{
	data_[0] = v[0];
	data_[1] = v[1];
	data_[2] = v[2];
}

Vector::Vector (const Point& p)
{
	data_[0] = p[0];
	data_[1] = p[1];
	data_[2] = p[2];
}

Vector::Vector (const Point& p1, const Point& p2)
{
	*this = p1 - p2;
}

Vector::Vector (const Vector::value_t& x, const Vector::value_t& y, const Vector::value_t& z)
{
	data_[0] = x;
	data_[1] = y;
	data_[2] = z;
}

Vector::~Vector ()
{
	
}

Vector::value_t&
Vector::operator[] (unsigned int index)
{
	assert( index >= 0 && index <=2 );
	return data_[index];
}

const Vector::value_t&
Vector::operator[] (unsigned int index) const
{
	assert( index >= 0 && index <=2 );
	return data_[index];
}

Vector::value_t
Vector::length () const
{
	return sqrt(
		pow(data_[0], 2) +
		pow(data_[1], 2) +
		pow(data_[2], 2)
	);
}

void
Vector::unify ()
{
	*this /= length();
}

Vector&
Vector::operator= (const Vector& v)
{
	Vector tmp(v);
	swap(tmp);
	return *this;
}

void
Vector::operator+= (const Vector& v)
{
	data_[0] += v.data_[0];
	data_[1] += v.data_[1];
	data_[2] += v.data_[2];
}

void
Vector::operator-= (const Vector& v)
{
	data_[0] -= v.data_[0];
	data_[1] -= v.data_[1];
	data_[2] -= v.data_[2];
}

void
Vector::operator*= (const Vector::value_t& scalar)
{
	data_[0] *= scalar;
	data_[1] *= scalar;
	data_[2] *= scalar;
}

void
Vector::operator/= (const Vector::value_t& scalar)
{
	data_[0] /= scalar;
	data_[1] /= scalar;
	data_[2] /= scalar;
}

Vector&
Vector::operator= (const Point& p)
{
	Vector tmp(p[0], p[1], p[2]);
	swap(tmp);
	return *this;
}

void
Vector::swap (Vector& v)
{
	std::swap(data_[0], v.data_[0]);
	std::swap(data_[1], v.data_[1]);
	std::swap(data_[2], v.data_[2]);
}

void
Vector::print_on (std::ostream& os) const
{
	os << "Vector (" << data_[0] << "," << data_[1] << "," << data_[2] << ")"; 
}

/* friend */ Vector
operator+ (const Vector& lhs, const Vector& rhs)
{
	Vector tmp(lhs);
	tmp += rhs;
	return tmp;
}

/* friend */ Vector
operator- (const Vector& lhs, const Vector& rhs)
{
	Vector tmp(lhs);
	tmp -= rhs;
	return tmp;
}

/* friend */ Vector
operator* (const Vector::value_t& scalar, const Vector& rhs)
{
	return rhs * scalar;
}

/* friend */ Vector
operator* (const Vector& lhs, const Vector::value_t& scalar)
{
	Vector tmp(lhs);
	tmp *= scalar;
	return tmp;
}

/* friend */ Vector
operator/ (const Vector& lhs, const Vector::value_t& scalar)
{
	Vector tmp(lhs);
	tmp /= scalar;
	return tmp;
}

/* friend */ bool
operator== (const Vector& lhs, const Vector& rhs)
{
	return (
		lhs.data_[0] == rhs.data_[0] &&
		lhs.data_[1] == rhs.data_[1] &&
		lhs.data_[2] == rhs.data_[2] );
}

/* friend */ bool
operator!= (const Vector& lhs, const Vector& rhs)
{
	if ( lhs == rhs )
		return false;
	else
		return true;
}

/* friend */ Vector::value_t
dot (const Vector& lhs, const Vector& rhs)
{
	return (
		lhs.data_[0] * rhs.data_[0] +
		lhs.data_[1] * rhs.data_[1] +
		lhs.data_[2] * rhs.data_[2] );
}

/* friend */ Vector
cross (const Vector& lhs, const Vector& rhs)
{
	return Vector (
		lhs.data_[1] * rhs.data_[2] - lhs.data_[2] * rhs.data_[1],
		lhs.data_[2] * rhs.data_[0] - lhs.data_[0] * rhs.data_[2],
		lhs.data_[0] * rhs.data_[1] - lhs.data_[1] * rhs.data_[0] );
}

/* friend */ std::ostream&
operator<< (std::ostream& os, Vector const& v)
{
	std::ostream::sentry const cerberus(os);
	if (cerberus) v.print_on(os);
	return os;
}


