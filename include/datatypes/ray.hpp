#ifndef BUW_RAY_HPP
#define BUW_RAY_HPP

// system header
#include <ostream>

// project header
#include <point.hpp>
#include <vector.hpp>


class Ray
{
public: // enums, typedefs
	typedef float scalar_t;

public: // c'tors, d'tor
	Ray ();
	Ray ( const Ray& r );
	Ray ( const Point& origin, const Point& target );
	Ray ( const Point& origin, const Vector& dir );
	~Ray ();
	
public: // methods
	const Point& origin () const;
	Point&       origin ( const Point& p );
	
	const Vector& dir () const;
	Vector&       dir ( const Vector& v );
	
	Point point_at_parameter ( const scalar_t& param );
	
	void print_on (std::ostream& os) const;
	
public: // friends
	friend std::ostream& operator<< (std::ostream& os, Ray const& r);
	
private:
	Point origin_;
	Vector dir_;
};

#endif //BUW_RAY_HPP 