#ifndef BUW_MATRIX_HPP
#define BUW_MATRIX_HPP

// system header
#include <iosfwd>

// forward declarations
class Vector;
class Point;


class Matrix 
{
public : // c'tors, d'tor
	Matrix  ( );
	Matrix  ( Matrix const& );
	Matrix  ( double const [16] );
	~Matrix ( );
	
public : // methods
	void          swap          ( Matrix& rhs );
	Matrix&       operator=     ( Matrix const& rhs );
	double const& operator()    ( unsigned row, unsigned col ) const;
	double&       operator()    ( unsigned row, unsigned col );
	double const& operator[]    ( unsigned ) const;
	double&       operator[]    ( unsigned );
	Matrix&       operator*=    ( Matrix const& );
	double        determinant   ( ) const;
	bool          invert        ( );
	void          transpose     ( );
	bool          is_invertible ( ) const;
	
public : // static methods
	static Matrix const& null();
	static Matrix const& identity();
	
private: // members
	double data_[16];
};

Matrix operator*  ( Matrix const&, Matrix const&  );
Matrix operator*  ( Matrix const&, double         );
Matrix operator*  ( double,        Matrix const&  );
Matrix operator/  ( Matrix const&, double         );
Point  operator*  ( Matrix const&, Point const& );
Vector operator*  ( Matrix const&, Vector const&);
bool   operator== ( Matrix const&, Matrix const&  );
bool   operator!= ( Matrix const&, Matrix const&  );

std::ostream& operator<< ( std::ostream&, Matrix const&  );

Matrix make_translation ( double, double, double );
Matrix make_translation ( Vector const& );
Matrix make_scale       ( double, double, double );
Matrix make_scale       ( Vector const& );
Matrix make_rotation_x  ( double );
Matrix make_rotation_y  ( double );
Matrix make_rotation_z  ( double );

double determinant   ( Matrix const& );
Matrix inverse       ( Matrix const& );
Matrix transpose     ( Matrix const& );
bool   is_invertible ( Matrix const& );

#endif // BUW_MATRIX_HPP
