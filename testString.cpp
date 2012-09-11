#include "String.hpp"

#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
using namespace std;

//class String {
//    public:
        // Copy constructor.
        String::String(const String &s)
        {
						_size = s._size;
						_theString = s._theString;
        }
        // why the heck can this access another obj.'s 
        // private data members????
          
        
        static String String::StringConstructor( std::string &s )
        {
          return String(s);
        }

        // Conversion to std::string.
  /*      operator std::string() const{
          return theString;
        }
*/
        // Assignment.
        //String &operator=(const String &);

        std::string String::showIt()
        {
          return _theString;
        }


        int String::getSize()
        {
          return _size;
        }

        std::string String::getString()
        {
          return _theString;
        }

    private:
				std::string String::_theString;
				int         String::_size;

/* don't need this, and can't make it work anyhow.
        String( const char * s = 0 )
				{
						_size = strlen(s);
						_theString = new char[ _size+1 ];
						strcpy( _theString, s );
        }
*/
        String::String( std::string &s )
				{
						_size = s.length();
						_theString = s.c_str();
        }
//};





/*
// Comparison with std::string.
bool operator==(const String &str1, const String &str2)
{
	// lifted straight out of C++ Primer, 3rd ed., pg 744.
	if ( str1.size() != str2.size() ) return false;
	return strcmp( str1.c_str(), str2.c_str() ) ? false : true;
                     //I'll have to figure out my naming conventions and methods
}


bool operator==(const std::string &, const String &);
bool operator==(const String &, const std::string &)

//inline? put into .hpp, eh?
bool operator==(const String &str, const char *s)
{
	return strcmp( str.c_str(), s ) ? false : true;
}


bool operator!=(const std::string &, const String &);
bool operator!=(const String &, const std::string &);

// Comparison with C string.
bool operator==(const char *, const String &);
bool operator==(const String &, const char *);

bool operator!=(const char *, const String &);
bool operator!=(const String &, const char *);
*/


/*
// Output operator
std::ostream &operator<<(std::ostream &, const String &);

//  The above is the string class that you should provide. 

I DON'T GET THIS:
    Note that there is no need for a public constructor, 
    though you would need a private (or undocumented one). 

I DON'T GET THIS:
    Also, note that this string class will allow you to 
    use optimized memory management.

I DON'T GET THIS:
    You can assume that any String objects must be destructed 
    before the Parser from where they came is destructed.


int main(int argc, char *argv[])
{
	std::string str = "Hello, world\n";

  String s = String::StringConstructor(str);

  cout<< s.showIt() << endl;

  cout<<"copying a 'String' object"<<endl;
  String z = String(s);
  cout<< z.showIt() << endl;





	
	return 0;



}

 */