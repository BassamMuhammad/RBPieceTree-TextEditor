#include "rb_piece_tree.hpp"
#include <iostream>
using namespace std;
RBPieceTree::RBPieceTree(){pieceTable = new PieceTable();}

Node* RBPieceTree::makeNewNode(int startIndex, int startOffset, int endIndex, int endOffset, int bufferIndex){
    BufferPosition* start = new BufferPosition(startIndex, startOffset);
    BufferPosition* end = new BufferPosition(endIndex, endOffset);
    return new Node(start, end, bufferIndex);
}

void RBPieceTree::invertColor(Node* node){node->setRed(!node->isRed());}

void RBPieceTree::leftRotation(Node* lowestNode){
    Node* parent = lowestNode->getParent();
    Node* grandParent = parent->getParent();
    Node* grandGrandParent = grandParent->getParent();

    grandParent->setRightChild(parent->getLeftChild());
    parent->setLeftChild(grandParent);

    //if grandGrandParent is not NULL break its connection with grandParent
    //and make parent its child
    if(grandGrandParent) {
        if(grandParent == grandGrandParent->getLeftChild()) grandGrandParent->setLeftChild(parent);
        else grandGrandParent->setRightChild(parent);
    }

    //correct parents
    if(grandParent->getRightChild()) grandParent->getRightChild()->setParent(grandParent);
    parent->setParent(grandGrandParent);
    grandParent->setParent(parent);

    //invert colors
    invertColor(parent);
    invertColor(grandParent);

    pieceTable->fixLeftSubTreeProps(lowestNode);
    grandParent->getRightChild() ? pieceTable->fixLeftSubTreeProps(grandParent->getRightChild())
                                 : pieceTable->fixLeftSubTreeProps(grandParent);
    pieceTable->fixRootNode();
}

void RBPieceTree::rightRotation(Node* lowestNode){
    Node* parent = lowestNode->getParent();
    Node* grandParent = parent->getParent();
    Node* grandGrandParent = grandParent->getParent();

    grandParent->setLeftChild(parent->getRightChild());
    parent->setRightChild(grandParent);

    //if grandGrandParent is not NULL break its connection with grandParent
    //and make parent its child
    if(grandGrandParent) {
        if(grandParent == grandGrandParent->getLeftChild()) grandGrandParent->setLeftChild(parent);
        else grandGrandParent->setRightChild(parent);
    }

    //correct parents
    if(grandParent->getLeftChild()) grandParent->getLeftChild()->setParent(grandParent);
    parent->setParent(grandGrandParent);
    grandParent->setParent(parent);

    //invert colors
    invertColor(parent);
    invertColor(grandParent);

    pieceTable->fixLeftSubTreeProps(lowestNode);
    grandParent->getLeftChild() ? pieceTable->fixLeftSubTreeProps(grandParent->getLeftChild())
                                : pieceTable->fixLeftSubTreeProps(grandParent);

    pieceTable->fixRootNode();
}

void RBPieceTree::leftRightRotation(Node* lowestNode){
    Node* parent = lowestNode->getParent();
    Node* grandParent = parent->getParent();

    parent->setRightChild(lowestNode->getLeftChild());
    lowestNode->setLeftChild(parent);
    grandParent->setLeftChild(lowestNode);

    //correct Parents
    if(parent->getRightChild()) parent->getRightChild()->setParent(parent);
    lowestNode->setParent(grandParent);
    parent->setParent(lowestNode);

    rightRotation(parent);
}

void RBPieceTree::rightLeftRotation(Node* lowestNode){
    Node* parent = lowestNode->getParent();
    Node* grandParent = parent->getParent();

    parent->setLeftChild(lowestNode->getRightChild());
    lowestNode->setRightChild(parent);
    grandParent->setRightChild(lowestNode);

    //correct Parents
    if(parent->getLeftChild()) parent->getLeftChild()->setParent(parent);
    lowestNode->setParent(grandParent);
    parent->setParent(lowestNode);

    leftRotation(parent);
}

void RBPieceTree::fixUncleRed(Node* lowestNode){
    lowestNode->getParent()->setRed(false);
    lowestNode->setUncleColor(false);

    Node* grandParent = lowestNode->getParent()->getParent();
    if(grandParent != pieceTable->getRootNode()){
        grandParent->setRed(true);
        fixRBTOnInsert(grandParent);
    }
}

void RBPieceTree::decideRotations(Node* lowestNode){
    Node* parent = lowestNode->getParent();
    Node* grandParent = parent->getParent();
    if(parent == grandParent->getLeftChild()){
        if(lowestNode == parent->getLeftChild()) {rightRotation(lowestNode);}
        else {leftRightRotation(lowestNode);}
    }
    else if(parent == grandParent->getRightChild()){
        if(lowestNode == parent->getRightChild()) {leftRotation(lowestNode);}
        else {rightLeftRotation(lowestNode);}
    }
}

void RBPieceTree::fixRBTOnInsert(Node* node){
    if(node->getParent() && node->getParent()->isRed()){
        if(node->isUncleRed()){
            fixUncleRed(node);
        }
        else{
            decideRotations(node);
        }
    }
}

void RBPieceTree::insertNode(Node* node, int textLength, int lineFeedsSize){
    int startIndex = lineFeedsSize > 0 ? 0 : -1;
    int endIndex = lineFeedsSize > 0 ? lineFeedsSize - 1 : -1;
    if(!node){		//if root is NULL
        pieceTable->setRootNode(makeNewNode(startIndex, 0, endIndex,textLength - 1, pieceTable->getBuffers().size()-1));		//make new Node and make it root
        pieceTable->getRootNode()->setRed(false);
    }
    else{
        //move to right most node
        while(node->getRightChild()){
            node = node->getRightChild();
        }
        node->setRightChild(makeNewNode(startIndex, 0, endIndex,textLength - 1, pieceTable->getBuffers().size() - 1));		//add new node to its right
        node->getRightChild()->setParent(node);
        fixRBTOnInsert(node->getRightChild());
    }
}
int RBPieceTree::addTextToBuffer(string text){
    vector<int> lineFeeds;
    for(unsigned long long i = 0;i < text.size();i++){
        if(text[i] == '\n')	lineFeeds.push_back(i);
    }
    pieceTable->addBuffer(Buffer(text,lineFeeds));
    return lineFeeds.size();
}

void RBPieceTree::insertText(string text){
    int lineFeedSize = addTextToBuffer(text);
    insertNode(pieceTable->getRootNode(), text.length(), lineFeedSize);
}

void RBPieceTree::fixChildrenRed(Node* node){
    decideRotations(node);
    node->setRed(false);
}

void RBPieceTree::fixRBTOnDel(Node* node){
    if(node && !node->isRed() && node != pieceTable->getRootNode()){
        if(!node->isSiblingRed()){//if sibling is black
            //if children of sibling are also black
            Node* siblingRightChild = node->getSibling()->getRightChild();
            Node* siblingLeftChild = node->getSibling()->getLeftChild();
            if((!siblingRightChild || !siblingRightChild->isRed()) && (!siblingLeftChild || !siblingLeftChild->isRed())){
                bool recurse = !node->getParent()->isRed();
                node->getParent()->setRed(false);
                node->setSiblingColor(true);
                if(recurse) fixRBTOnDel(node->getParent());
            }
            else{
                if(node->getParent()->getLeftChild() == node){
                    if(siblingRightChild && siblingRightChild->isRed()){
                        fixChildrenRed(siblingRightChild);
                    }
                    else{
                        fixChildrenRed(siblingLeftChild);
                    }
                }
                else{
                    if(siblingLeftChild && siblingLeftChild->isRed()){
                        fixChildrenRed(siblingLeftChild);
                    }
                    else{
                        fixChildrenRed(siblingRightChild);
                    }
                }
            }
        }
        else{//if sibling is red
            if(node->getParent()->getLeftChild() == node){
                leftRotation(node->getSibling()->getRightChild());
            }
            else{
                rightRotation(node->getSibling()->getLeftChild());
            }
            fixRBTOnDel(node);
        }
    }
}

void RBPieceTree::deleteNode(Node* node){
    if(node->getLeftChild() && node->getRightChild()){
        //get in-order successor
        Node* temp = node->getRightChild();
        while(temp->getLeftChild()){
            temp = temp->getLeftChild();
        }
        node->editValues(temp->getBufferIndex(),temp->getStart(),temp->getEnd());
        deleteNode(temp);
    }
    else{
        Node* child = node->getLeftChild() ? node->getLeftChild() : node->getRightChild();
        if(child){
            node->editValues(child->getBufferIndex(),child->getStart(),child->getEnd());
            fixRBTOnDel(child);
            node->setLeftChild(NULL);
            node->setRightChild(NULL);
            delete child;
        }
        else{
            fixRBTOnDel(node);
            if(node->getParent()) node->getParent()->getLeftChild() == node ? node->getParent()->setLeftChild(NULL) : node->getParent()->setRightChild(NULL);
            node->setStart(NULL);
            node->setEnd(NULL);
            delete node;
        }
    }
}

void RBPieceTree::updateNode(Node* node, int splitOffset, string text){
    int lineFeedSize = addTextToBuffer(text);
    int startIndex = lineFeedSize > 0 ? 0 : -1;
    int endIndex = lineFeedSize > 0 ? lineFeedSize - 1 : -1;
    BufferPosition* start = new BufferPosition(startIndex, 0);
    BufferPosition* end = new BufferPosition(endIndex, text.size() - 1);
    Node* middleNode;
    if(node->getStart()->getOffset() > splitOffset){//letter entered before this node
        middleNode = node->setAndGetInOrderPredecessor(start,end,pieceTable->getBuffers().size() - 1);
    }
    else if(node->getEnd()->getOffset() < splitOffset){//letter entered after this node
        middleNode = node->setAndGetInOrderSuccessor(start,end,pieceTable->getBuffers().size() - 1);
    }
    else{//letter entered b/w this node
        splitNode(node, splitOffset, false);
        middleNode = node->setAndGetInOrderSuccessor(start,end,pieceTable->getBuffers().size() - 1);
    }
    fixRBTOnInsert(middleNode);
    pieceTable->fixLeftSubTreeProps(middleNode);
}

void RBPieceTree::splitNode(Node* node, int splitOffset, bool fromDel){
    vector<int> lineFeeds = pieceTable->getBuffers().at(node->getBufferIndex()).getLineFeeds();
    unsigned long long index = -1;
    for(unsigned long long i = 0; i < lineFeeds.size(); i++){
        if(fromDel){
            if(lineFeeds[i] < splitOffset){
                index = i;
            }
            else break;
        }
        else{
            if(lineFeeds[i] <= splitOffset){
                index = i;
            }
            else break;
        }
    }
    int nEndIndex = node->getEnd()->getIndex();
    int nEndOffset = node->getEnd()->getOffset();
    if(fromDel) {node->editEnd(index, splitOffset - 1);}
    else {node->editEnd(index, splitOffset);}

    int nStartIndex = index + 1 <= lineFeeds.size() - 1 ? index + 1 : index;
    BufferPosition* start = new BufferPosition(nStartIndex, splitOffset+1);
    BufferPosition* end = new BufferPosition(nEndIndex, nEndOffset);
    Node* successor = node->setAndGetInOrderSuccessor(start, end, node->getBufferIndex());
    fixRBTOnInsert(successor);
    pieceTable->fixLeftSubTreeProps(successor);
}

void RBPieceTree::helperDelLetter(Node* node, int index){
    if(node->getEnd()->getOffset() == node->getStart()->getOffset()){
        if(node == pieceTable->getRootNode()){
            deleteNode(node);
            pieceTable->setRootNode(NULL);
        }
        else deleteNode(node);

    }
    else{
        Buffer buffer = pieceTable->getBuffers().at(node->getBufferIndex());
        string text = buffer.getText();
        if(index < 0){
            if(text.at(node->getEnd()->getOffset() ) == '\n'){
                node->editEnd(node->getEnd()->getIndex() - 1 , node->getEnd()->getOffset() - 1);
            }
            else node->editEnd(node->getEnd()->getIndex(), node->getEnd()->getOffset() - 1);
        }
        else if(index == 0){
            int startIndex = node->getStart()->getIndex() < 0 ? -2 : node->getStart()->getIndex();
            vector<int> lineFeeds = buffer.getLineFeeds();
            if(text.at(node->getStart()->getOffset() ) == '\n' && lineFeeds.size() > (unsigned long long)startIndex + 1){
                node->editStart(startIndex + 1 , node->getStart()->getOffset() + 1);
            }
            else node->editStart(startIndex, node->getStart()->getOffset() + 1);
        }
        else if(index > 0){
            splitNode(node, node->getStart()->getOffset() + index - 1, true);
        }
    }

}

void RBPieceTree::searchNode(Node* node, int column, string text){
    if(node){
        int totalTextLength = node->getLeftSubTreeTextLength() + node->getTextLength();
        int index = column - 1 - node->getLeftSubTreeTextLength();
        if(totalTextLength > column-1){
            if(node->getLeftSubTreeTextLength() < column - 1){
                if(text == "") {helperDelLetter(node,index);}
                else {updateNode(node, node->getStart()->getOffset() + index - 2, text);}
            }

            else searchNode(node->getLeftChild(),column,text);
        }
        else if(totalTextLength < column - 1){
            column -= totalTextLength;
            searchNode(node->getRightChild(),column,text);
        }
        else if(totalTextLength == column - 1){
            if(text == "") {helperDelLetter(node,-1);}
            else {updateNode(node, node->getStart()->getOffset() + index - 2, text);}
        }
    }
}

void RBPieceTree::deleteLetter(int column){
    searchNode(pieceTable->getRootNode(), column, "");
}

void RBPieceTree::updateText(string text, int column){
    searchNode(pieceTable->getRootNode(), column + 1, text);
}

string RBPieceTree::helperGetLine(Node* node, int row){
    if(node){
        string lineText = "";
        int totalLineFeeds = node->getLeftSubTreeLineFeedCount() + node->getLineFeedCount();
        Buffer buffer = pieceTable->getBuffers().at(node->getBufferIndex());
        string text = buffer.getText();
        if(totalLineFeeds > row - 1){
            lineText += helperGetLine(node->getLeftChild(), row);
            if(node->getLeftSubTreeLineFeedCount() <= row - 1) {
                int index = row - 2 - node->getLeftSubTreeLineFeedCount();
                int startingPoint = index < 0 ? node->getStart()->getOffset() : buffer.getLineFeeds().at(index)  + 1;
                int endingPoint = buffer.getLineFeeds().size() <= (unsigned long long)index + 1 ? node->getEnd()->getOffset()
                                                                         : buffer.getLineFeeds().at(index + 1) + 1;
                lineText += text.substr(startingPoint, endingPoint);
            }
        }
        else if(totalLineFeeds < row - 1){
            row -= totalLineFeeds;
            lineText += helperGetLine(node->getRightChild(), row);
        }
        else if(totalLineFeeds == row - 1){
            lineText += helperGetLine(node->getLeftChild(), row);//endIndex,endOffset
            int startingPoint = node->getEnd()->getIndex() >= 0 ? buffer.getLineFeeds().at(node->getEnd()->getIndex())+1
                                                                 : node->getStart()->getOffset();
            lineText += text.substr(startingPoint, node->getEnd()->getOffset() + 1 - startingPoint);
            row -= totalLineFeeds;
            lineText += helperGetLine(node->getRightChild(), row);
        }
        return lineText;
    }
    return "";
}
string RBPieceTree::helperGetText(Node* node){
    if(!node) return "";
        string text = "";
        text += helperGetText(node->getLeftChild());
        string t = pieceTable->getBuffers().at(node->getBufferIndex()).getText();
        text += t.substr(node->getStart()->getOffset(), node->getEnd()->getOffset() - node->getStart()->getOffset() + 1);
        text += helperGetText(node->getRightChild());
        return text;
}
string RBPieceTree::getText(){
    return helperGetText(pieceTable->getRootNode());

}

string RBPieceTree::getLine(int row){
    return helperGetLine(pieceTable->getRootNode(),row);
}

//void RBPieceTree::undo(){
//    switch (undoIndex) {
//    case 1:
//        deleteNode();
//        break;

//    case 2:
//        insertNode();
//        break;

//    case 3:
//        deUpdate();
//        break;

//    case 4:
//        updateNode();

//    }
//}

