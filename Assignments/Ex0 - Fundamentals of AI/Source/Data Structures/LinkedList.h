//#include <iostream>

// LinkedList class should go in the "ufl_cap4053::fundamentals" namespace!
namespace ufl_cap4053 { namespace fundamentals {


	template<typename T> class LinkedList {
	private:
		struct ListNode {
			T value;
			ListNode* prev;
			ListNode* next;

			ListNode() {}
			ListNode(T val, ListNode* pr = nullptr, ListNode* nx = nullptr) {
				value = val;
				prev = pr;
				next = nx;
			}
		};
		
		ListNode* startptr;
		ListNode* endptr;


	public:
		struct Iterator {
		public:
			ListNode* curr;

			Iterator() { curr = startptr; }
			Iterator(ListNode* node) { curr = node; }

			T operator*() const {
				return curr->value;
			}
			Iterator& operator++() {
				curr = curr->next;
				return *this;
			}

			bool operator==(Iterator const& rhs) {
				return (rhs.curr == curr);
			}
			bool operator!=(Iterator const& rhs) {
				return !(rhs.curr == curr);
			}

		};

		LinkedList() { startptr = endptr = nullptr; }

		Iterator begin() const { return Iterator(startptr); }
		Iterator end() const { return Iterator(nullptr); }
		bool isEmpty() const { return startptr == nullptr; }
		T getFront() const { return startptr->value; }
		T getBack() const { return endptr->value; }

		void enqueue(T element) {
			ListNode* node = new ListNode(element, endptr, nullptr);
			// attach to end of list
			if (endptr != nullptr) {
				endptr->next = node;
			}
			// set as new end
			endptr = node;

			// set as start if only node in list
			if (startptr == nullptr) {
				startptr = node;
			}

		}
		//  all removals pipe through the same function. this is marginally slower
		// but it means i only have to implement removal (and associated edge cases) once
		void dequeue() {
			removebyit(startptr);
		}
		void pop() {
			if (endptr != nullptr) {
				removebyit(endptr);
			}
		}
		// yeah im wrong for this
		void clear() {
			while (!isEmpty()) {
				pop();
			}
		}
		// not asked for but makes contains()/remove() a bit easier
		Iterator find(T element) const {
			Iterator it(startptr);
			while (it != nullptr) {
				if (*it == element) { return it; }
				++it;
			}
			return nullptr;
		}
		bool contains(T element) const {
			return (find(element) != nullptr);
		}
		void remove(T element) {
			Iterator at = find(element);
			
			removebyit(at);
		}
		// the aforementioned true removal function
		void removebyit(Iterator at) {
			// easy escape case
			if (at == nullptr) { return; }

			// test if first element
			if (at.curr->prev == nullptr) {
				startptr = at.curr->next;
			}
			else {
				at.curr->prev->next = at.curr->next;
			}
			// test if last element
			if (at.curr->next == nullptr) {
				endptr = at.curr->prev;
			}
			else {
				at.curr->next->prev = at.curr->prev;
			}

			delete at.curr;
		}

		//void printState() {
		//	std::cout << "\n=Startpointer exists: " << (startptr != nullptr) << "\n=Endpointer exists: " << (startptr != nullptr);
		//}
	};


} }  // namespace ufl_cap4053::fundamentals
