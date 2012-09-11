#include "String.hpp"
#include <iostream>
#include <string>

using namespace std;
//using namespace xml;
int main(void)
{
	string woof = "woof";
	xml::String s = xml::String::StringConstructor( woof );

	string w = s;

	cout << s << "is from s, " << w << " is from w" << endl;




	cout<<"end of program.  To exit, hit <enter>"<<endl;
	std::cin.get(); // to keep visual studio's FUCKING console (terminal) window open so I can view output. Fucking bastards.

}