#ifndef _NODE_H
#define _NODE_H

#include <Trackable.h>

const int BAD_NODE_ID = -1;
#define NODE_ID int

class Node:public Trackable
{
public:
	Node( const NODE_ID& id );
	Node();
	~Node();

	const NODE_ID& getId() const {return mId;};

	//getters
	double getDistToSource() const { return mDistanceToSource; }
	Node* getPrevNode() const { return mPrev; }

	//setters
	void setDistToSource(double dist) { mDistanceToSource = dist; }
	void setPrevNode(Node* prev) { mPrev = prev; }

private:
	const NODE_ID mId;
	double mDistanceToSource;
	Node* mPrev;
};

#endif