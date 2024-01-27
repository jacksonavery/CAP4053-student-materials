#include "../Data Structures/LinkedList.h"


// TreeNode class should go in the "ufl_cap4053::fundamentals" namespace!
namespace ufl_cap4053 { namespace fundamentals {


	template<typename T> class TreeNode {
	private:
		T val;
		// this might more easily be a std::vector but im not sure we're allowed to use those
		LinkedList<TreeNode*> childs;
		size_t childCount = 0;

	public:
		TreeNode() { val = nullptr; };
		TreeNode(T element) { val = element; }

		const T& getData() const {
			return val;
		}
		size_t getChildCount() const {
			return childCount;
		}
		TreeNode<T>* getChild(size_t index) {
			auto it = childs.begin();
			for (int i = 0; i < index; i++) {
				++it;
			}

			return *it;
		}
		TreeNode<T>* getChild(size_t index) const {
			auto it = childs.begin();
			for (int i = 0; i < index; i++) {
				++it;
			}

			return *it;
		}
		void addChild(TreeNode<T>* child) {
			childs.enqueue(child);
			
			childCount++;
		}
		TreeNode<T>* removeChild(size_t index) {
			TreeNode<T>* ret = childs.remove_at(index, false);

			childCount--;

			return ret;
		}
		//takes advantage of the linkedlist class
		void breadthFirstTraverse(void (*dataFunction)(const T)) const {
			LinkedList<TreeNode*> nodeQueue;
			// initialize the queue.
			for (int i = 0; i < getChildCount(); i++) {
				nodeQueue.enqueue(getChild(i));
			}
			dataFunction(val);

			for (auto itr = nodeQueue.begin(); itr != nodeQueue.end(); ++itr) {
				TreeNode* current = (itr.curr->value);
				for (int i = 0; i < current->getChildCount(); i++) {
					nodeQueue.enqueue(current->getChild(i));
				}
				dataFunction(current->val);
			}

		}
		void preOrderTraverse(void (*dataFunction)(const T)) const {
			dataFunction(val);
			for (auto itr = childs.begin(); itr != childs.end(); ++itr) {
				(*itr)->preOrderTraverse(dataFunction);
			}
		}
		void postOrderTraverse(void (*dataFunction)(const T)) const {
			for (auto itr = childs.begin(); itr != childs.end(); ++itr) {
				(*itr)->postOrderTraverse(dataFunction);
			}
			dataFunction(val);
		}
	};


}}  // namespace ufl_cap4053::fundamentals
