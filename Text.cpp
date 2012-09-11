#include "Node.hpp"
#include "String.hpp"
#include "Text.hpp" 
#include "Element.hpp"
#include "Visitor.hpp"
#include <string.h> 

        // Returns the text content as a string.
        const xml::String & xml::Text::str() const{
					return theText;
				}

				// Sets the text as a String object
				void xml::Text::setText(const std::string &text){
					theText = text;
				}

				void xml::Text::setParent(xml::Element*p){
					parent = p;
				}

				const xml::Element * xml::Text::getParent() const{
					return parent;
				}

				
        // Accepts a visitor.
        void xml::Text::accept(xml::Visitor *v) const{
					// this is Java: v.visit(this);
					// -----------do nothing--------
				}


				// Convenience functions that internally will use RTTI.
        bool xml::Text::is_Text(const xml::Node * node_pointer){

						/*MORE MYSTERIOUS C++ BOGOSITY: if you declare a variable 
							or method as static in the class declaration, you don't 
							need (CORRECTION: CAN'T USE) the static keyword in the definition. 
							The compiler still knows that the variable/method is part of the 
							class and not the instance.
						 */
								
				  // to find whether abc_pointer is pointing to xyz type of object
					const xml::Text * text_pointer = dynamic_cast<const xml::Text*>(node_pointer);

					//element_pointer = dynamic_cast<element*>(node_pointer);
 
					if (text_pointer != NULL)
					{
						//std::cout << "node_pointer is pointing to a Text class object";   // identified
						return true;
					}
					else
					{
						//std::cout << "node_pointer is NOT pointing to a Text class object";
						return false;
					}
								
				}
				

				const xml::Text * xml::Text::to_Text(const xml::Node * n){
					return (xml::Text *)n; //const_cast<const xml::Text*>(n); 
					                       //sooo, sometimes you can cast a const
																 //without trouble; dunno why.
				}

/* The above class represents XML text content. It inherits from the 
   Node class. RTTI can be used to distinguish an Element object from 
   a Text object when just a pointer to a Node is available.
 */
