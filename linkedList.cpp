//linked list with dummy node cycle mode
#pragma once
#include <ostream>

template <class T>
class LinkedLinearList{
private:
		class Node{
		public:
			T	mData;
			Node*	mPrev;
			Node*	mNext;
		};

public:
	class Iterator{
	public:
		//constructors:
		Iterator ()
			:mCurNode (NULL){}

		Iterator (const Iterator &other)
			:mCurNode (other.mCurNode){}
		
		Iterator (Node* node)
			:mCurNode (node){}
		
		//overloading operators:
		virtual Iterator& operator++(){ // preincrement
			mCurNode = mCurNode->mNext;
			return *this;
		}

		virtual Iterator operator++(int dummy){ // postincrement
			Iterator temp = Iterator(mCurNode);
			mCurNode = mCurNode->mNext;
			return temp;
		}

		virtual Iterator& operator--(){ // predecrement
			mCurNode = mCurNode->mPrev;
			return *this;
		}

		virtual Iterator operator--(int dummy){ // postdecrement
			Iterator temp = Iterator(mCurNode);
			mCurNode = mCurNode->mPrev;
			return temp;
		}

		bool operator!=(const Iterator& right)const {
			return (mCurNode) != ((right.mCurNode));
		}

		bool operator==(const Iterator& right)const {
			return (mCurNode) == ((right.mCurNode));
		}

		T* operator->() const {
			return &(mCurNode->mData);
		}

		T& operator*() const {
			return (mCurNode->mData);
		}

		friend class LinkedLinearList;
	private:
		//const LinkedLinearList<T> *mLinkedList;
		Node *mCurNode;
	};

	LinkedLinearList(void){
		mSize = 0;
		mHeaderNode = new Node();
		mHeaderNode->mNext = mHeaderNode;
		mHeaderNode->mPrev = mHeaderNode;
	}

	virtual ~LinkedLinearList(void) {
		Node *n, *nn; 
		for (n = mHeaderNode->mNext; n != mHeaderNode;){
			nn = n->mNext;
			delete n;
			n = nn;
		}
		delete mHeaderNode;
	}

public:
	virtual Iterator begin() const {
		return Iterator(mHeaderNode->mNext);
	}

	virtual Iterator end() const {
		return Iterator(mHeaderNode);
	}

	virtual Iterator rbegin() const {
		return Iterator(mHeaderNode->mPrev);
	}

	virtual Iterator rend() const {
		return Iterator(mHeaderNode);
	}

	// The returned iterator would point to the inserted element.
	virtual Iterator insert(Iterator it, const T& data) {
		Node *newnode = new Node();
		newnode->mData = data;
		Node *lastnode = (it.mCurNode);
		newnode->mPrev = lastnode;
		newnode->mNext = lastnode->mNext;
		lastnode->mNext->mPrev = newnode;
		lastnode->mNext = newnode;
		it++;
		mSize++;
		return it;
	}

	// The returned iterator would point to the element after the removed one.
	virtual Iterator remove(Iterator it) {
		Node *curnode = (it.mCurNode);
		curnode->mPrev->mNext = curnode->mNext;
		curnode->mNext->mPrev = curnode->mPrev;

		it++;
		mSize--;

		delete curnode;
		return it;
	}

	virtual int size() const {
		return mSize;
	};

private:
	Node* mHeaderNode;
	int mSize;
};

template <class T>
std::ostream& operator<<(std::ostream& os, const LinkedLinearList<T>& ll){
	LinkedLinearList<T>::Iterator itr;

	for (itr = ll.begin(); itr != ll.end(); itr++)
		os << *itr << "\t";
	os << "\n";
	return os;
}
