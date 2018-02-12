#ifndef __NODE__
#define __NODE__

class Node
{
public:
	Node(void * memPtr, Node * prev, Node * next);

	inline void * GetVal() const;
	inline Node * GetPrev() const;
	inline Node * GetNext() const;
	inline void SetPrev(Node* p);
	inline void SetNext(Node* n);

private:
	void* _memPtr = nullptr;
	Node* _prev = nullptr;
	Node* _next = nullptr;
};

inline Node::Node(void * memPtr, Node * prev, Node * next): _memPtr(memPtr), _prev(prev), _next(next) {}

inline void* Node::GetVal() const
{
	return _memPtr;
}

inline Node* Node::GetPrev() const
{
	return _prev;
}

inline Node* Node::GetNext() const
{
	return _next;
}

inline void Node::SetPrev(Node* p)
{
	_prev = p;
}

inline void Node::SetNext(Node* n)
{
	_next = n;
}
#endif