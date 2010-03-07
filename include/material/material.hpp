#ifndef BUW_MATERIAL_HPP
#define BUW_MATERIAL_HPP

// system header
#include <string>

// project header
#include <rgb.hpp>

// fwd declarations
class HitRecord;



class Material
{
public: // c'tors, d'tor
	Material ( std::string name );
	virtual ~Material();
	
public: // methods
	virtual rgb shade ( HitRecord& hitrec ) const = 0;
	std::string name () const;
	
private: // members
	std::string name_;
	
};

#endif //BUW_MATERIAL_HPP