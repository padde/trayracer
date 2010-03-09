// i/f header
#include "matrix.hpp"

// system header
#include <algorithm>              // std::copy, std::swap_ranges
#include <cmath>                  // std::cos, std::sin
#include <iomanip>                // std::fixed, std::setprecision
#include <ostream>                // std::ostream
#include <limits>                 // std::numeric_limits
#include <cassert>                // assert

// project header
#include <point.hpp>
#include <vector.hpp>

namespace {
	
	double const null_array16[16] = {
		0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0
	};

	double const ident_array16[16] = {
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0
	};
	
	// functions, internal
	
	double
	det3_helper(
		double a1, double a2, double a3,
		double b1, double b2, double b3,
		double c1, double c2, double c3)
	{
		return (
			(a1 * b2 * c3) + (a2 * b3 * c1) + (a3 * b1 * c2) -
			(a1 * b3 * c2) - (a2 * b1 * c3) - (a3 * b2 * c1));
	}
	
	double
	deg_to_rad(double angle)
	{
		// a deg -> a*(180/pi) rad
		return angle * 0.0174533;
	}
}



Matrix::Matrix()
{
	std::copy(ident_array16, ident_array16+16, data_);
}

Matrix::Matrix(Matrix const& rhs)
{
	std::copy(rhs.data_, rhs.data_+16, data_);
}

Matrix::Matrix(double const a[16])
{
	std::copy(a, a+16, data_);
}

Matrix::~Matrix()
{}


void Matrix::swap(Matrix& rhs)
{
	std::swap_ranges(data_, data_+16, rhs.data_);
}

Matrix&
Matrix::operator=(Matrix const& rhs)
{
	Matrix tmp(rhs);
	swap(tmp);
	return *this;
}

double const&
Matrix::operator()(unsigned row, unsigned col) const
{
	assert(16 > row * 4 + col);
	return data_[(row * 4) + col];
}

double&
Matrix::operator()(unsigned row, unsigned col)
{
	assert(16 > row * 4 + col);
	return data_[(row * 4) + col];
}

double const& 
Matrix::operator[](unsigned i) const
{
	return data_[i];
}

double&       
Matrix::operator[](unsigned i)
{
	return data_[i];
}

Matrix&
Matrix::operator*=(Matrix const& rhs)
{
	Matrix tmp;
	
	tmp.data_[ 0] = (data_[ 0] * rhs.data_[ 0] +
	                 data_[ 4] * rhs.data_[ 1] +
	                 data_[ 8] * rhs.data_[ 2] +
	                 data_[12] * rhs.data_[ 3]);
	
	tmp.data_[ 1] = (data_[ 1] * rhs.data_[ 0] +
	                 data_[ 5] * rhs.data_[ 1] +
	                 data_[ 9] * rhs.data_[ 2] +
	                 data_[13] * rhs.data_[ 3]);
	
	tmp.data_[ 2] = (data_[ 2] * rhs.data_[ 0] +
	                 data_[ 6] * rhs.data_[ 1] +
	                 data_[10] * rhs.data_[ 2] +
	                 data_[14] * rhs.data_[ 3]);
	
	tmp.data_[ 3] = (data_[ 3] * rhs.data_[ 0] +
	                 data_[ 7] * rhs.data_[ 1] +
	                 data_[11] * rhs.data_[ 2] +
	                 data_[15] * rhs.data_[ 3]);
	
	tmp.data_[ 4] = (data_[ 0] * rhs.data_[ 4] +
	                 data_[ 4] * rhs.data_[ 5] +
	                 data_[ 8] * rhs.data_[ 6] +
	                 data_[12] * rhs.data_[ 7]);
	
	tmp.data_[ 5] = (data_[ 1] * rhs.data_[ 4] +
	                 data_[ 5] * rhs.data_[ 5] +
	                 data_[ 9] * rhs.data_[ 6] +
	                 data_[13] * rhs.data_[ 7]);
	
	tmp.data_[ 6] = (data_[ 2] * rhs.data_[ 4] +
	                 data_[ 6] * rhs.data_[ 5] +
	                 data_[10] * rhs.data_[ 6] +
	                 data_[14] * rhs.data_[ 7]);
	
	tmp.data_[ 7] = (data_[ 3] * rhs.data_[ 4] +
	                 data_[ 7] * rhs.data_[ 5] +
	                 data_[11] * rhs.data_[ 6] +
	                 data_[15] * rhs.data_[ 7]);
	
	tmp.data_[ 8] = (data_[ 0] * rhs.data_[ 8] +
	                 data_[ 4] * rhs.data_[ 9] +
	                 data_[ 8] * rhs.data_[10] +
	                 data_[12] * rhs.data_[11]);
	
	tmp.data_[ 9] = (data_[ 1] * rhs.data_[ 8] +
	                 data_[ 5] * rhs.data_[ 9] +
	                 data_[ 9] * rhs.data_[10] +
	                 data_[13] * rhs.data_[11]);
	
	tmp.data_[10] = (data_[ 2] * rhs.data_[ 8] +
	                 data_[ 6] * rhs.data_[ 9] +
	                 data_[10] * rhs.data_[10] +
	                 data_[14] * rhs.data_[11]);
	
	tmp.data_[11] = (data_[ 3] * rhs.data_[ 8] +
	                 data_[ 7] * rhs.data_[ 9] +
	                 data_[11] * rhs.data_[10] +
	                 data_[15] * rhs.data_[11]);
	
	tmp.data_[12] = (data_[ 0] * rhs.data_[12] +
	                 data_[ 4] * rhs.data_[13] +
	                 data_[ 8] * rhs.data_[14] +
	                 data_[12] * rhs.data_[15]);
	
	tmp.data_[13] = (data_[ 1] * rhs.data_[12] +
	                 data_[ 5] * rhs.data_[13] +
	                 data_[ 9] * rhs.data_[14] +
	                 data_[13] * rhs.data_[15]);
	
	tmp.data_[14] = (data_[ 2] * rhs.data_[12] +
	                 data_[ 6] * rhs.data_[13] +
	                 data_[10] * rhs.data_[14] +
	                 data_[14] * rhs.data_[15]);
	
	tmp.data_[15] = (data_[ 3] * rhs.data_[12] +
	                 data_[ 7] * rhs.data_[13] +
	                 data_[11] * rhs.data_[14] +
	                 data_[15] * rhs.data_[15]);
	
	swap(tmp);
	
	return *this;
}


Matrix&
Matrix::operator*=( double rhs )
{
	Matrix tmp;
	
	tmp.data_[ 0] *= rhs;
	tmp.data_[ 1] *= rhs;
	tmp.data_[ 2] *= rhs;
	tmp.data_[ 3] *= rhs;
	tmp.data_[ 4] *= rhs;
	tmp.data_[ 5] *= rhs;
	tmp.data_[ 6] *= rhs;
	tmp.data_[ 7] *= rhs;
	tmp.data_[ 8] *= rhs;
	tmp.data_[ 9] *= rhs;
	tmp.data_[10] *= rhs;
	tmp.data_[11] *= rhs;
	tmp.data_[12] *= rhs;
	tmp.data_[13] *= rhs;
	tmp.data_[14] *= rhs;
	tmp.data_[15] *= rhs;
	
	swap(tmp);
	return *this;
}

Matrix&
Matrix::operator+=(Matrix const& rhs)
{
	Matrix tmp;
	
	tmp.data_[ 0] += rhs.data_[ 0];
	tmp.data_[ 1] += rhs.data_[ 1];
	tmp.data_[ 2] += rhs.data_[ 2];
	tmp.data_[ 3] += rhs.data_[ 3];
	tmp.data_[ 4] += rhs.data_[ 4];
	tmp.data_[ 5] += rhs.data_[ 5];
	tmp.data_[ 6] += rhs.data_[ 6];
	tmp.data_[ 7] += rhs.data_[ 7];
	tmp.data_[ 8] += rhs.data_[ 8];
	tmp.data_[ 9] += rhs.data_[ 9];
	tmp.data_[10] += rhs.data_[10];
	tmp.data_[11] += rhs.data_[11];
	tmp.data_[12] += rhs.data_[12];
	tmp.data_[13] += rhs.data_[13];
	tmp.data_[14] += rhs.data_[14];
	tmp.data_[15] += rhs.data_[15];
	
	swap(tmp);
	return *this;
}

Matrix&
Matrix::operator-=(Matrix const& rhs)
{
	Matrix tmp;
	
	tmp.data_[ 0] -= rhs.data_[ 0];
	tmp.data_[ 1] -= rhs.data_[ 1];
	tmp.data_[ 2] -= rhs.data_[ 2];
	tmp.data_[ 3] -= rhs.data_[ 3];
	tmp.data_[ 4] -= rhs.data_[ 4];
	tmp.data_[ 5] -= rhs.data_[ 5];
	tmp.data_[ 6] -= rhs.data_[ 6];
	tmp.data_[ 7] -= rhs.data_[ 7];
	tmp.data_[ 8] -= rhs.data_[ 8];
	tmp.data_[ 9] -= rhs.data_[ 9];
	tmp.data_[10] -= rhs.data_[10];
	tmp.data_[11] -= rhs.data_[11];
	tmp.data_[12] -= rhs.data_[12];
	tmp.data_[13] -= rhs.data_[13];
	tmp.data_[14] -= rhs.data_[14];
	tmp.data_[15] -= rhs.data_[15];
	
	swap(tmp);
	return *this;
}

double
Matrix::determinant() const
{
	double const& a1(data_[ 0]);
	double const& b1(data_[ 4]);
	double const& c1(data_[ 8]);
	double const& d1(data_[12]);
	
	double const& a2(data_[ 1]);
	double const& b2(data_[ 5]);
	double const& c2(data_[ 9]);
	double const& d2(data_[13]);
	
	double const& a3(data_[ 2]);
	double const& b3(data_[ 6]);
	double const& c3(data_[10]);
	double const& d3(data_[14]);
	
	double const& a4(data_[ 3]);
	double const& b4(data_[ 7]);
	double const& c4(data_[11]);
	double const& d4(data_[15]);
	
	return (
		a1 * det3_helper(b2, b3, b4, c2, c3, c4, d2, d3, d4) -
		b1 * det3_helper(a2, a3, a4, c2, c3, c4, d2, d3, d4) +
		c1 * det3_helper(a2, a3, a4, b2, b3, b4, d2, d3, d4) -
		d1 * det3_helper(a2, a3, a4, b2, b3, b4, c2, c3, c4) );
}

bool
Matrix::invert()
{
	bool         result(false);
	double const d(determinant());
	
	if ( 0.0 != d )
	{
		double const& a1(data_[ 0]);
		double const& b1(data_[ 4]);
		double const& c1(data_[ 8]);
		double const& d1(data_[12]);
		double const& a2(data_[ 1]);
		double const& b2(data_[ 5]);
		double const& c2(data_[ 9]);
		double const& d2(data_[13]);
		double const& a3(data_[ 2]);
		double const& b3(data_[ 6]);
		double const& c3(data_[10]);
		double const& d3(data_[14]);
		double const& a4(data_[ 3]);
		double const& b4(data_[ 7]);
		double const& c4(data_[11]);
		double const& d4(data_[15]);
		
		double const di(1.0 / d);
		
		Matrix tmp;
		
		tmp.data_[ 0] =  det3_helper(b2, b3, b4, c2, c3, c4, d2, d3, d4) * di;
		tmp.data_[ 1] = -det3_helper(a2, a3, a4, c2, c3, c4, d2, d3, d4) * di;
		tmp.data_[ 2] =  det3_helper(a2, a3, a4, b2, b3, b4, d2, d3, d4) * di;
		tmp.data_[ 3] = -det3_helper(a2, a3, a4, b2, b3, b4, c2, c3, c4) * di;
		tmp.data_[ 4] = -det3_helper(b1, b3, b4, c1, c3, c4, d1, d3, d4) * di;
		tmp.data_[ 5] =  det3_helper(a1, a3, a4, c1, c3, c4, d1, d3, d4) * di;
		tmp.data_[ 6] = -det3_helper(a1, a3, a4, b1, b3, b4, d1, d3, d4) * di;
		tmp.data_[ 7] =  det3_helper(a1, a3, a4, b1, b3, b4, c1, c3, c4) * di;
		tmp.data_[ 8] =  det3_helper(b1, b2, b4, c1, c2, c4, d1, d2, d4) * di;
		tmp.data_[ 9] = -det3_helper(a1, a2, a4, c1, c2, c4, d1, d2, d4) * di;
		tmp.data_[10] =  det3_helper(a1, a2, a4, b1, b2, b4, d1, d2, d4) * di;
		tmp.data_[11] = -det3_helper(a1, a2, a4, b1, b2, b4, c1, c2, c4) * di;
		tmp.data_[12] = -det3_helper(b1, b2, b3, c1, c2, c3, d1, d2, d3) * di;
		tmp.data_[13] =  det3_helper(a1, a2, a3, c1, c2, c3, d1, d2, d3) * di;
		tmp.data_[14] = -det3_helper(a1, a2, a3, b1, b2, b3, d1, d2, d3) * di;
		tmp.data_[15] =  det3_helper(a1, a2, a3, b1, b2, b3, c1, c2, c3) * di;
		
		swap(tmp);
		
		result = true;
	}
	
	return result;
}

void
Matrix::transpose()
{
	Matrix tmp(*this);
	data_[ 1] = tmp.data_[ 4];
	data_[ 2] = tmp.data_[ 8];
	data_[ 3] = tmp.data_[12];
	data_[ 4] = tmp.data_[ 1];
	data_[ 6] = tmp.data_[ 9];
	data_[ 7] = tmp.data_[13];
	data_[ 8] = tmp.data_[ 2];
	data_[ 9] = tmp.data_[ 6];
	data_[11] = tmp.data_[14];
	data_[12] = tmp.data_[ 3];
	data_[13] = tmp.data_[ 7];
	data_[14] = tmp.data_[11];
}

bool
Matrix::is_invertible() const
{
	return 0 != determinant();
}

/* static */ Matrix const& 
Matrix::null()
{
	static Matrix null_(null_array16);
	return null_;
}


/* static */ Matrix const& 
Matrix::identity()
{
	static Matrix identity_(ident_array16);
	return identity_;
}

// external functions

Matrix
operator*(Matrix const& lhs, Matrix const& rhs)
{
	return Matrix(lhs) *= rhs;
}

Matrix
operator*(Matrix const& lhs, double rhs)
{
	return Matrix(lhs) *= rhs;
}

Matrix
operator*(double lhs, Matrix const& rhs)
{
	return rhs * lhs;
}

Matrix
operator+(Matrix const& lhs, Matrix const& rhs)
{
	return Matrix(lhs) += rhs;
}

Matrix
operator-(Matrix const& lhs, Matrix const& rhs)
{
	return Matrix(lhs) -= rhs;
}

bool
operator==(Matrix const& lhs, Matrix const& rhs)
{
	return bool(
		lhs[ 0] == rhs[ 0] &&
		lhs[ 1] == rhs[ 1] &&
		lhs[ 2] == rhs[ 2] &&
		lhs[ 3] == rhs[ 3] &&
		lhs[ 4] == rhs[ 4] &&
		lhs[ 5] == rhs[ 5] &&
		lhs[ 6] == rhs[ 6] &&
		lhs[ 7] == rhs[ 7] &&
		lhs[ 8] == rhs[ 8] &&
		lhs[ 9] == rhs[ 9] &&
		lhs[10] == rhs[10] &&
		lhs[11] == rhs[11] &&
		lhs[12] == rhs[12] &&
		lhs[13] == rhs[13] &&
		lhs[14] == rhs[14] &&
		lhs[15] == rhs[15] );
}

bool
operator!=(Matrix const& lhs, Matrix const& rhs)
{
	return !(lhs == rhs);
}

double
determinant(Matrix const& a)
{
	return a.determinant();
}

Matrix
inverse(Matrix const& a)
{
	Matrix tmp(a);
	tmp.invert();
	return tmp;
}

Matrix
transpose(Matrix const& a)
{
	Matrix tmp(a);
	tmp.transpose();
	return tmp;
}

bool
is_invertible(Matrix const& a)
{
	return a.is_invertible();
}

std::ostream&
operator<<(std::ostream& os, Matrix const& a)
{
	std::ostream::sentry const cerberus(os);

	if (cerberus) {
		os << std::fixed << std::setprecision(3)
			<< '[' << a[0]  << ',' << a[1]  << ',' << a[2]  << ',' << a[3]  << ',' << std::endl
			<< ' ' << a[4]  << ',' << a[5]  << ',' << a[6]  << ',' << a[7]  << ',' << std::endl
			<< ' ' << a[8]  << ',' << a[9]  << ',' << a[10] << ',' << a[11] << ',' << std::endl
			<< ' ' << a[12] << ',' << a[13] << ',' << a[14] << ',' << a[15] << ']';
  }

  return os;
}

Matrix
make_translation ( double t1, double t2, double t3 )
{
	double const values[16] = {
		1.0, 0.0, 0.0, t1 ,
		0.0, 1.0, 0.0, t2 ,
		0.0, 0.0, 1.0, t3 ,
		0.0, 0.0, 0.0, 1.0
	};
	return values;
}

Matrix
make_translation ( Vector const& v)
{
	double const values[16] = {
		1.0, 0.0, 0.0, v[0],
		0.0, 1.0, 0.0, v[1],
		0.0, 0.0, 1.0, v[2],
		0.0, 0.0, 0.0, 1.0
	};
	return values;
}

Matrix
make_scale ( double t1, double t2, double t3 )
{
	double const values[16] = {
		t1 , 0.0, 0.0, 0.0,
		0.0, t2 , 0.0, 0.0,
		0.0, 0.0, t3 , 0.0,
		0.0, 0.0, 0.0, 1.0
	};
	return values;
}

Matrix
make_scale ( Vector const& v)
{
	double const values[16] = {
		v[0], 0.0 , 0.0 , 0.0,
		0.0 , v[1], 0.0 , 0.0,
		0.0 , 0.0 , v[2], 0.0,
		0.0 , 0.0 , 0.0 , 1.0
	};
	return values;
}

Matrix make_rotation ( Vector const& v, double a )
{
	a = deg_to_rad(a);
	Vector u   = unify(v);
	double c   = cos(a);
	double s   = sin(a);
	double omc = 1-c;
	double ux  = u[0];
	double uy  = u[1];
	double uz  = u[2];
	double ux2 = ux*ux;
	double uy2 = uy*uy;
	double uz2 = uz*uz;
	double uxy = ux*uy;
	double uxz = ux*uz;
	double uyz = uy*uz;
	double uxs = ux*s;
	double uys = uy*s;
	double uzs = uz*s;
	
	double const values[16] = {
		ux2+(1-ux2)*c, uxy*omc-uzs,   uxz*omc+uys,   0.0,
		uxy*omc+uzs,   uy2+(1-uy2)*c, uyz*omc-uxs,   0.0,
		uxz*omc-uys,   uyz*omc+uxs,   uz2+(1-uz2)*c, 0.0,
		0.0,           0.0,           0.0,           1.0
	};
	
	return values;
}

Point
operator* ( Matrix const& lhs, Point const& rhs)
{
	Point tmp;
	tmp[0] = lhs[0] *rhs[0] + lhs[1] *rhs[1] + lhs[2] *rhs[2] + lhs[3] ;
	tmp[1] = lhs[4] *rhs[0] + lhs[5] *rhs[1] + lhs[6] *rhs[2] + lhs[7] ;
	tmp[2] = lhs[8] *rhs[0] + lhs[9] *rhs[1] + lhs[10]*rhs[2] + lhs[11];
	return tmp;
}

Vector
operator* ( Matrix const& lhs, Vector const& rhs)
{
	Vector tmp;
	tmp[0] = lhs[0] *rhs[0] + lhs[1] *rhs[1] + lhs[2] *rhs[2];
	tmp[1] = lhs[4] *rhs[0] + lhs[5] *rhs[1] + lhs[6] *rhs[2];
	tmp[2] = lhs[8] *rhs[0] + lhs[9] *rhs[1] + lhs[10]*rhs[2];
	return tmp;
}


