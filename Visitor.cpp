
				
				//virtual void start_element_visit(const Element &) = 0;
        //virtual void end_element_visit(const Element &) = 0;
        //virtual void visit_text(const Text &) = 0;

/*
An application will derive a concrete class from the above abstract base class,
and pass an instance of it to the root Element in the accept() member function. 
Calling accept() on anything other than a root Element results in undefined 
behavior.
After accepting a visitor, callbacks must be invoked on the visitor object 
in document order (depth-first). For example, consider the small application 
program below. All of this code is written by the application programmer.


I DON'T UNDERSTAND: how is visitor to know subclass names, e.g. Elm1, Elm2...
rather than just the generic Element type.  (Must be where RTTI/Reflection comes
in.)  My understanding is that Visitor pattern implements the abstration Visitor, 
and has many visit() functions that take each different Element type as an arguments. 

Meanwhile, each sub-type of element has an inherited 
accept(Visitor v){v.visit(this));//double dispatch} method.

Then each Visitor subtype has in its visit(Elm1){ Elm1.doSomething();}

 */