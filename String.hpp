

#include <string>
#include <cstring>
#include <iostream>
#include <ostream>
#ifndef STRING_HPP
#define STRING_HPP

namespace xml {

class String {

		friend class Element;
		friend class Text;

    public:

        static String StringConstructor( std::string &s )
        {
          return String(s);
        }

        // Copy constructor.
        String(const String &s)
        {
						_size = s._size;
						_theString = s._theString;
        }

       ~String() { }//delete _theString; } // delete _theString; }
		
								// was getting huge linker errors, but "inlining" keeps linker quiet.
        inline void display(std::ostream & out) const
        {
          out << _theString;
        }

        // Conversion String object to 'normal' std::string.
        operator std::string() const
        {
          return _theString;
        }

		
				//once again, this won't work in .cpp, so move back to .h
				const std::string showIt() const
					// there is no "xml::" here!!  wtf?!
				{
					return _theString;
				}

				//once again, this won't work in .cpp, so move back to .h
				const int getSize() const
				{
					return _size;
				}

				//once again, this won't work in .cpp, so move back to .h
				const std::string getString() const
				{
					return _theString;
				}
				
				// Assignment.
				String &operator=(const String & s){
						_size = s._size;
						_theString = s._theString;
						return *this;
				}
				
				String &operator=(const std::string & s){
						_size = s.length();
						_theString = s;
						return *this;
				}

		
    private:

				std::string _theString;
				int _size;

				String(){}

        String( std::string &s )
				{
						_size = s.length();
						_theString = s.c_str();
        }

};

		// Comparison with std::string.
		inline bool operator==(const  String & STR1, const String & STR2)
		{  if (STR1.getSize() != STR2.getSize() ) return false;
			 return STR1.getString() == STR2.getString();
			 //return strcmp( STR1.getString().c_str(), STR2.getString().c_str() ) ? false : true;
		}

		inline bool operator==(const std::string & stdStr, const String & STR)
		{  return stdStr == STR.getString(); }

		inline bool operator==(const String & STR, const std::string & stdStr)
		{  return stdStr == STR.getString(); }


		inline bool operator!=(const String & STR1, const String & STR2)
		{  return STR1.getString() != STR2.getString(); }

		inline bool operator!=(const std::string & stdStr, const String & STR)
		{  return stdStr != STR.getString(); }

		inline bool operator!=(const String & STR, const std::string & stdStr)
		{  return stdStr != STR.getString(); }


		// Comparison with C string.
		inline bool operator==(const char * s, const String & STR)
		{  return STR.getString().compare(s) == 0; }

		inline bool operator==(const String & STR, const char * s)
		{  return STR.getString().compare(s) == 0; }

		inline bool operator!=(const char * s, const String & STR)
		{  return STR.getString().compare(s) != 0; }

		inline bool operator!=(const String & STR, const char * s)
		{  return STR.getString().compare(s) != 0; }

								// was getting huge linker errors, but "inlining" keeps linker quiet.
		// Output operator
		inline std::ostream &operator<<(std::ostream & outty, const String & s)
		{
		  s.display(outty);
		  return outty;
		}


} //end namespace xml

#endif
