#include "shape.hpp"



Shape::Shape ( std::string name ) :
	name_(name), material_ptr_(NULL)
{}

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
Shape::transform ( const Matrix& trans )
{
	Matrix tmp(trans);
	tmp.invert();
	trans_ *= tmp;
}