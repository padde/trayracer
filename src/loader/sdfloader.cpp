//system headers
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctime>

//project headers
#include "sdfloader.hpp"
#include "scene.hpp"
#include "shape.hpp"
#include "sphere.hpp"
#include "triangle.hpp"
#include "compositeshape.hpp"
#include "box.hpp"
#include "material.hpp"
#include "phong.hpp"
#include "reflective.hpp"
#include "transparent.hpp"
#include "light.hpp"
#include "ambientlight.hpp"
#include "pointlight.hpp"

////////////////////////////////////////////////////////////////////////////////
//  path to the sdf files...
////////////////////////////////////////////////////////////////////////////////
#define SDFPATH "./sdf/"

using namespace std;

////////////////////////////////////////////////////////////////////////////////
//  c'tor
////////////////////////////////////////////////////////////////////////////////
sdfloader::sdfloader()
	: world(new Scene)
{}





////////////////////////////////////////////////////////////////////////////////
//	getdir: directory listing for choosing of sdf-file
////////////////////////////////////////////////////////////////////////////////
int
sdfloader::getdir (string dir , vector<string>& files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
//	load: main routine that initiates the whole file loader
////////////////////////////////////////////////////////////////////////////////
bool
sdfloader::load ()
{
	vector<string> files = vector<string>();
	vector<string> sdf_files = vector<string>();
	
	
	// get files in the sdf folder
	getdir(SDFPATH,files);
	
	// weed out non sdf files
	for (unsigned int i = 0;i < files.size();i++) {
	  	if (string::npos != files[i].find ( ".sdf", 0 ) )
	  	{
			sdf_files.push_back( files[i] );
	    	}
	}
	
	// if several sdf files are present, start the file chooser
	if (sdf_files.size() > 1 )
	{
		cout << endl << "Please choose the sdf file to load:" << endl;
		for (unsigned int i = 0;i < sdf_files.size();++i){
			cout << '['<<i<<"] " << sdf_files[i] << endl;
		}
		
		cout << endl << "Enter the number of the correct file: ";
		
		unsigned number;
		cin >> number;
		
		load (sdf_files[number]);
		
	}
	else if ( sdf_files.size() == 1)
	{
		load( sdf_files[0] );
	}
	else 
		cerr << endl << "No sdf files found to load!" << endl << "Please check the "<< SDFPATH << " Folder";
	return 0;
}



////////////////////////////////////////////////////////////////////////////////
//	fileload: converts file on drive in 2d input vector
////////////////////////////////////////////////////////////////////////////////
vector < vector<string> >
sdfloader::fileload (const char* path )
{
	ifstream ifs ( path, ifstream::in );
	unsigned int zeilenzahl = 0;
	vector < vector<string> > input;
	
  	while( ifs.good() )
  	{
  		// cleanup input till first argument statement
  		unsigned int dirty = 1;
  		while ( dirty )
  		{
  			char firstchar = ifs.peek();
  						
  			if ( firstchar == '#' )
  			{
				ifs.ignore( 512, '\n');
 			}  				
  			else if ( firstchar == '\n' )
  			{
  				ifs.ignore(512, '\n');
  			}
  			else if ( firstchar == '\t' )
  			{
  				ifs.ignore(1, '\t');
  			}
  			else if ( firstchar == ' ' )
  			{
  				ifs.ignore(1, ' ');
 			}
  			else
  			{
  				dirty = 0;
  			}
  		}
  		
  		// resize input vector to accomodate enough lines
  		++zeilenzahl;
  		input.resize(zeilenzahl);
  		
  		// import a single line from the input filestream
		char cline[512];
		ifs.getline(cline,512);
		
		// convert it into a stringstream for formatted extraction of words
		stringstream line (stringstream::in | stringstream::out);
		// fill stringstream from char array
		line << cline;
		string word;
		while ( line.good() )
		{
			
			line >> word;
			input[zeilenzahl - 1].push_back( word );
		}	 		
  	}
  	ifs.close();
  	
  	return input;
}


bool
sdfloader::load (string& filename)
{
	cout << endl << "loading " << SDFPATH << filename << " ..." << endl;

	const string temppath = SDFPATH + filename;
  	const char* path = temppath.c_str();
  	
  	// load pure input from file
  	vector< vector <string> > input = fileload( path );
  	
  	
  	
	// parse input
	parse( input );

	
	return true;
}


void
sdfloader::parse ( vector< vector<string> >& input)
{
	for (unsigned int i = 0; i < input.size()-1; ++i)
	{
	
		if( phong( input[i]) )
		{
			load_phong ( input[i] );
		}
		else if( reflective( input[i]) )
		{
			load_reflective( input[i] );
		}		
		else if( transparent( input[i] ) )
		{
			load_transparent( input[i] );
		}				
		else if( box( input[i] ) )
		{
			load_box( input[i] );
		}
		else if( sphere( input[i] ) )
		{
			load_sphere( input[i] );
		}
		else if( triangle( input[i] ) )
		{
			load_triangle( input[i] );
		}
		else if( composite( input[i] ) )
		{
			load_composite( input[i] );
		}
		else if( alight( input[i]) )
		{
			load_alight( input[i] );
		}
		else if( dlight( input[i] ) )
		{
			load_dlight( input[i] );
		}
		else if( camera( input[i] ) )
		{
			load_camera( input[i] );
		}
		else if( transform( input[i] ) )
		{
			apply_transformation( input[i] );
			
		}
		else if( background ( input[i] ) )
		{
			set_bgcolor (input[i]);
		}
		else if( render( input[i] ) )
		{
			do_render( input[i] );
			
		}
		else
		{
			cerr << "Error: Cannot parse input: \n\t";
			for (unsigned int j = 0; j < input[i].size(); ++j)
			{
				cerr << input[i][j] << " ";
			}
			cerr << endl;
		}
	}	
}





void
sdfloader::load_phong ( vector<string>& word )
{
	cout << "Adding material \"" << word[3] << "\" of type phong ...\n";
	
	// check for input sanity
	if (word.size() != 14)
	{ 
		cerr << "\tInvalid number of arguments!\n" ;
	}		
	else
	{
		
	// conversion of strings to floats :
	float kaR = atof ( word[4].c_str() );
	float kaG = atof ( word[5].c_str() );
	float kaB = atof ( word[6].c_str() );
	
	float kdR = atof ( word[7].c_str() );
	float kdG = atof ( word[8].c_str() );
	float kdB = atof ( word[9].c_str() );
	
	float ksR = atof ( word[10].c_str() );
	float ksG = atof ( word[11].c_str() );
	float ksB = atof ( word[12].c_str() );
	
	float m = atof ( word[13].c_str() );


	// integrate into world
	world->push_material( new Phong(word[3], rgb( kaR, kaG, kaB ), rgb( kdR, kdG, kdB ), rgb( ksR, ksG, ksB ), m) );
	}
}

void
sdfloader::load_reflective ( vector<string>& word )
{
	cout << "Adding material \"" << word[3] << "\" of type reflective ...\n";
			
	// check for input sanity
	if (word.size() != 17)
	{
		cerr << "\tInvalid number of arguments!\n" ;
	}
	else
	{	
	// conversion of strings to floats :
	float kaR = atof ( word[4].c_str() );
	float kaG = atof ( word[5].c_str() );
	float kaB = atof ( word[6].c_str() );
	
	float kdR = atof ( word[7].c_str() );
	float kdG = atof ( word[8].c_str() );
	float kdB = atof ( word[9].c_str() );
	
	float ksR = atof ( word[10].c_str() );
	float ksG = atof ( word[11].c_str() );
	float ksB = atof ( word[12].c_str() );
	
	float krR = atof ( word[14].c_str() );
	float krG = atof ( word[15].c_str() );
	float krB = atof ( word[16].c_str() );
	
	float m = atof ( word[13].c_str() );
	
	// integrate into world
	world->push_material( new Reflective(word[3], rgb( kaR, kaG, kaB ), rgb( kdR, kdG, kdB ), rgb( ksR, ksG, ksB ), m, rgb( krR, krG, krB )) );
	}
}

void
sdfloader::load_transparent ( vector<string>& word )
{
	cout << "Adding material \"" << word[3] << "\" of type transparent ...\n";
			
	// check for input sanity
	if (word.size() != 19)
	{
		cerr << "\tInvalid number of arguments!\n" ;
	}		
	else
	{
	// conversion of strings to floats :
	float kaR = atof ( word[4].c_str() );
	float kaG = atof ( word[5].c_str() );
	float kaB = atof ( word[6].c_str() );
	
	float kdR = atof ( word[7].c_str() );
	float kdG = atof ( word[8].c_str() );
	float kdB = atof ( word[9].c_str() );
	
	float ksR = atof ( word[10].c_str() );
	float ksG = atof ( word[11].c_str() );
	float ksB = atof ( word[12].c_str() );
	
	float exp = atof ( word[13].c_str() );
	
	float krR = atof ( word[14].c_str() );
	float krG = atof ( word[15].c_str() );
	float krB = atof ( word[16].c_str() );
	
	float kt  = atof ( word[17].c_str() );
	float ior = atof ( word[18].c_str() );
	
	// integrate into world
	
	world->push_material( new Transparent(word[3], rgb( kaR, kaG, kaB ), rgb( kdR, kdG, kdB ), rgb( ksR, ksG, ksB ), exp, rgb( krR, krG, krB ), kt, ior ) );
	}
}				

void
sdfloader::load_box ( vector<string>& word )
{
	cout << "Adding box \"" << word[3] << "\" ...\n";
	
	// check for input sanity
	if (word.size() != 11)
	{
		cerr << "\tInvalid number of arguments!\n" ;
	}
	else
	{
	// conversion of strings to correct types:
	float lX = atof ( word[4].c_str() );
	float lY = atof ( word[5].c_str() );
	float lZ = atof ( word[6].c_str() );
	
	float hX = atof ( word[7].c_str() );
	float hY = atof ( word[8].c_str() );
	float hZ = atof ( word[9].c_str() );

	
	Material* m = world->get_material( word[10] );

	// integrate into world
	world->push_shape( new Box( word[3], Point( lX, lY, lZ), Point( hX, hY, hZ ), m ) ); 
	}
}

void
sdfloader::load_sphere ( vector<string>& word )
{
	cout << "Adding sphere \"" << word[3] << "\" ...\n";
	
	// check for input sanity
	if (word.size() != 9)
	{
		cerr << "\tInvalid number of arguments!\n" ;
	}
	else
	{
	// conversion of strings to correct type :
	float cX = atof ( word[4].c_str() );
	float cY = atof ( word[5].c_str() );
	float cZ = atof ( word[6].c_str() );
	
	float r = atof ( word[7].c_str() );
	
	
	Material* mat = world->get_material( word[8] );

	
	// integrate into world
	world->push_shape( new Sphere( word[3], Point( cX, cY, cZ), r, mat ) );
	} 
}

void
sdfloader::load_triangle ( vector<string>& word )
{
	cout << "Adding sphere \"" << word[3] << "\" ...\n";
	
	// check for input sanity
	if (word.size() != 14)
	{
		cerr << "\tInvalid number of arguments!\n" ;
	}
	else
	{
	// conversion of strings to correct type :
	float aX = atof ( word[4].c_str() );
	float aY = atof ( word[5].c_str() );
	float aZ = atof ( word[6].c_str() );
	
	float bX = atof ( word[7].c_str() );
	float bY = atof ( word[8].c_str() );
	float bZ = atof ( word[9].c_str() );
	
	float cX = atof ( word[10].c_str() );
	float cY = atof ( word[11].c_str() );
	float cZ = atof ( word[12].c_str() );
	
	Material* mat = world->get_material( word[13] );

	
	// integrate into world
	world->push_shape( new Triangle( word[3], Point( aX, aY, aZ), Point( bX, bY, bZ), Point( cX, cY, cZ), mat ) );
	} 
}

void
sdfloader::load_composite ( vector<string>& word )
{
	cout << "Adding composite \"" << word[3] << "\" ...\n";
	
	// create composite shape to fill
	CompositeShape* temp = new CompositeShape( word[3] );
	
	// fill it with the remaining arguments
	for (unsigned int j = 4; j < word.size(); ++j)
	{	
		temp->push(world->get_and_remove_shape( word[j] ));
	}

	// and add it to the world
	world->push_shape( temp );
}

void
sdfloader::load_alight ( vector<string>& word )
{
	cout << "Adding ambient light \"" << word[3] << "\" ...\n";
	
	// check for input sanity
	if (word.size() != 7)
	{
		cerr << "\tInvalid number of arguments!\n" ;
	}
	else
	{
	// conversion of strings to correct type :
	float r = atof ( word[4].c_str() );
	float g = atof ( word[5].c_str() );
	float b = atof ( word[6].c_str() );
	
	// integrate into world
	world->set_ambient ( new AmbientLight ( word[3], rgb ( r, g, b)));
	}
}

void
sdfloader::load_dlight ( vector<string>& word )
{			
	cout << "Adding diffuse light \"" << word[3] << "\" ...\n";
	
	// check for input sanity
	if (word.size() != 10)
	{
		cerr << "\tInvalid number of arguments!\n" ;
	}
	else
	{
	// conversion of strings to correct type :
	
	float x = atof ( word[4].c_str() );
	float y = atof ( word[5].c_str() );	
	float z = atof ( word[6].c_str() );	
			
	float r = atof ( word[7].c_str() );
	float g = atof ( word[8].c_str() );
	float b = atof ( word[9].c_str() );
	
	// integrate into world
	world->push_light ( new PointLight ( word[3], Point( x, y, z), rgb ( r, g, b) ));
	}
}

void
sdfloader::load_camera (vector<string>& word)
{
	cout << "Adding camera \"" << word[2] << "\" ...\n";
	
	// check for input sanity
	if (word.size() != 6)
	{
		cerr << "\tInvalid number of arguments!\n" ;
	}
	else
	{
	// conversion of strings to correct type :
	
	float angle = atof ( word[3].c_str() );
	float x_res = atof ( word[4].c_str() );	
	float y_res = atof ( word[5].c_str() );	
			
	// integrate into world
	world->push_camera ( new Camera ( word[2], x_res, y_res, angle ));
	}
}

void
sdfloader::apply_transformation( vector<string>& word )
{
	cout << "Applying transformation \"" << word[2] << "\" to shape \"" << word[1] << "\" ...\n";
	
	Shape* move_me = world->get_shape( word[1] );
		
	if (word[2] == "scale")
	{
		float x = atof ( word[3].c_str() );
		float y = atof ( word[4].c_str() );	
		float z = atof ( word[5].c_str() );	
		move_me->transform(make_scale(x,y,z));
	}
	else if (word[2] == "rotate")
	{
		float x = atof ( word[3].c_str() );	
		float y = atof ( word[4].c_str() );	
		float z = atof ( word[5].c_str() );	
		float angle = atof ( word[6].c_str() );
		move_me->transform(make_rotation(Vector(x,y,z), angle));
	}
	else if (word[2] == "translate")
	{		
		float x = atof ( word[3].c_str() );
		float y = atof ( word[4].c_str() );	
		float z = atof ( word[5].c_str() );	
		move_me->transform(make_translation(x,y,z));
	}
	else
	{
		cerr << "\tInvalid arguments!\n" ;
	}
}

void
sdfloader::set_bgcolor (vector< string >& word)
{
		float r = atof ( word[1].c_str() );
		float g = atof ( word[2].c_str() );	
		float b = atof ( word[3].c_str() );	
		world->set_bgcolor ( rgb ( r, g, b) );
}


void
sdfloader::do_render(vector<string>& word) const
{
	// preparations for filename
	time_t      t = time(NULL);
	struct tm* lt = localtime(&t);
	char time_str [80];
	strftime(time_str,80,"%Y-%m-%d__%H-%M-%S",lt);
	const string filename = word[2] + "__" +  string(time_str) + ".png";
	
	cout << "\n Now rendering scene as seen through \"" << word[1] << "\" and outputting to file \"" << filename << "\" !\n\n";
	
	if (word.size() != 3)			
	{
		cerr << "\tInvalid number of arguments!\n" ;
	}
	else
	{
	Camera* cam = world->get_camera( word[1] );
	cam->render( filename );
	}
}

bool
sdfloader::phong( vector < string>& word) const
{
	if ( word[0] == "define" && word[1] == "material" && word[2] == "phong")
		return true;
	else
		return false;
}


bool
sdfloader::reflective( vector < string>& word) const
{
	if ( word[0] == "define" && word[1] == "material" && word[2] == "reflective")
		return true;
	else
		return false;
}


bool
sdfloader::transparent( vector < string>& word) const
{
	if ( word[0] == "define" && word[1] == "material" && word[2] == "transparent")
		return true;
	else
		return false;
}


bool
sdfloader::box( vector < string>& word) const
{
	if ( word[0] == "define" && word[1] == "shape" && word[2] == "box" )
		return true;
	else
		return false;
}

bool
sdfloader::sphere( vector < string>& word) const
{
	if ( word[0] == "define" && word[1] == "shape" && word[2] == "sphere" )
		return true;
	else
		return false;
}

bool
sdfloader::triangle( vector < string>& word) const
{
	if ( word[0] == "define" && word[1] == "shape" && word[2] == "triangle" )
		return true;
	else
		return false;
}

bool
sdfloader::composite( vector < string>& word) const
{
	if ( word[0] == "define" && word[1] == "shape" && word[2] == "composite" )
		return true;
	else
		return false;
}

bool
sdfloader::alight( vector < string>& word) const
{
	if ( word[0] == "define" && word[1] == "light" && word[2] == "ambient" )
		return true;
	else
		return false;
}

bool
sdfloader::dlight( vector < string>& word) const
{
	if ( word[0] == "define" && word[1] == "light" && word[2] == "diffuse" )
		return true;
	else
		return false;
}

bool
sdfloader::camera( vector < string>& word) const
{
	if ( word[0] == "define" && word[1] == "camera" )
		return true;
	else
		return false;
}

bool
sdfloader::render( vector < string>& word) const
{
	if ( word[0] == "render" )
		return true;
	else
		return false;
}

bool
sdfloader::transform( vector < string>& word) const
{
	if ( word[0] == "transform" )
		return true;
	else
		return false;
}

bool
sdfloader::background( vector< string >& word) const
{
	if ( word[0] == "setbgcolor" )
		return true;
	else
		return false;
}
