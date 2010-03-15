#ifndef BUW_POINT_HPP
#define BUW_POINT_HPP

// system header
#include <ostream>



// forward declarations
class Vector;

//! @author Bauhaus Uni Weimar
//! @date ???
//! @brief ... Basic point class
//
class Point
{
public: // enums, typedefs
	typedef float value_t;
	
public: // c'tors, d'tor
	Point ();
	Point (const Point& p);
	Point (const Vector& v);
	Point (const value_t& x, const value_t& y, const value_t& z);
	~Point ();
	
public: // methods	
	value_t&       operator[](unsigned int index);
	const value_t& operator[](unsigned int index) const;
	
	Point& operator=  (const Point& p);
	void   operator+= (const Point& p);
	void   operator-= (const Point& p);
	
	Point& operator=  (const Vector& v);
	void   operator+= (const Vector& v);
	void   operator-= (const Vector& v);
	
	void swap (Point& p);
	
	void print_on (std::ostream& os) const;
	
public: // friends
	friend Vector operator+ (const Point& lhs, const Point& rhs);
	friend Vector operator- (const Point& lhs, const Point& rhs);
	
	friend Point operator+ (const Point& lhs, const Vector& rhs);
	friend Point operator- (const Point& lhs, const Vector& rhs);
	
	friend bool operator== (const Point& lhs, const Point& rhs);
	friend bool operator!= (const Point& lhs, const Point& rhs);
	
	friend std::ostream& operator<< (std::ostream& os, Point const& p);
	
private: // members
	value_t data_[3]; // x,y,z
};

#endif //BUW_POINT_HPP


