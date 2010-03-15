#ifndef BUW_SHAPE_HPP
#define BUW_SHAPE_HPP

// system header
#include <string>
#include <algorithm>

// project header
#include <rgb.hpp>
#include <ray.hpp>
#include <matrix.hpp>
#include <hitrecord.hpp>
#include <material.hpp>

// fwd declarations
class Box;


//! @author Patrick Oscity
//! @date January 2010
//! @brief ... abstract shape class for inheritance
//
class Shape
{
public: // enums, typedefs
	typedef float interval_t;

public: // c'tors, d'tor
	Shape ( std::string name );
	Shape ( std::string name, Material* material );
	virtual ~Shape ();

public: // methods
	const std::string& name () const;  // name_ getter
	void name ( const std::string& );  // name_ setter
	
	virtual void transform ( const Matrix& ); // multiplicate trans_ with given matrix
	
	virtual Box bbox () const;
	
public: // virtual methods
	virtual bool hit ( const Ray& ray, interval_t& tmin, HitRecord& hitrec ) const = 0; // compute intersections with given ray, store result in hitrec
	virtual bool hit ( const Ray& ray, interval_t& tmin ) const = 0;                    // no hitrec for saving time

private:
	std::string name_;

protected:	
	Material*   material_ptr_;
	Matrix      trans_;
	Matrix      inv_trans_;
	Matrix      back_trans_;
	std::pair<Point,Point> bbox_;
};

#endif //BUW_SHAPE_HPP 
