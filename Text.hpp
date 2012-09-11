#ifndef TEXT_HPP
#define TEXT_HPP

#include "Node.hpp"
#include "Element.hpp"
#include "String.hpp"
#include "Visitor.hpp"
#include <string.h> 




namespace xml {

class Element;
class Visitor;
	
class Text : public Node {

		//friend class String;
		//LEARNED: duh!  This class uses string's private member, 
		//not the other way around. 
		
    private:
			String theText;
			Element *parent;

    public:

				//Text() {}
				Text() : theText() {}
				
				Text(const std::string &text)
				{
					theText = text;
				}


			 ~Text(){ /*delete parent;*/ }

        // Returns the text content as a string.
        const String &str() const;

				// Sets the text as a String object
				void setText(const std::string &name);

				// Sets this Text object's parent in the xml tree
				void setParent(Element*p);

				// Gets this Text object's parent in the xml tree
				const Element * getParent() const;


        // Accepts a visitor.
        void accept(Visitor *) const;



/* FOR THE NEXT COUPLE FUNCTIONS:
 * A base class pointer can point to objects of any class which is derived 
 * from it. RTTI is useful to identify which type (derived class) of object is 
 * pointed to by a base class pointer.
 */

        // Convenience functions that internally will use RTTI.
        static bool is_Text(const Node *);
        static const Text *to_Text(const Node *);				
				
};

}// end namespace xml (big, uncomfortable problems if this bracket isn't here.

/* The above class represents XML text content. It inherits from the 
   Node class. RTTI can be used to distinguish an Element object from 
   a Text object when just a pointer to a Node is available.
 */

 
#endif
