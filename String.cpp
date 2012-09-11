#include "String.hpp"

#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
using namespace std;

/*
once again, this won't work in .cpp, so move back to .h
void xml::String::display(ostream & out) const
{
  out<<_theString;
}

once again, this won't work in .cpp, so move back to .h
std::string xml::String::showIt()
{
  return _theString;
}

once again, this won't work in .cpp, so move back to .h
int xml::String::getSize()
{
  return _size;
}

once again, this won't work in .cpp, so move back to .h
std::string xml::String::getString()
{
  return _theString;
}




// ABSOLUTELY NO DEFINITIONS ARE ALLOWED IN .CPP; 
// EVERYTHING FAILS WHEN DEFINED IN .CPP.

// Comparison with std::string.
bool operator==(const std::string & stdString, const xml::String & StringString)
{  return stdString == StringString.getString(); }

bool operator==(const xml::String & StringString, const std::string & stdString)
{  return stdString == StringString._theString; }

bool operator!=(const std::string & stdString, const xml::String & StringString)
{  return stdString != StringString._theString; }

bool operator!=(const xml::String & StringString, const std::string & stdString)
{  return stdString != StringString._theString; }


// Comparison with C string.
bool operator==(const char * s, const xml::String & StringString)
{  return StringString._theString.compare(s) == 0; }

bool operator==(const xml::String & StringString, const char * s)
{  return StringString._theString.compare(s) == 0; }

bool operator!=(const char * s, const xml::String & StringString)
{  return StringString._theString.compare(s) != 0; }

bool operator!=(const xml::String & StringString, const char * s)
{  return StringString._theString.compare(s) != 0; }

// Output operator
std::ostream &operator<<(std::ostream & out, const xml::String & s)
{
  s.display(out);
  return out;
}
	

	
*/



#if 0

WHAT IS THE POINT OF HAVING THESE PIDDLY LITTLE FUNCTIONS
IF NEARLY EVERYTHING HAS TO BE DEFINED IN String.hpp
BECAUSE ITS PRIVATE, OR A CONSTRUCTOR OF SOME KIND???

AND WHATS TO PREVENT OTHER CLASSES FROM ADDING THEIR OWN
MEMBER FUNCTIONS TO THE CLASS BY JUST INCLUDING String.hpp???

IN OTHER WORDS, COULDNT SOME OTHER CLASS, SAY, malitious.cpp
include String.hpp and have a function that `infects` privt 
data members?  Or something malicious like that?

In Java, I would make an abstract clss, or an interface with
member methods` signatures, then REDECLARE the clss in an 
implementation file. 

????????????????????????????????????????????????????????
????????????????????????????????????????????????????????
WHY WOULD I NEED A CLASS CALLED `String.cpp` AT ALL?????
????????????????????????????????????????????????????????
????????????????????????????????????????????????????????

part of the answer is down below: the overloaded operators.


#endif


/* don't need this, and can't make it work anyhow.
        String( const char * s = 0 )
				{
						_size = strlen(s);
						_theString = new char[ _size+1 ];
						strcpy( _theString, s );
        }
*/

//};




#if 0

// Comparison with std::string.
bool operator==(const String &str1, const String &str2)
{
	// lifted straight out of C++ Primer, 3rd ed., pg 744.
	if ( str1.getSize() != str2.getSize() ) return false;
	return strcmp( str1.showIt(), str2.showIt() ) ? false : true;
                     //I'll have to figure out my naming conventions and methods
}

String.cpp: In function 'bool operator==(const String&, const String&)':
String.cpp:95: error: passing 'const String' as 'this' argument of 'int String::getSize()' discards qualifiers
String.cpp:95: error: passing 'const String' as 'this' argument of 'int String::getSize()' discards qualifiers
String.cpp:96: error: passing 'const String' as 'this' argument of 'std::string String::showIt()' discards qualifiers
String.cpp:96: error: passing 'const String' as 'this' argument of 'std::string String::showIt()' discards qualifiers
String.cpp:96: error: cannot convert 'std::string' to 'const char*' for argument '1' to 'int strcmp(const char*, const char*)'

#endif

/*
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

 */

