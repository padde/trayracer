// header i/f
#include "rgb.hpp"

// header, system
#include <algorithm>
#include <iostream>
#include <cmath>

// header, project


////////////////////////////////////////////////////////////////////////////////
rgb::rgb()
{
  data_[0] = 0;
  data_[1] = 0;
  data_[2] = 0;
}


////////////////////////////////////////////////////////////////////////////////
rgb::rgb(rgb const& rhs)
{
  data_[0] = rhs.data_[0];
  data_[1] = rhs.data_[1];
  data_[2] = rhs.data_[2];
}


////////////////////////////////////////////////////////////////////////////////
rgb::rgb(float r, float g, float b)
{
  data_[0] = r;
  data_[1] = g;
  data_[2] = b;
}


////////////////////////////////////////////////////////////////////////////////
rgb::rgb(const rgb::value_t& rgb)
{
  data_[0] = rgb;
  data_[1] = rgb;
  data_[2] = rgb;
}


////////////////////////////////////////////////////////////////////////////////
rgb::~rgb()
{}


////////////////////////////////////////////////////////////////////////////////
void
rgb::swap(rgb& rhs)
{
  std::swap(data_[0], rhs.data_[0]);
  std::swap(data_[1], rhs.data_[1]);
  std::swap(data_[2], rhs.data_[2]);
}



////////////////////////////////////////////////////////////////////////////////
void
rgb::print(std::ostream& os) const
{
  os << '(' << data_[0] << '|' << data_[1] << '|' << data_[2] << ')';
}


rgb&
rgb::max_to_one ()
{
	float max = std::max( data_[0], std::max( data_[1], data_[2] ) );
	
	if ( max > 1.0 )
	{
		data_[0] /= max;
		data_[1] /= max;
		data_[2] /= max;
	}
	
	return *this;
}

rgb&
rgb::powc ( float exp )
{
	data_[0] = pow(data_[0], exp);
	data_[1] = pow(data_[1], exp);
	data_[2] = pow(data_[2], exp);
	
	return *this;
}


////////////////////////////////////////////////////////////////////////////////
rgb::value_t& 
rgb::operator[](enum rgb::component c)
{
  return data_[c];
}



////////////////////////////////////////////////////////////////////////////////
const rgb::value_t& 
rgb::operator[](enum rgb::component c) const 
{
  return data_[c];
}



////////////////////////////////////////////////////////////////////////////////
rgb& 
rgb::operator=(rgb const& rhs)
{
  rgb tmp(rhs);
  swap(tmp);
  return *this;
}


////////////////////////////////////////////////////////////////////////////////
void 
rgb::operator+=(rgb const& rhs) 
{ 
  data_[0] += rhs.data_[0];
  data_[1] += rhs.data_[1];
  data_[2] += rhs.data_[2];
}

void 
rgb::operator*=(rgb const& rhs) 
{ 
  data_[0] *= rhs.data_[0];
  data_[1] *= rhs.data_[1];
  data_[2] *= rhs.data_[2];
}

void 
rgb::operator*=(float const& rhs) 
{ 
  data_[0] *= rhs;
  data_[1] *= rhs;
  data_[2] *= rhs;
}

void 
rgb::operator/=(float const& rhs) 
{ 
  data_[0] /= rhs;
  data_[1] /= rhs;
  data_[2] /= rhs;
}

/* friend */ rgb
operator* (const rgb& lhs, const rgb& rhs)
{
  rgb result(lhs);
  result *= rhs;
  return result;
}


/* friend */ rgb
operator* (const rgb& lhs, const float& rhs)
{
  rgb result(lhs);
  result *= rhs;
  return result;
}

/* friend */ rgb
operator* (const float& lhs, const rgb& rhs)
{
  return (rhs * lhs);
}

/* friend */ rgb
operator/ (const rgb& lhs, const float& rhs)
{
  rgb result(lhs);
  result /= rhs;
  return result;
}

/* friend */ rgb
operator/ (const float& lhs, const rgb& rhs)
{
  return (rhs * lhs);
}

////////////////////////////////////////////////////////////////////////////////
rgb 
operator+(rgb const& a, rgb const& b) 
{
  rgb result(a);
  result += b;
  return result;
}


////////////////////////////////////////////////////////////////////////////////
std::ostream& 
operator<<(std::ostream& os, rgb const& color) 
{
  color.print(os);
  return os;
}
