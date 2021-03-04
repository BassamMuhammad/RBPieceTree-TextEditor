#include "node.hpp"
#include <cstddef>

Node::Node(BufferPosition* nStart, BufferPosition* nEnd, int nBufferIndex){			
	leftChild = NULL;					
	rightChild = NULL;
	parent = NULL;
	start = nStart;
	end = nEnd;
	bufferIndex = nBufferIndex;
	leftSubTreeTextLength = 0;
    leftSubTreeLineFeedCount = 0;
	red = true;
}

Node::~Node(){
    delete start;
    delete end;
}

Node* Node::getLeftChild(){return leftChild;}

Node* Node::getRightChild(){return rightChild;}

Node* Node::getParent(){return parent;}

BufferPosition* Node::getStart(){return start;}

BufferPosition* Node::getEnd(){return end;}
	
int Node::getBufferIndex(){return bufferIndex;}

int Node::getLeftSubTreeTextLength(){return leftSubTreeTextLength;}

int Node::getLeftSubTreeLineFeedCount(){return leftSubTreeLineFeedCount;}

bool Node::isRed(){return red;}

int Node::getLineFeedCount(){return end->getIndex() < 0 ? 0 : end->getIndex() - start->getIndex() + 1;}

int Node::getTextLength(){return end->getOffset() - start->getOffset() + 1;}

void Node::setLeftChild(Node* nLeftChild){leftChild = nLeftChild;}

void Node::setRightChild(Node* nRightChild){rightChild = nRightChild;}

void Node::setParent(Node* nParent){parent = nParent;}

void Node::setBufferIndex(int nBufferIndex){bufferIndex = nBufferIndex;}

void Node::setStart(BufferPosition* nStart){start = nStart;}

void Node::setEnd(BufferPosition* nEnd){end = nEnd;}

void Node::setLeftSubTreeTextLength(int nLeftSubTreeTextLength){leftSubTreeTextLength = nLeftSubTreeTextLength;}

void Node::setLeftSubTreeLineFeedCount(int nLeftSubTreeLineFeedCount){leftSubTreeLineFeedCount = nLeftSubTreeLineFeedCount;}

void Node::setRed(bool nRed){red = nRed;}

bool Node::isRightInAncestory(){return getFirstRightAncestor() != NULL;}

Node* Node::getFirstRightAncestor(){
    Node* node = this;
    while (node->parent) {
        if(node->parent->rightChild == node) return node;
        else node = node->parent;
    }
    return NULL;
}

Node* Node::getSibling(){
    if(parent){
       return parent->leftChild == this ? parent->rightChild : parent->leftChild;
    }
    else return NULL;
}

Node* Node::getUncle() {return parent ? parent->getSibling() : NULL;}

bool Node::isSiblingRed() {return getSibling() && getSibling()->isRed();}


bool Node::isUncleRed() {return getUncle() && getUncle()->isRed();}

void Node::setSiblingColor(bool red){
    Node* sibling = getSibling();
    if(sibling) sibling->setRed(red);
}

void Node::setUncleColor(bool red){
    Node* uncleNode = getUncle();
    if(uncleNode) {uncleNode->setRed(red);}
}

void Node::editStart(int nIndex, int nOffset){
    start->setIndex(nIndex);
    start->setOffset(nOffset);
}

void Node::editEnd(int nIndex, int nOffset){
    end->setIndex(nIndex);
    end->setOffset(nOffset);
}

void Node::editValues(int bufferIndex, BufferPosition* nStart, BufferPosition* nEnd){
    this->setBufferIndex(bufferIndex);
    editStart(nStart->getIndex(),nStart->getOffset());
    editEnd(nEnd->getIndex(),nEnd->getOffset());
}

Node* Node::setAndGetInOrderPredecessor(BufferPosition* nStart, BufferPosition* nEnd, int bufferIndex){
    Node* node = getLeftChild();
    if(!node){
        setLeftChild(new Node(nStart,nEnd,bufferIndex));
        getLeftChild()->setParent(this);
        return getLeftChild();
    }
    else{
        while(node->getRightChild()){
            node = node->getRightChild();
        }
        node->setRightChild(new Node(nStart,nEnd,bufferIndex));
        node->getRightChild()->setParent(node);
        return node;
    }
}
Node* Node::setAndGetInOrderSuccessor(BufferPosition* nStart, BufferPosition* nEnd, int bufferIndex){
    Node* node = getRightChild();
    if(!node){
        setRightChild(new Node(nStart,nEnd,bufferIndex));
        getRightChild()->setParent(this);
        return getRightChild();
    }
    else{
        while(node->getLeftChild()){
            node = node->getLeftChild();
        }
        node->setLeftChild(new Node(nStart,nEnd,bufferIndex));
        node->getLeftChild()->setParent(node);
        return node;
    }
}
