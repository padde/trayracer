// i/f header
#include "shape.hpp"

// system header
#include <string>    // std::string
#include <iostream>  // NULL

// project header
// #include <material.hpp>

Shape::Shape () :
	name_(""), material_(NULL)
{}

Shape::Shape ( std::string name, Material* material ) :
	name_(name), material_(material)
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

const Matrix&
Shape::trans () const
{
	return trans_;
}

void
Shape::trans ( const Matrix& trans )
{
	trans_ = trans;
}

void
Shape::trans_mult ( const Matrix& trans )
{
	trans_ *= trans;
}