#ifndef _SSLL_H_
#define _SSLL_H_
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <iterator>

namespace cop3530{
	template <typename T>
	class SSLL {
	private:
		struct Node {	//This is the node struct
			T data;
			Node * next;
			Node(T data){	//This is the node constructor
				this->data = data;
				this->next = NULL;
			}

			~Node(){}
		}; // end struct Node		
		Node* tail;
		Node* head;

	public:
		//--------------------------------------------------
		// Constructors/Destructor/Overloaded Operators
		//--------------------------------------------------
		SSLL(){	//This is the default constructor
			this->head = NULL;
			this->tail = NULL;
		}

		//--------------------------------------------------
		SSLL(const SSLL& src){	//This is the copy constructor
			head = NULL;
			*this = src;
		}

		//--------------------------------------------------
		~SSLL(){	//This is the destructor
			clear();
		}

		//--------------------------------------------------
		SSLL& operator=(const SSLL& src){	//This is the overloaded equals operator
			Node* currentNode = src.head;
			if (&src == this) // check for self-assignment
				return *this;// do nothing
			else{
				clear();	//delete all data
				while (currentNode != NULL){	//Traverse the list
					push_back(currentNode->data);	//make all the values equal to src
					currentNode = currentNode->next;
				}
				return *this;	//Return the newly created this
			}
		}

		//--------------------------------------------------
		T& operator[](int i){	//This is the overloaded [] operator
			int count = 0;
			Node* currentNode = head;
			if (is_empty()){	//If the list is empty 
				throw std::domain_error("The list is empty");	//Throw an exception
			}
			else if (i < 0 || i > size()){	//If the i is outside the range of nodes	
				throw std::out_of_range("Invalid index");	//Throw an exception
			}
			else if (i == 0){	//If i equal to 0
				T& element = head->data;	//Return the data in head node
				return element;
			}
			else if (i == size()){	//If i equal tail
				T& element = tail->data;	//Return the data in tail node
				return element;
			}
			else{	//If i is in between head and tail
				while (currentNode != NULL){	//Traverse the list until i is found
					++count;
					currentNode = currentNode->next;
					if (count == i){	//Once i is found 
						T& element = currentNode->data;	//Return the data in current node
						return element;
					}
				}
			}
		}

		//--------------------------------------------------
		T const& operator[](int i) const{	//This is the const overloaded [] operator
			int count = 0;
			Node* currentNode = head;
			if (is_empty()){	//If the list is empty 
				throw std::domain_error("The list is empty");	//Throw an exception
			}
			else if (i < 0 || i > size()){	//If the i is outside the range of nodes	
				throw std::out_of_range("Invalid index");	//Throw an exception
			}
			else if (i == 0){	//If i equal to 0
				T const& element = head->data;	//Return the data in head node
				return element;
			}
			else if (i == size()){	//If i equal tail
				T const& element = tail->data;	//Return the data in tail node
				return element;
			}
			else{	//If i is in between head and tail
				while (currentNode != NULL){	//Traverse the list until i is found
					++count;
					currentNode = currentNode->next;
					if (count == i){	//Once i is found 
						T const& element = currentNode->data;	//Return the data in current node
						return element;
					}
				}
			}
		}

		//--------------------------------------------------
		// Member Functions
		//--------------------------------------------------
		T replace(const T& element, int position){	//This function is used to replace a value in the list
			Node* currentNode = head;
			int count = 0;
			T oldElement;
			if (is_empty()){	//If the list is empty throw an exception
				throw std::domain_error("The list is empty");	//Throw exception
			}
			else if (position >= size() || position < 0){	//If the position value that is passed in is 
				throw std::out_of_range("Invalid index");	//out of range of the list throw exception
			}
			else if (position == 0){ //If the position equals zero 
				oldElement = head->data;	//save the old element data
				head->data = element;	//The head data value is reequated to element
				return oldElement;		//return the old element value
			}
			else if (position == size() - 1){	//If the position is at the end of the list
				oldElement = tail->data;	//save the old element data	
				tail->data = element;	//The tail data value is reequated to element
				return oldElement;		//return the old element value
			}
			else{	//If the index value is in between head and tail
				while (currentNode != NULL){	//Travese the list until the positon is found
					++count;
					currentNode = currentNode->next;

					if (position == count){	//Once the position has been located 
						oldElement = currentNode->data;	
						currentNode->data = element;	//The current data value is reequated to element
						return oldElement;	//return the old element value
					}
				}
			}
		}

		//--------------------------------------------------
		void insert(const T& element, int position){	//This is the function used to insert an element in position
			Node* currentNode = head;
			Node* newNode = new Node(element); 
			int count = 0;
			if (is_empty()){	//If the list is empty the value is placed at the begining of the list
				push_back(element);
			}
			else if (position >= size() || position < 0){	//If the position is outside the range 
				throw std::out_of_range("Invalid index");	//of the start and end of the list throw exception
			}
			else if (position == 0){	//If the position is at zero then 
				push_front(element);	//push_front the element
			}
			else if (position == size() - 1){	//If the position is tail
				push_back(element);	//push back the element
			}
			else{	//If position is between head and tail
				while (currentNode != NULL){	//Travese the list until position is found
					++count;
					currentNode = currentNode->next;
					if (position == count){	//Once the position is found
						newNode->data = currentNode->data;	//Insert the new node in between the old nodes
						currentNode->data = element;		
						newNode->next = currentNode->next;
						currentNode->next = newNode;
					}
				}
			}
		}
	
		//--------------------------------------------------
		void push_front(const T& element){	//Insert the value at the front of the list
			Node* currentNode = head;
			Node* newNode = new Node(element);
			if (is_empty()){	//If the list is empty 
				head = newNode;	//head equals the new node
				tail = newNode;	//head equals the new node
			}
			else{	//If the list is not empty
				head = newNode;	//head equals the new node
				newNode->next = currentNode;  //the next pointer now points to the next node in the list
			}
		}

		//--------------------------------------------------
		void push_back(const T& element){	//Insert the element at the back of the list
			Node* newNode = new Node(element);
			if (is_empty()){	//If the list is empty
				head = newNode;	//head equals the new node
				tail = newNode;	//head equals the new node
			}
			else{	//If the list is not empty
				tail->next = newNode;	//tail next equals the new node
				tail = tail->next;	//the tail pointer now points to the new node
			}
		}

		//--------------------------------------------------
		T pop_front(){	//Remove the first element in the list and return the value
			Node* delNode = NULL;
			T element;
			if (is_empty()){	//If the list is empty
				throw std::domain_error("The list is empty"); //Throw an exception
			}
			else{	//If the list is not empty
				if (size() == 1){	//If the list has only one element 
					element = head->data;	//The old data is saved
					delNode = head;		//the delNode points to head
					head = NULL;	//head is set to NULL indicating an empty list
					tail = NULL;	//tail is set to NULL indicating an empty list
					delete delNode;	//the head is deleted
					return element;	//The old element is returned
				}
				else{	//If the list is larger than one
					element = head->data;	//The old data is saved
					delNode = head;		//the delNode points to head
					head = head->next;	//The head pointer is set to the next node
					delete delNode;		//the head is deleted
					return element;		//The old element is returned
				}
			}
		}

		//--------------------------------------------------
		T pop_back(){	//Remove the first element in the list and return the value
			Node* delNode = NULL;
			Node* currentNode = head;
			Node* previousNode = NULL;
			T element;
			if (is_empty()){	//If the list is empty
				throw std::domain_error("The list is empty");	//Throw an exception
			}
			else{	//If the list is not empty
				if (size() == 1){	//If the list has only one element
					element = head->data;	//The old data is saved
					delNode = head;		//the delNode points to head
					head = NULL;		//head is set to NULL indicating an empty list
					tail = NULL;		//tail is set to NULL indicating an empty list
					delete delNode;		//the head is deleted
					return element;		//The old element is returned
				}
				else{	//If the list is larger than one
					element = tail->data;	//The old data is saved
					delNode = tail;		//the delNode points to tail
					while (currentNode->next != NULL){	//Traverse the list
						previousNode = currentNode;
						currentNode = currentNode->next;
					}
					previousNode->next = NULL; //Find the node befor tail
					tail = previousNode;	//Set the tail pointer to the node before original tail
					delete delNode;		//the tail is deleted
					return element;		//The old element is returned
				}
			}
		}

		//--------------------------------------------------
		T remove(int position){	//Remove an element at position 
			Node* currentNode = head;
			Node* previousNode = NULL;
			Node* delNode = NULL;
			int count = 0;
			if (is_empty()){	//If the list is empty 
				throw std::domain_error("The list is empty");	//Throw an exception
			}
			else if (position >= size() || position < 0){	//If the position is outside the range of the list
				throw std::out_of_range("Invalid index");	//Throw an exception
			}
			else if (position == 0){	//If the the position is 0
				return pop_front();	//Pop off the front element and return the value
			}
			else if (position == size() - 1){	//If the position eqaul the tail
				return pop_back();	 //Pop back the element 
			}
			else{	//If position is in between head and tail
				while (currentNode != NULL){	//Traverse the list until position is found
					++count;
					previousNode = currentNode;
					currentNode = currentNode->next;
					if (count == position){	//Once the position is found
						delNode = currentNode;	//the delNode points to position node
						T element = currentNode->data;	//The old data is saved
						previousNode->next = currentNode->next; //The previous node now equals node after position
						delete delNode;	//the current node is deleted
						return element;	//The old element is returned
					}
				}
			}
		}

		//--------------------------------------------------
		T item_at(int position) const{	//Return the item in the list at position
			int count = 0;
			Node* currentNode = head;
			if (is_empty()){	//If the list is empty 
				throw std::domain_error("The list is empty");	//Throw an exception
			}
			else if (position < 0 || position > size()){	//If the position is outside the range of nodes	
				throw std::out_of_range("Invalid index");	//Throw an exception
			}
			else if (position == 0){	//If position equal to 0
				return head->data;	//Return the data in head node
			}
			else if (position == size()){	//If position equal tail
				return tail->data;	//Return the data in tail node
			}
			else{	//If position is in between head and tail
				while (currentNode != NULL){	//Traverse the list until position is found
					++count;
					currentNode = currentNode->next;
					if (count == position){	//Once position is found 
						return currentNode->data;	//Return the data in current node
					}
				}
			}
		}

		//--------------------------------------------------
		bool is_empty() const{	//Check if the list is empty
			return (tail == NULL);	//If tail points to NULL this means the list is empty
		}

		//--------------------------------------------------
		int size() const{	//Return the size of the linked list
			int count = 0;		//The count variable is used and the value that will determine linked list size
			Node* currentNode = head;
			while (currentNode != NULL){	//Traver the list
				++count;	//Strating from the head and traversing the 
				currentNode = currentNode->next;		//list until NULL the count will be incremented by 1
			}
			return count;	//Return the value for count
		}

		//--------------------------------------------------
		void clear(){	//Deletes all the element and links in the list
			Node* delNode = head;
			while (delNode != NULL){	//Traverse the list
				head = head->next;		//list until NULL the count will be incremented by 1
				delete delNode;			// delete the delNode
				delNode = head;			//delnode pointer now points to new head
			}
			head = NULL;	//head is set to NULL indicating an empty list
			tail = NULL;	//tail is set to NULL indicating an empty list
		}

		//--------------------------------------------------
		bool contains(const T& element, bool(*fptr)(const T& a, const T& b)) const{	//contains check is the vlaue is present
			Node* currentNode = head;
			while (currentNode != NULL){	//Traverse the list 
				if (fptr(currentNode->data, element)){	//if same char is a function pointer
					return true;	//If the values are the same return true
				}
				currentNode = currentNode->next;
			}

			return false;	//If the char are not the same return false
		}

		//--------------------------------------------------
		std::ostream& print(std::ostream& out) const{	//This function prints out the list
			Node* currentNode = head;
			if(is_empty()){	//If the list is empty print out empty list
				std::cout << "<Empty List>\n\n" << std::endl;
			}
			else{	//If the list is not empty
				out << "[";
				while (currentNode != NULL){	//Traverse the list printing each node's data 
					if (currentNode->next == NULL){
						std::cout << currentNode->data; //If this is the last node in the list
					}
					else{
						std::cout << currentNode->data << ", ";
					}
					currentNode = currentNode->next;
				}
				std::cout << "]\n\n";
			}
			return out;	//Return the final string for print
		}

		//--------------------------------------------------
		// SSLL_Iter CLass
		//--------------------------------------------------
		class SSLL_Iter : public std::iterator<std::forward_iterator_tag, T>{
			public:
				typedef T value_type;
				typedef std::ptrdiff_t difference_type;
				typedef T& reference;
				typedef T* pointer;
				typedef std::forward_iterator_tag iterator_category;
				typedef SSLL_Iter self_type;
				typedef SSLL_Iter& self_reference;

			private:
				Node* here;  //Saves the passed in Node to here

			public:
				//--------------------------------------------------
				explicit SSLL_Iter(Node* start) : here(start) {}   //This is the constructor that sets here node to start of list

				//--------------------------------------------------
				SSLL_Iter(const SSLL_Iter& src) : here(src.here) {}      //This is the copy constructor

				//--------------------------------------------------
				reference operator*() const {   //This is the *overloaded operator that derefences iterators data value
					return here->data;
				}

				//--------------------------------------------------
				pointer operator->() const {   //This is the ->overloaded operator that grants access to memeber functions
					return &this;
				}

				//--------------------------------------------------
				self_reference operator=(const SSLL_Iter& src) {  //This is =overloaded operator to copy contents
					this->here = src.here;
					return *this;
				}

				//--------------------------------------------------
				self_reference operator++() {  //This is ++overloaded operator preincrements iterator
					here = here->next;
					return *this;
				}

				//--------------------------------------------------
				self_type operator++(int) {  //This is ++overloaded operator postincrements iterator
					self_type temp(*this);
					++(*this);
					return temp;
				}

				//--------------------------------------------------
				bool operator==(const SSLL_Iter& rhs) const {  //This is ==overloaded operator that checks two iterators for equality
					return (this->here == rhs.here);
				}

				//--------------------------------------------------
				bool operator!=(const SSLL_Iter& rhs) const { //This is !=overloaded operator that checks two iterators for inequality
					return (this->here != rhs.here);
				}
			}; // end SSLL_Iter

		//--------------------------------------------------
		// Const SSLL_Iter Class
		//--------------------------------------------------
		class Const_SSLL_Iter : public std::iterator<std::forward_iterator_tag, T>{
				public:
					typedef T value_type;
					typedef std::ptrdiff_t difference_type;
					typedef const T& reference;
					typedef const T* pointer;
					typedef std::forward_iterator_tag iterator_category;
					typedef Const_SSLL_Iter self_type;
					typedef Const_SSLL_Iter& self_reference;

				private:
					const Node* here;  //Saves the passed in Node to here

				public:
					//--------------------------------------------------
					explicit Const_SSLL_Iter(Node* start) : here(start) {}  //This is the constructor that sets here node to start of list

					//--------------------------------------------------
					Const_SSLL_Iter(const Const_SSLL_Iter& src) : here(src.here) {}   //This is the copy constructor

					//--------------------------------------------------
					reference operator*() const {   //This is the *overloaded operator that derefences iterators data value
						return here->data;
					}

					//--------------------------------------------------
					pointer operator->() const {  //This is the ->overloaded operator that grants access to memeber functions
						return &this;
					}

					//--------------------------------------------------
					self_reference operator=(const SSLL_Iter& src) {  //This is =overloaded operator to copy contents
						this->here = src.here;
						return *this;
					}

					//--------------------------------------------------
					self_reference operator++() {   //This is ++overloaded operator preincrements iterator
						here = here->next;
						return *this;
					}

					//--------------------------------------------------
					self_type operator++(int) {    //This is ++overloaded operator preincrements iterator
						self_type temp(*this);
						++(*this);
						return temp;
					}

					//--------------------------------------------------
					bool operator==(const Const_SSLL_Iter& rhs) const {   //This is ==overloaded operator that checks two iterators for equality
						return (this->here == rhs.here);
					}

					//--------------------------------------------------
					bool operator!=(const Const_SSLL_Iter& rhs) const {  //This is !=overloaded operator that checks two iterators for inequality
						return (this->here != rhs.here);
					}
				}; // end Const_SSLL_Iter

		typedef std::size_t size_type;
		typedef T value_type;
		typedef SSLL_Iter iterator;
		typedef Const_SSLL_Iter const_iterator;

		iterator begin() { return SSLL_Iter(head); }  //This returns the iterator's pointer to start of the list
		iterator end() { return SSLL_Iter(NULL); }   //This returns the iterator's pointer to end of the list
		const_iterator begin() const { return Const_SSLL_Iter(head); } //This returns the const iterator's pointer to start of the list
		const_iterator end() const { return Const_SSLL_Iter(NULL); }   //This returns the const iterator's pointer to end of the list
	}; //end class SSLL
} // end namespace cop3530
#endif // _SSLL_H_