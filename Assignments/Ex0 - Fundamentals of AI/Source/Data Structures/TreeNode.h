#include "../Data Structures/LinkedList.h"


// TreeNode class should go in the "ufl_cap4053::fundamentals" namespace!
namespace ufl_cap4053 { namespace fundamentals {


	template<typename T> class TreeNode {
	private:
		T val;
		TreeNode** children;
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
			return children[index];
		}
		TreeNode<T>* getChild(size_t index) const {
			return children[index];
		}
		void addChild(TreeNode<T>* child) {
			TreeNode<T>** newChildren = new TreeNode<T>[childCount+1];
			// im sure you could memcopy this but im a little rusty
			for (int i = 0; i < childCount; i++) {
				newChildren[i] = children[i];
			}
			newChildren[childCount] = child;
			
			delete[] children;
			children = newChildren;
			
			childCount++;
		}
		TreeNode<T>* removeChild(size_t index) {
			TreeNode<T>** newChildren = new TreeNode<T>[childCount - 1];
			// j runs alongside but skips over the removed element
			int j = 0;
			for (int i = 0; i < childCount; i++) {
				if (i == index)
					j++;
				newChildren[i] = children[j];
				j++;
			}
			TreeNode<T>* ret = &children[index];

			delete[] children;
			children = newChildren;

			childCount--;

			return ret;
		}
		//takes advantage of the linkedlist class
		void breadthFirstTraverse(void (*dataFunction)(const T)) const {
			LinkedList<TreeNode*> nodeQueue;
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
			for (int i = 0; i < childCount; i++) {
				children[i]->preOrderTraverse(dataFunction);
			}
		}
		void postOrderTraverse(void (*dataFunction)(const T)) const {
			for (int i = 0; i < childCount; i++) {
				children[i]->postOrderTraverse(dataFunction);
			}
			dataFunction(val);
		}
	};


}}  // namespace ufl_cap4053::fundamentals
