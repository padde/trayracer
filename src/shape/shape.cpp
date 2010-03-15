#include "shape.hpp"

// project header
#include <box.hpp>

// system header
#include <limits>

namespace {
	float floatmax = std::numeric_limits<float>::max();
	float floatmin = std::numeric_limits<float>::min();
}



Shape::Shape ( std::string name ) :
	name_(name), material_ptr_(NULL)
{
	bbox_.first  = Point(floatmin,floatmin,floatmin);
	bbox_.second = Point(floatmax,floatmax,floatmax);
}

Shape::Shape ( std::string name, Material* material ) :
	name_(name), material_ptr_(material)
{}

/* virtual */
Shape::~Shape ()
{}

const std::string&
Shape::name () const
{
	return name_;
}

void
Shape::name ( const std::string& name )
{
	name_ = name;
}

/* virtual */ void
Shape::transform ( const Matrix& new_trans )
{
	trans_      = trans_ * new_trans;
	inv_trans_  = inverse(new_trans) * inv_trans_;
	back_trans_ = transpose(trans_);
}

/* virtual */ Box
Shape::bbox () const
{
	return Box("",bbox_.first,bbox_.second,NULL);
}