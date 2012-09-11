#include <stdio.h>
#include "String.hpp"
#include "Node.hpp"
#include "Element.hpp"
#include "Text.hpp"
#include "Visitor.hpp"
#include "Parser.hpp"
#include <iostream>
#define offsetof(struct_type, field_name) \
(  (size_t)  (&  ((struct_type *)0)->field_name  )  )

using namespace std;
using namespace xml;




struct A
{
	char c;
	struct A *next;
	struct A *prev;
};

struct B
{
	int a[40];
	struct B *next;
	struct B *prev;
	double x;
};

struct C
{
	struct C *next;
	struct C *prev;
	char c[21];
};
















int main(int argc, char *argv[])
{
	cout<<"========================================"<<endl;
	cout<<"========================================"<<endl;
	cout<<"=========   now, traverse tree   ======="<<endl;
	cout<<"========================================"<<endl;
	cout<<"========================================"<<endl<<endl;

	Parser parser;

//111111111111111111111111111111111111111111111
//         pass in documents

	Element *root = parser.parse();

//222222222222222222222222222222222222222222222
//         define visitor class & methods


//333333333333333333333333333333333333333333333
//         pass Visitor to root (just prints root element)
//
//         ... thusly: root->accept(&v);
	
	parser.printTree(root);
	
//444444444444444444444444444444444444444444444
//         implement RTTI in Element class


// This is junk; practice for the midterm
	//int x = ( ((A*)0)->prev - ((A*)0)    );

	int v = offsetof(A,c);
	int w = (  (size_t)  (&  ((A *)0)->next  )  );
	int x = (  (size_t)  (&  ((A *)0)->prev  )  );



	cout<<v<<"   "<<w<<"   "<<x<<endl;

	return 0;
}
