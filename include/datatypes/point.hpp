#ifndef BUW_POINT_HPP
#define BUW_POINT_HPP

// system header
#include <ostream>



// forward declarations
class Vector;


class Point
{
public: // enums, typedefs
	typedef float value_t;
	
public: // c'tors, d'tor
	Point ();
	Point (const Point& p);
	// Point (const Vector& v);
	Point (const value_t& x, const value_t& y, const value_t& z);
	~Point ();
	
public: // methods	
	value_t&       operator[](unsigned int index);
	const value_t& operator[](unsigned int index) const;
	
	Point& operator=  (const Point& p);
	void   operator+= (const Point& p);
	void   operator-= (const Point& p);
	
	// Point& operator=  (const Vector& p);
	//
	// void   operator+= (const Vector& v);
	// void   operator-= (const Vector& v);
	
	void swap (Point& p);
	
	void print_on (std::ostream& os) const;
	
public: // friends
	friend Point operator+  (const Point& p1, const Point& p2);
	friend Point operator-  (const Point& p1, const Point& p2);
	
	// friend Point operator+  (const Point& p1, const Vector& p2);
	// friend Point operator-  (const Point& p1, const Vector& p2);
	
	friend bool operator== (const Point& p1, const Point& p2);
	friend bool operator!= (const Point& p1, const Point& p2);
	
	friend std::ostream& operator<< (std::ostream& os, Point const& p);
	
private: // members
	value_t data_[3]; // x,y,z
};

#endif //BUW_POINT_HPP


