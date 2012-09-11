#include "Node.hpp"
#include "String.hpp"
#include "Element.hpp"
#include "Visitor.cpp"


				void xml::Element::setTagName(const std::string &name){
					tagName = name;
				}
			
				void xml::Element::setNamespace(const std::string &nameSpace){
					tagNameSpace = nameSpace;
				}

				void xml::Element::setNameSpcPrefx(const std::string &namespcPref){
					namespcPrefx = namespcPref;
				}

				void xml::Element::setParent(xml::Element*p){
					parent = p;
				}

				const xml::Element * xml::Element::getParent() const{
					return parent;
				}

				void xml::Element::addChild(xml::Node* child){
					childrens.push_back(child);
					numChildren = childrens.size();
				}


				// Convenience functions that internally will use RTTI.
        bool xml::Element::is_Element(const xml::Node * node_pointer){

						/*MORE MYSTERIOUS C++ BOGOSITY: if you declare a variable 
							or method as static in the class declaration, you don't 
							need (CORRECTION: CAN'T USE) the static keyword in the definition. 
							The compiler still knows that the variable/method is part of the 
							class and not the instance.
						 */
								
				  // to find whether abc_pointer is pointing to xyz type of object
					const xml::Element * element_pointer = dynamic_cast<const xml::Element*>(node_pointer);

					//element_pointer = dynamic_cast<element*>(node_pointer);
 
					if (element_pointer != NULL)
					{
						//std::cout << "node_pointer is pointing to a Element class object";   // identified
						return true;
					}
					else
					{
						//std::cout << "node_pointer is NOT pointing to a Element class object";
						return false;
					}
								
				}


				size_t xml::Element::n_children() const {
					return numChildren;
				}

				// Returns the i'th child.
				const xml::Node * xml::Element::child(size_t i) const{
					return childrens[i];
				}		

        // Returns the name of the element.  This is just
        // the part after the colon.  If there is no colon, then
        // it is the whole thing, of course.
							// LEARNED: 2nd 'const' means if obj is const, this meth still works
        const xml::String &xml::Element::name() const{
					return tagName;
				}

				// Returns the full namespace URI (not the prefix) of the element.
        // If the element is not in any namespace, this should simply
        // return an empty String.  Note that 'namespace' is a reserved
        // keyword, so we don't fully spell it out.
										//ah, returns a reference?
        const xml::String &xml::Element::nmspace() const{
					return tagNameSpace;
				}

        // Returns the namespace prefix of the element.
        // If the element is not in any namespace, this should simply
        // return an empty String. 
        const xml::String &xml::Element::nmspaceprfx() const{
					return namespcPrefx;
				}
      

        // Accepts a visitor.
        void xml::Element::accept(xml::Visitor *v) const{
					// this is Java: v.visit(this);
					// -----------do nothing--------
				}
        //triggers a traversal of the whole tree???
        // (depth first search) and outputs what we want????


				const xml::Element * xml::Element::to_Element(const Node * n){
					return (Element *)n; //const_cast<Element*>(n); 
				}
				// if we're just going to cast it anyhow, why make param a const in the first place?!

/*
  The above class represents XML elements. It inherits from the Node class. 
  RTTI can be used to distinguish an Element derived class from a Text 
  derived class.
 */


/*
int main(int argc, char *argv[])
{
	String a;
	std::string str = "Hello, world\n";
  String s = String::StringConstructor(str);
  cout<< "string encapsulated into 'String' s: "<<s.showIt() << endl;

  cout<<"copying a 'String' object to 'String' z..."<<endl;
  String z = String(s);
  cout<< "string encapsulated into 'String' z: "<<z.showIt() << endl;


	Element e = ElementConstructor();

	return 0;
}

*/