#include "piece_table.hpp"

Node* PieceTable::getRootNode(){return rootNode;}

void PieceTable::setRootNode(Node* nRootNode){rootNode = nRootNode;}

vector<Buffer> PieceTable::getBuffers(){return buffers;}

void PieceTable::addBuffer(Buffer buffer){buffers.push_back(buffer);}

void PieceTable::fixRootNode(){
    if(rootNode){
        rootNode->setRed(true);
        Node* node = rootNode;
        while(node->getParent()){
            node = node->getParent();
        }
        node->setRed(false);
        rootNode = node;
    }
}

void PieceTable::fixLeftSubTreeProps(Node* node){
    if(node){
        Node* child = node->getLeftChild();
        if(child){
            int leftSubtreeTextLength = child->getLeftSubTreeTextLength() + child->getTextLength();
            int leftSubtreeLineCount = child->getLeftSubTreeLineFeedCount() + child->getLineFeedCount();
            //add props of right child of leftChild and its leftSubtree props and move right
            while(child && child->getRightChild()){
                child = child->getRightChild();
                leftSubtreeTextLength += child->getLeftSubTreeTextLength() + child->getTextLength();
                leftSubtreeLineCount += child->getLeftSubTreeLineFeedCount() + child->getLineFeedCount();
            }
            node->setLeftSubTreeLineFeedCount(leftSubtreeLineCount);
            node->setLeftSubTreeTextLength(leftSubtreeTextLength);
        }
        else{
            node->setLeftSubTreeLineFeedCount(0);
            node->setLeftSubTreeTextLength(0);
        }

        fixLeftSubTreeProps(node->getParent());
    }
}
