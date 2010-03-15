#ifndef BUW_SDFLOADER
#define BUW_SDFLOADER


// project header
#include <scene.hpp>

using namespace std;

//! @author Frank Urbainsky
//! @date January 2010
//! @brief ... sdf file loader and parser
//
class sdfloader
{
	public:
	//! @brief constructor
	sdfloader();
	
	///////////////////////////////////////////////////////////
	//! @brief	interface for sdfloader access
	//////////////////////////////////////////////////////////
	
	//! @brief for access to ./sdf/
	bool	load	();
	//! @brief for access to specific sdf file
	//! @param filename filename of the sdf file to load
	bool	load	(string& filename);
	
	private: //member function
	
	///////////////////////////////////////////////////////////	
	//! @brief directory listing for choosing of sdf-file
	int			 getdir	(string dir ,vector<string>& files);
	
	///////////////////////////////////////////////////////////	
	//! @brief converts file on drive in 2d input vector
	vector< vector<string> > fileload (const char* path);
	
	///////////////////////////////////////////////////////////	
	//! @brief parses the input vector
	void			 parse ( vector < vector<string> >& input);
	
	///////////////////////////////////////////////////////////
	//! @brief helper functions for specific things to parse
	void			load_phong( vector<string>& word );
	void			load_reflective ( vector<string>& word );
	void			load_transparent ( vector<string>& word );
	void			load_box ( vector<string>& word );
	void			load_sphere ( vector<string>& word );
	void			load_composite ( vector<string>& word );
	void			load_alight ( vector<string>& word );
	void			load_dlight ( vector<string>& word );
	void			load_camera (vector<string>& word);
	void			apply_transformation( vector<string>& word );
	void			do_render(vector<string>& word);
	
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


#endif //BUW_SDFLOADER
