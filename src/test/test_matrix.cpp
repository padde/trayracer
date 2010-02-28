// project header
#include <point.hpp>
#include <vector.hpp>
#include <matrix.hpp>
#include <UnitTest++.h>

// system header
#include <cmath>



TEST ( matrix__should_make_translation_with_arguments )
{
	Matrix m = make_translation(1,2,3);
	
	double const values[16] = {
		1.0, 0.0, 0.0, 1.0,
		0.0, 1.0, 0.0, 2.0,
		0.0, 0.0, 1.0, 3.0,
		0.0, 0.0, 0.0, 1.0
	};
	Matrix expected(values);
	
	CHECK_EQUAL(expected, m);
}

TEST ( matrix__should_make_translation_with_Vector )
{
	Vector v(4,5,6);
	Matrix m = make_translation(v);
	
	double const values[16] = {
		1.0, 0.0, 0.0, 4.0,
		0.0, 1.0, 0.0, 5.0,
		0.0, 0.0, 1.0, 6.0,
		0.0, 0.0, 0.0, 1.0
	};
	Matrix expected(values);
	
	CHECK_EQUAL(expected, m);
}

TEST ( matrix__should_make_scale_with_arguments )
{
	Matrix m = make_scale(1,2,3);
	
	double const values[16] = {
		1.0, 0.0, 0.0, 0.0,
		0.0, 2.0, 0.0, 0.0,
		0.0, 0.0, 3.0, 0.0,
		0.0, 0.0, 0.0, 1.0
	};
	Matrix expected(values);
	
	CHECK_EQUAL(expected, m);
}

TEST ( matrix__should_make_scale_with_Vector )
{
	Vector v(4,5,6);
	Matrix m = make_scale(v);
	
	double const values[16] = {
		4.0, 0.0, 0.0, 0.0,
		0.0, 5.0, 0.0, 0.0,
		0.0, 0.0, 6.0, 0.0,
		0.0, 0.0, 0.0, 1.0
	};
	Matrix expected(values);
	
	CHECK_EQUAL(expected, m);
}

/*
TEST ( matrix__should_make_rotation_x )
{
	double a = 45 * M_PI / 180;
	Matrix m = make_rotation_x(a);
	
	double const values[16] = {
		1.0, 0.0   ,  0.0   , 0.0,
		0.0, cos(a), -sin(a), 0.0,
		0.0, sin(a),  cos(a), 0.0,
		0.0, 0.0   ,  0.0   , 1.0
	};
	Matrix expected(values);
	
	CHECK_EQUAL(expected, m);
}

TEST ( matrix__should_make_rotation_y )
{
	double a = 45 * M_PI / 180;
	Matrix m = make_rotation_y(a);
	
	double const values[16] = {
		 cos(a), 0.0, sin(a), 0.0,
		 0.0   , 1.0, 0.0   , 0.0,
		-sin(a), 0.0, cos(a), 0.0,
		 0.0   , 0.0, 0.0   , 1.0
	};
	Matrix expected(values);
	
	CHECK_EQUAL(expected, m);
}

TEST ( matrix__should_make_rotation_z )
{
	double a = 45 * M_PI / 180;
	Matrix m = make_rotation_z(a);
	
	double const values[16] = {
		cos(a), -sin(a), 0.0, 0.0,
		sin(a),  cos(a), 0.0, 0.0,
		0.0   ,  0.0   , 1.0, 0.0,
		0.0   ,  0.0   , 0.0, 1.0
	};
	Matrix expected(values);
	
	CHECK_EQUAL(expected, m);
}*/

TEST ( matrix__should_multiplicate_scale_with_Vector )
{
	Matrix m = make_scale(1,2,3);
	Vector v(2,2,2);
	Vector result = m*v;
	CHECK_EQUAL(2, result[0]);
	CHECK_EQUAL(4, result[1]);
	CHECK_EQUAL(6, result[2]);
}

TEST ( matrix__should_multiplicate_translation_with_Vector )
{
	Matrix m = make_translation(1,2,3);
	Vector v(2,2,2);
	Vector result = m*v;
	CHECK_EQUAL(2, result[0]);
	CHECK_EQUAL(2, result[1]);
	CHECK_EQUAL(2, result[2]);
}

TEST ( matrix__should_multiplicate_scale_with_Point )
{
	Matrix m = make_translation(1,2,3);
	Point p(2,2,2);
	Point result = m*p;
	CHECK_EQUAL(3, result[0]);
	CHECK_EQUAL(4, result[1]);
	CHECK_EQUAL(5, result[2]);
}



