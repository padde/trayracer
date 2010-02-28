#ifndef BUW_SHAPE_HPP
#define BUW_SHAPE_HPP

// system header
#include <string>

// project header
#include <rgb.hpp>
#include <ray.hpp>
#include <matrix.hpp>
// #include <material.hpp>
class Material; // FIXME: uncomment above line and delete this one, when material is implemented



// struct for recording hits
struct HitRecord
{
	bool   hit;
	float  t;
	rgb    color;
	Vector normal;
};



class Shape
{
public: // enums, typedefs
	typedef float interval_t;

public: // c'tors, d'tor
	Shape ();
	Shape ( std::string name, Matrix trans );
	Shape ( std::string name, Material* material );
	Shape ( std::string name, Material* material, Matrix trans );
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
	Material*   material_ptr_;

protected:
	Matrix      trans_;
};

#endif //BUW_SHAPE_HPP 