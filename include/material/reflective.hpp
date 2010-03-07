#ifndef BUW_REFLECTIVE_HPP
#define BUW_REFLECTIVE_HPP

// system header
#include <string>

// project header
#include <rgb.hpp>
#include <phong.hpp>
#include <perfectspecular.hpp>
#include <hitrecord.hpp>



class Reflective : public Phong
{
public: // c'tors, d'tor
	Reflective ( std::string name, const rgb ka, const rgb kd, const rgb ks, const float exp, const rgb kr );
	~Reflective();
	
public: // methods
	virtual rgb shade ( HitRecord& hitrec ) const;
	
private: // members
	PerfectSpecular* reflective_brdf_ptr_;
};

#endif //BUW_REFLECTIVE_HPP