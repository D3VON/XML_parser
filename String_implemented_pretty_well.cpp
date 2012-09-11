namespace xml {  ///////didn't put closing bracket yet

class String {
    public:
        // Copy constructor.
        String(const String &);
        // Conversion to std::string.
        operator std::string() const;
        // Assignment.
        String &operator=(const String &);
};


void String::display(ostream & out) const
{
  out<<theString;
}


// Comparison with std::string.
bool operator==(const std::string & stdString, const String & StringString)
{  return stdString == StringString.theString; }

bool operator==(const String & StringString, const std::string & stdString)
{  return stdString == StringString.theString; }

bool operator!=(const std::string & stdString, const String & StringString)
{  return stdString != StringString.theString; }

bool operator!=(const String & StringString, const std::string & stdString)
{  return stdString != StringString.theString; }


// Comparison with C string.
bool operator==(const char * s, const String & StringString)
{  return StringString.theString.compare(s) == 0; }

bool operator==(const String & StringString, const char * s)
{  return StringString.theString.compare(s) == 0; }

bool operator!=(const char * s, const String & StringString)
{  return StringString.theString.compare(s) != 0; }

bool operator!=(const String & StringString, const char * s)
{  return StringString.theString.compare(s) != 0; }

// Output operator
std::ostream &operator<<(std::ostream & out, const String & s)
{
  s.display(out);
  return out;
}
  








































class Text : public Node {
    public:
        // Returns the text content as a string.
        const String &str() const;
        // Convenience functions that internally will use RTTI.
        static bool is_Text(const Node *);
        static const Text *to_Text(const Node *);
    public:
        ... // You could add more to the public interface, if you wanted to.
    private:
        ... // Private things for your implementation.
};


class Element : public Node {
    public:
        // Returns the name of the element.  This is just
        // the part after the colon.  If there is no colon, then
        // it is the whole thing, of course.
        const String &name() const;
        // Returns the full namespace URI (not the prefix) of the element.
        // If the element is not in any namespace, this should simply
        // return an empty String.  Note that 'namespace' is a reserved
        // keyword, so we don't fully spell it out.
        const String &nmspace() const;
        // Returns the number of children nodes.
        size_t n_children() const;
        // Returns the i'th child.
        const Node *child(size_t i) const;
        // Accepts a visitor.
        void accept(Visitor *) const;
        // Convenience functions that internally will use RTTI.
        static bool is_Element(const Node *);
        static const Element *to_Element(const Node *);
    public:
        ... // You could add more to the public interface, if you wanted to.
    private:
        ... // Private things for your implementation.
};