#ifndef BUW_SHAPE_HPP
#define BUW_SHAPE_HPP

// system header
#include <string>

// project header
#include <rgb.hpp>
#include <ray.hpp>
#include <matrix.hpp>
#include <hitrecord.hpp>
#include <material.hpp>



class Shape
{
public: // enums, typedefs
	typedef float interval_t;

public: // c'tors, d'tor
	Shape ();
	Shape ( std::string name );
	Shape ( std::string name, Material* material );
	virtual ~Shape ();

public: // methods
	const std::string& name () const;  // name_ getter
	void name ( const std::string& );  // name_ setter
	
	virtual void transform ( const Matrix& ); // multiplicate trans_ with given matrix

public: // virtual methods
	virtual bool hit ( const Ray& ray, interval_t tmin, interval_t tmax, HitRecord& hitrec ) const = 0; // compute intersections with given ray, store result in hitrec
	virtual bool hit ( const Ray& ray, interval_t tmin, interval_t tmax ) const = 0;                    // no hitrec for saving time

private:
	std::string name_;

protected:	
	Material*   material_ptr_;
	Matrix      trans_;
};

#endif //BUW_SHAPE_HPP 