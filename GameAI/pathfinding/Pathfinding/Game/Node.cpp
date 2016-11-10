#include "Node.h"

Node::Node()
:mId(BAD_NODE_ID), mPrev(NULL), mDistanceToSource(-1)
{
}

Node::Node( const NODE_ID& id )
:mId(id), mPrev(NULL), mDistanceToSource(std::numeric_limits<double>::infinity())
{
}

Node::~Node()
{
}