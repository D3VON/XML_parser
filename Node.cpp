class Node {
    public:

        /* FURTHER INFO: RTTI is available only for classes
           which are polymorphic, which means they have at 
           least one virtual method. In practice, this is 
           not a limitation because base classes must have 
           a virtual destructor to allow objects of derived 
           classes to perform proper cleanup if they are 
           deleted from a base pointer.
         */


    public:
        // You could add more to the public interface, if you wanted to.
				Node();



    private:
        // Private things for your implementation.  Probably will not need
        // anything, since this primarily an interface class.
};
/*
The above class is a base class. 
It is polymorphic, and so will work with RTTI.
*/
