/*
  The assignment is to write a parser for a simplified form of XML, 
  containing only start-tags, end-tags, content, and namespaces.

 */
#include "String.hpp"
#include "Node.hpp"
#include "Element.hpp"
#include "Text.hpp"
#include "Visitor.hpp"
#include <sstream>
#include <iostream>
#include <cassert>
#include <string>
#include <algorithm>
#include <map>  
#include <stack>  
#include <fstream>
using namespace std;

namespace xml{

class Parser
{

public:
	Parser(){}
	~Parser(){}

	/*
	
		what the HECK is the diff btwn Parser(){}, and Perser();
		...I see both all the time, but the 2nd one always chokes this compiler.
	
	*/




/* GLOBALS:
   1. a stack for tag bookkeeping;
	 2. a map of stacks for namespace bookkeeping. 
 */
stack<Element*> tagStack;

map<string, stack<string> > nspcBindings;
map<string, stack<string> >::iterator it;	// used only for testing at end



bool validAlpha(string& s)
{
  if ( (s[0] >= 'A' && s[0] <= 'Z') 
    || (s[0] >= 'a' && s[0] <= 'z')
    || (s[0] == '_') )
  {
    //cout<< "checking "<<s[0]<<endl;
    return true;
  }
    //cout<<"returning false from validAlpha"<<endl;
  return false;
}

bool validAlphaNumScore(char c)
{
  if (   (c >= 'A' && c <= 'Z')
      || (c >= 'a' && c <= 'z')
      || (c >= '0' && c <= '9')
      || (c == '_') 
     )
  {
    //cout<< "checking "<<c<<endl;
    //cout<<"returning true from validAlphaNumScore"<<endl;
    return true;
  }
    //cout<<"returning false from validAlphaNumScore"<<endl;
  return false;
}


void doTree(Node* child){

	Node* n = child;
	cout<<((Element*)n)->name()<<" has "<< (int)((Element*)n)->n_children() << " children."<<endl;

	if (Text::is_Text(n)) // PRINT TEXT CONTENT ONLY
	{
		cout<<((Text*)n)->str()<<endl;
	}
	else // IT'S A TAG; PRINT IT; RECURSE IF IT HAS CHILDREN
	{
		cout<<"<";
		if ( !((Element*)n)->nmspaceprfx().showIt().empty() )
		{ 
			cout<<((Element*)n)->nmspaceprfx()<<":"; 
		}
		cout<<((Element*)n)->name()<<">"<<endl;
		// FINISHED PRINTING TAG

		// possible children. traverse vector, and recurse
		for (size_t i = 0; i < ((Element*)n)->n_children(); i++) {
		  doTree( const_cast<Node*>( ((Element*)n)->child(i) ) );	
		}

		// now do closing tags
		cout<<"</";
		if ( !((Element*)n)->nmspaceprfx().showIt().empty() )
		{ 
			cout<<((Element*)n)->nmspaceprfx()<<":"; 
		}
		cout<<((Element*)n)->name()<<">"<<endl;
	}
}


// handle that funny 'sentinel' node I have as "~root~"
void printTree(Node* n){
	assert( ((Element*)n)->name() == "~root~" );

	Node* realroot = const_cast<Node*>(((Element*)n)->child(0));// 'kid' is the 'real' root

	cout<<"~root~'s child is: "<< ((Element*)realroot)->name()<<endl;

	doTree(realroot);
}


bool validTag(string& s)
{
  //cout<<"starting validTag function"<<endl;
  if (!validAlpha(s)) return false;

  int index = 1;
  while (s[index] != 0 )
  {
    //cout<<"checking other chars in validTag function"<<endl;
    if (!validAlphaNumScore(s[index++])) return false;
  }
  //cout<<"returning true from validTag"<<endl;
  return true;
}


void createNewPrefixMapping(string& prefix, string& nmspace){
	// we want it to fail (somehow) if it's trying to add an existing prefix
	assert(nspcBindings.find(prefix) == nspcBindings.end());
		
	stack<string> newStack; // new stack for this prefix
	newStack.push(nmspace); // add the value to the stack
	
	nspcBindings[prefix] = newStack; // map prefix to that new stack
}


/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
 ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
 |||||||||||||||             DO PARSING               |||||||||||||||
 ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
 |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

Element * parse(const char* doc, int sz){
		//cout<<sz<<endl;

		string str(doc);

		string tagName, namespacePrefix, prefixANDtagName, rawTag, moreStuff;
		string tagNamespace, content, anotherPrefx, anotherNamespace;
		int pos1, pos2, taglength, clsPos, whitePos, xPos, badTag, tagNameLength;
		int nsPos1, nsPos2, afterTxt, colonPos, equalPos, nameSize;

			// Assuming doc might begin with spaces, 
			// but but first meaningful thing is assumed to be root element.
			pos1 = str.find_first_not_of(" \t\n\v\f\r");

			/* I'm not sure if the made-up "root" needs to be a full Element, 
				 or just a pointer to the "real" root. 
			 */
			Element *root = new Element(); 
			root->setTagName("~root~");
			tagStack.push(root);
															
														 /***********************
															* PARSE ENTIRE STRING *
															***********************/

			while(1){ // go through entire string
															/*****************
															 * GET WHOLE TAG *
															 *****************/
				pos1 = str.find ("<", pos1);
				if (pos1 < 0) break;  //cout << "'<' found at position " << pos1 << endl;
				pos1++; // so it doesn't keep finding the same character
				pos2 = str.find (">", pos1); //cout << "'>' found at position " << pos2 << endl;
				taglength = pos2-pos1;
				rawTag = str.substr( pos1, taglength );  cout << rawTag << "<---rawTag" << endl;
				// ALWAYS REMEMBER, 2ND ARG IS COUNT OF CHARS, NOT POSITION

															/*********************
															 * GOT WHOLE TAG,    *
															 * BEGIN PARSING TAG *
															 *********************/

															//OPENING TAG

				//if doesn't start with'/', it's an opening tag
				clsPos = rawTag.find ("/"); 
				if (clsPos != 0) // make sure it isn't a closing tag
				{ 
					
					// detect if whitespace after tag's name
					char charary[] = " \t\n\v\f\r";
					whitePos = rawTag.find_first_of(charary, 0);

					// CASE: no whitespace in tag; could have namespace prefix, tho
					if (whitePos < 0) // no space, so, no namespace defined
					{                // --could still be namespace prefix, though.

															//GET PREFIX:TAGNAME

						//if exists a colon, split namespace prefix from element name
						colonPos = rawTag.find_first_of(":", 0);
						if (colonPos > 0)
						{
							namespacePrefix = rawTag.substr(0,colonPos);
							tagName         = rawTag.substr(colonPos+1,taglength);
						} 
						else // it's only a tag name.
						{            
							tagName = rawTag; //cout<<"namespace doesn't exist"<<endl;
							namespacePrefix = "";
						}

							// CASE: exists whitespace in tag
					}else
					{
						assert(whitePos>0); // whitespace can't be btwn '<' and 'prefix:tag'
						// grab prefix:tag cluster
						prefixANDtagName = rawTag.substr(0,whitePos);

						//if exists a colon in the prefix:tagname clump,
						//then split namespace prefix from element name
						colonPos = prefixANDtagName.find_first_of(":", 0);
						if (colonPos > 0)
						{
							namespacePrefix = rawTag.substr(0,colonPos);
							tagNameLength = whitePos-colonPos-1;
							//cout << "tag name length is "<<tagNameLength<<endl;
							tagName         = rawTag.substr(colonPos+1,tagNameLength);
						}
						else // it's should be only a tag name, or bind more namespaces
						{            
							tagName = rawTag.substr(0,whitePos);
							namespacePrefix = "";
							tagNamespace = "";
						}
					}
					cout << tagName << "<---element name"<< endl;

															//VALIDATE TAG NAME

					if (!validTag(tagName)) exit(1);

															//RECORD TAG NAME & NAMESPACE-PREFIX 
															//INTO THE ELEMENT

					Element *current = new Element(); 
					current->setTagName     (tagName);         //cout<<"<"<<tagName<<">";
					current->setNameSpcPrefx(namespacePrefix); //cout<<", Prefix: "<<namespacePrefix;
					current->setParent      (tagStack.top());  //cout<<", Parent: "<<tagStack.top()->name()<<endl;
					// make this Element a child of that parent
					tagStack.top()->addChild((Node*)current);  
					//cout<<"0000000000000000Parent "<< tagStack.top()->name() <<" has "<<tagStack.top()->n_children()<<" children.00000000000000000"<<endl;

					//cout<<"DONE GETTING NAME, PREFIX, PARENT; PUSH CURRENT TAG TO GLOBAL STACK"<<endl;
					tagStack.push(current);
					// current->setNamespace   (tagNamespace); WE DON'T KNOW THIS YET FOR MANY CASES

					nameSize = tagName.size();
          if(namespacePrefix.size() > 0) 
            nameSize += namespacePrefix.size()+1;//including colon

          xPos = rawTag.find_first_not_of(" \t\n\v\f\r", nameSize);
					//xPos = rawTag.find ("xmlns:", whitePos);
          do{

            if (xPos < 0) // nothing (but maybe whitespace) after prefix:tag cluster
            {            
              tagNamespace = ""; 
            }else // something after prefix:tag cluster
            {
              // verify no more 'junk' after 1st occurance of whitespace

                cout<<rawTag[xPos]<<"<--is first non-white character found"<<endl;
                // first non-whitespace character after 
                // prefix:tag clustermust be "x"


                // if not contiguous "xmlns:", then fail
                xPos = rawTag.find ("xmlns:", xPos, 6);
                assert(xPos > -1);
              
  /*
                cout<<taglength<<" is taglength"<<endl;
                cout<<rawTag<<"<+++++++++++is the rawTag"<<endl;
                moreStuff = rawTag.substr(whitePos, 2);//taglength-whitePos-1);
                cout<<moreStuff<<"<--is moreStuff"<<endl;
                badTag = moreStuff.find_first_not_of(" \t\n\v\f\r");
                
                assert(badTag < 0); // -1 means no *not* whitespace found
  */
            //}else // yes, it has another well-formed 'xmlns:'
            //{          

                              //STORE NEW NAMESPACE BINDINGS

              //do // validate namespace(s) OLD 'DO'
              //{
                // store namespace-prefix
                equalPos = rawTag.find ("=", xPos);
                anotherPrefx = rawTag.substr( xPos+6, equalPos-xPos-6 );					

                // store namespace
                nsPos1 = rawTag.find ("\"", xPos); // find open quote
                nsPos1++;//start after the first quote
                nsPos2 = rawTag.find ("\"", nsPos1);
                assert( (nsPos2-nsPos1)>0 ); 
                anotherNamespace = rawTag.substr( nsPos1, nsPos2-nsPos1 );
                // I ALWAYS FORGET: 2ND ARG IS COUNT OF CHARS, NOT POSITION
                
                // this asserts the *LOCAL* set doesn't re-bind a prefix twice in the same tag. 
                // the *global* map *can* rebind (push stack)
                assert(!current->prefixExists(&anotherPrefx));
                current->addPrefix(&anotherPrefx); // store (re)binding in local Element
                //cout<< "========================= "<<anotherPrefx<<" is a new prefix binding in this tag"<<endl;

                /* If OK to (re)bind locally, must (re)bind globally.
                   First, check if exists in global map of stacks. 
                   If yes, push new namespace binding onto that stack. 
                   If no, add new key/value to the global map of stacks.
                 */                                 // if already there
                if( nspcBindings.find(anotherPrefx) != nspcBindings.end() ){
                  nspcBindings[anotherPrefx].push(anotherNamespace); // just push
                }else{ //make new key/value (stack), and push new namespace
                  createNewPrefixMapping(anotherPrefx, anotherNamespace);
                }
                xPos = rawTag.find_first_not_of(" \t\n\v\f\r", nsPos2);

					}while (xPos > -1 );
					// all possible (re)bindings of namespaces are finished 
					// for this tag & its children

					}
					if ( !namespacePrefix.empty() )
					{
						tagNamespace = nspcBindings[namespacePrefix].top();
					}
					//cout<<"^^^^^^^^^^^^^^^^^this tag's namespace is: "<<tagNamespace<<"^^^^^^^^^^^^^^^^^"<<endl;
					current->setNamespace(tagNamespace);
				}
				else // it's a CLOSING tag, so handle that.
				{

															/*******************
															 * GET CLOSING TAG *
															 *******************/

	/* SORRY: UGLY, SMELLY REDUNDANCY; 
		 THIS IS A PARAPHRASE OF THE CODE ABOVE,
		 USED TO WEEDLE OUT THE OPENING TAGS
	 */
					
					// detect if whitespace after tag's name
					char charary[] = " \t\n\v\f\r";
					whitePos = rawTag.find_first_of(charary, 0);

					// CASE: no whitespace in tag; could have namespace prefix, tho
					if (whitePos < 0) // no space, so, no namespace defined
					{                // --could still be namespace prefix, though.

						//if exists a colon, split namespace prefix from element name
						colonPos = rawTag.find_first_of(":", 0);
						if (colonPos > 0)
						{
							namespacePrefix = rawTag.substr(1,colonPos-1);
							tagName         = rawTag.substr(colonPos+1,taglength);
						} 
						else // it's only a tag name.
						{            
							tagName = rawTag.substr(1,taglength);
							namespacePrefix = "";
						}

					// CASE: exists whitespace in tag
					}else 
					{

						assert(whitePos>0); // whitespace can't be btwn '<' and 'prefix:tag'
						assert(whitePos>1); // this is the position after the '/'
						// grab prefix:tag cluster
						prefixANDtagName = rawTag.substr(0,whitePos);

						//if exists a colon in the prefix:tagname clump,
						//then split namespace prefix from element name
						colonPos = prefixANDtagName.find_first_of(":", 0);
						if (colonPos > 0)
						{
							namespacePrefix = rawTag.substr(1,colonPos-1);
							int tagNameLength = whitePos-colonPos-1;
							//cout << "tag name length is "<<tagNameLength<<endl;
							tagName         = rawTag.substr(colonPos+1,tagNameLength);
						}
						else // it's only a tag name.
						{            
							tagNameLength = whitePos-1;
							//cout << "tag name length is "<<tagNameLength<<endl;
							tagName         = rawTag.substr(1,tagNameLength);
							namespacePrefix = "";



							// verify no more 'junk' after 1st occurance of whitespace
							// shouldn't even be new namespace binding.
							moreStuff = rawTag.substr(whitePos, taglength-whitePos);
							badTag = moreStuff.find_first_not_of(" \t\n\v\f\r");
							assert(badTag < 0); // -1 means nothing *not* whitespace found


						}
					}

		cout<<tagName<<"<---closing tag name";
		cout<<", and its nspPrefix is: "<<namespacePrefix<<endl;
		cout<<tagStack.top()->name()<<"<---name at top of stack (should be its opening tag)."<<endl;


					// compare with what's on stack, 
					// if OK, pop any re-bound namespaces, pop stack, and we're done.
					assert((tagStack.top())->name() == tagName);
					assert((tagStack.top())->nmspaceprfx() == namespacePrefix);
					if ( !namespacePrefix.empty() )
					{
						// iterates through opening tag's set of (re)bound namespaces
						// and pops them off the global map of stacks
						tagStack.top()->flushBindings(&nspcBindings);
						//cout<<"all namespaces (re)bound by this tag have been POPPED "<<endl;
					}
					//cout<<"</" << namespacePrefix<<":"<< tagName << "> POPPED  (OK if no prefix in this output)"<<endl;
					tagStack.pop();
				}

				/************************
				 * FINISHED PARSING TAG *
				 ************************/  
					 
				// could have been last tag & end of string, so check for that
				//cout<<pos2+1<<" (just beyond closing bracket), "<<str.length()<<" (string length)"<<endl;
				if (pos2+1 == (int)str.length()) break;


				/**********************
				 * GET TEXT / CONTENT *
				 **********************/
				if (str.at(pos2+1) != '<' ) // means text follows -- even if it's just a space
				{
					afterTxt = str.find ("<", pos2); // find end of text content
					if (afterTxt < 0) break; // never be true in a well formed doc.
					content = str.substr(pos2+1, afterTxt-pos2-1);
					// ALWAYS REMEMBER, 2ND ARG IS COUNT OF CHARS, NOT POSITION

					Node *currentText = new Text(); 
					((Text*)currentText)->setText(content);           //cout<<"__________Text: \""<<content<<"\""<<endl;
					//cout<<"...that content's parent is: ";
					((Text*)currentText)->setParent(tagStack.top());  //cout<<tagStack.top()->name()<<endl;

					// make this Text a child of that parent
					tagStack.top()->addChild(currentText);
													//NOTE: text never has children; only Elements have children

				}// end if

								tagName.clear();
				namespacePrefix.clear();
					 prefixANDtagName.clear();
								 rawTag.clear();
					 tagNamespace.clear();
								content.clear();

			}//end while(1)

		nspcBindings.clear();
		// now, nothing should print in the following:
/*
		// show content of map of stacks (for each prefix, pop whole stack):
		for ( it=nspcBindings.begin() ; it != nspcBindings.end(); it++ ){

			// OK, this is weird syntax I didn't expect.  Thank god for google.
			cout << "========namespaces for prefix "<< (*it).first << "============="<<endl;// " => " << (*it).second.top() << endl;
			while( ! (*it).second.empty() ){
				cout << "   " << (*it).second.top()<<endl; 
				(*it).second.pop();
			}
		}
*/		
		// get rid of my funny 'sentinel' node "~root~"
		root = (Element*)root->child(0);
		return root;
}

/* GIVEN API:
    public:
        Parser(); // Must be able to create one.
        const Element *parse(const char *doc, size_t sz);
 */
 
/* To parse a document, the user will first instantiate a Parser object. 
   She will then call parse() and pass in the document in memory and its 
   size. Your code must not modify the memory, of course. This method 
   returns a pointer to the root Element object.

   For example, if the input XML document is:

   <e1><e2>Text1</e2>Text2<e3></e3></e1>

   then the resulting DOM tree will have a single root node named e1 with 
   three child nodes. The first child node will be an Element node e2. The 
   second child node will be a Text node with Text2 as the string. The 
   third child node will be an Element node named e3. The e2 Element 
   node will have a single Text node, containing the content Text1, 
   as a child. The e3 Element node will have no children.

   Deleting the root Element object will delete all child objects. 
   Calling delete on any other Node object will result in undefined 
   behavior. The application must guarantee that the document will 
   be unchanged and persist as long as any Node objects or String 
   objects associated with the document still exist.
 */

};// end of class Parser

//sssooooooooooooooooooooooooooooooooooooooo easy to forget the semicolon.  
// I couldn't care less that it needs a semicolon, but it's ultra important.  
// Why doesn't the compiler just put it in?!  I used the key word "class".  Jerks. 
// They should have mandated that we put "still a class" in the middle every 17 lines. 
// And then a key phrase "just_so_ya_know_--_class_is_finished_here". 
// --because the closing bracket is just not sufficient.  Jerks. 

} // end xml namespace