#ifndef SDFLOADER
#define SDFLOADER


// project header
#include <scene.hpp>

using namespace std;

class sdfloader
{
	public:
	
	sdfloader();
	
	///////////////////////////////////////////////////////////
	//	interface for sdfloader access
	///////////////////////////////////////////////////////////
	bool	load	();		// for access to ./sdf/
	bool	load	(string&);	// for access to specific sdf file
	
	private: //member function
	
	///////////////////////////////////////////////////////////	
	//	directory listing for choosing of sdf-file
	int			 getdir	(string dir ,vector<string>& files);
	
	///////////////////////////////////////////////////////////	
	//	converts file on drive in 2d input vector
	vector< vector<string> > fileload (const char* path);
	
	///////////////////////////////////////////////////////////	
	//	parses the input vector
	void			 parse ( vector < vector<string> >& input);
	
	///////////////////////////////////////////////////////////
	//	helper functions for parse
	bool			phong( vector < string>& input);
	bool			reflective( vector < string>& input);
	bool			transparent( vector < string>& input);
	bool			box( vector<string>& input);
	bool			sphere( vector<string>& input);
	bool			composite( vector<string>& input);
	bool			alight( vector<string>& input);
	bool			dlight( vector<string>& input);
	bool			camera( vector<string>& input);
	bool			render( vector<string>& input);
	bool			transform( vector<string>& input);
	
	///////////////////////////////////////////////////////////
	public: //member variables
	Scene*	world;
	
};


#endif //SDFLOADER
