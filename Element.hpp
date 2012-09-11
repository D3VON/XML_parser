#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include "Node.hpp"
#include "String.hpp"
#include "Visitor.hpp"
#include <string.h> 
#include <vector>  
#include <set>  
#include <map> 
#include <stack>   

namespace xml {

class Visitor;

class Element : public Node {

		//friend class String;
		//LEARNED: duh!  This class uses string's private member, 
		//not the other way around. 

    private:
        
				String tagName;
				String tagNameSpace; // this Element's namespace
				String namespcPrefx;

				Element *parent; // ptr to parent of this Element

				// list of children of this Element
				std::vector<Node*> childrens; // list keeps children in right order

				// number of children of this Element
				//std::vector<Node*>::.............can't seem to use this
				size_t numChildren; 

				// set of namespace prefixes this element (re)bound to namespaces
				std::set<std::string> prefixes;
			  std::set<std::string>::iterator it;
			

    public:

				Element() : tagName(), tagNameSpace(), namespcPrefx() { parent = NULL; } 

				Element(const std::string &tagname, const std::string &nspPrefx, const std::string &namespc)
				{
					tagName = tagname;
					tagNameSpace = namespc;
					namespcPrefx = nspPrefx;
				}

			 ~Element(){
											childrens.clear(); // vector of Node*
											prefixes.clear();  // set of strings
											//it        // iterator to prefixes
			 } 

				// 'setter' methods
				void setTagName(const std::string &name);
				void setNamespace(const std::string &nameSpace);
				void setNameSpcPrefx(const std::string &namespcPref);
				void setParent(Element*p);
				const Element * getParent() const;
				void addChild(Node* child);// add child to vector				
				//Node* getNextChild();// get next child from queue
				//void removeChild();// remove child from queue

        // Returns the name of the element.  This is just
        // the part after the colon.  If there is no colon, then
        // it is the whole thing, of course.
        const String &name() const;


        // Returns the full namespace URI (not the prefix) of the element.
        // If the element is not in any namespace, this should simply
        // return an empty String.  Note that 'namespace' is a reserved
        // keyword, so we don't fully spell it out.
        const String &nmspace() const;


        // Returns the namespace prefix of the element.
        // If the element is not in any namespace, this should simply
        // return an empty String. 
        const String &nmspaceprfx() const;
				

        
        // Returns the number of children nodes.
        size_t n_children() const;

        // Returns the i'th child.
        const Node *child(size_t i) const;

        // Accepts a visitor.
        void accept(Visitor *) const;

        // Convenience functions that internally will use RTTI.
        static bool is_Element(const Node *);

        static const Element *to_Element(const Node *);
        // You could add more to the public interface, if you wanted to.

				// add prefix to list of prefixes (re)bound by this tag
				void addPrefix(std::string * prefx){
					prefixes.insert(*prefx);
				}

				void 
				flushBindings
				( std::map<std::string, std::stack<std::string> > *nspcBindings )
				{
					for (it=prefixes.begin(); it!=prefixes.end(); ++it)
					{
						(*nspcBindings)[*it].pop();
					}
					prefixes.clear();
				}

				// Has prefix already been bound by this tag?  
				// If so, that's bad: can't rebind within same tag!
				// So, we have to check if it's in the list bound by this tag.
				bool prefixExists(std::string * prefx){
					return prefixes.find(*prefx) != prefixes.end();
				}


};

/*
  The above class represents XML elements. It inherits from the Node class. 
  RTTI is used to distinguish an Element derived class from a Text 
  derived class.
 */


} // end namespace xml

#endif
