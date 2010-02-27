// i/f header
#include "shape.hpp"

// system header
#include <string>    // std::string
#include <iostream>  // NULL

// project header
// #include <material.hpp>

Shape::Shape () :
	name_(""), material_ptr_(NULL)
{}


Shape::Shape ( std::string name, Matrix trans ) :
	name_(name), trans_(trans)
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

void
Shape::transform ( const Matrix& trans )
{
	trans_ *= trans;
}