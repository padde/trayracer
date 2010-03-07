#include "material.hpp"



Material::Material ( std::string name ) :
	name_ (name)
{}

/* virtual */
Material::~Material()
{}

std::string
Material::name () const
{
	return name_;
}