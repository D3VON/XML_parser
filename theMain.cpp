#include "Parser.hpp"
#include "Visitor.hpp"
#include "Element.hpp"
#include "Text.hpp"
#include <iostream>

using namespace std;

class MyVisitor : public xml::Visitor {
    public:
        virtual void start_element_visit(const xml::Element &);
        virtual void end_element_visit(const xml::Element &);
        virtual void visit_text(const xml::Text &);
};

void
MyVisitor::start_element_visit(const xml::Element &e) {
    cout << "Starting visit of element named \"" << e.name()
         << "\" in namespace \"" << e.namspace() << "\"..." << endl;
}

void
MyVisitor::end_element_visit(const xml::Element &e) {
    cout << "Ending visit of element named \"" << e.name()
         << "\" in namespace \"" << e.namspace() << "\"..." << endl;
}

void
MyVisitor::visit_text(const xml::Text &t) {
    cout << "Visiting text content \"" << t.str() << "\"..." << endl;
}

int
main() {

    xml::Parser parser;

    const char *doc = ...;

    xml::Element *root = parser.parse(doc, sz);// sz is size?
                         // creates the tree?
    MyVisitor v;
    root->accept(&v); //root accepts visitor, and traversal happens(?)
}

/*

The above is the example of application code that would use 
your Visitor pattern implementation to traverse the DOM tree. 
Note that it is application code, not part of your parser proper. 
Your Visitor implementation should traverse every node starting 
from the root element and invoke callbacks on the passed in 
Visitor object. Using the code above, if the input XML document was:

<r>Text1<ns1:c1 xmlns:ns1="URI1"></ns1:c1></r>

then the sample application program above would print:

Starting visit of element named "r" in namespace ""...
Visiting text content "Text1"...
Starting visit of element named "c1" in namespace "URI1"...
Ending visit of element named "c1" in namespace "URI1"...
Ending visit of element named "r" in namespace ""...

*/