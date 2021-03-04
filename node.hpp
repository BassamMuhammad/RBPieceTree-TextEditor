#ifndef NODE_HPP
#define NODE_HPP
#include "buffer_position.hpp"

class Node{
    private:
        Node* leftChild;                //leftChild of node
        Node* rightChild;               //rightChild of node
        Node* parent;                   //parent of node
        BufferPosition* start;          //start pointing to range of text in Buffer
        BufferPosition* end;			//end pointing to range of text in Buffer
        int bufferIndex;                //index in PieceTable.buffers
        int leftSubTreeTextLength;      //total length of text in left sub tree
        int leftSubTreeLineFeedCount;	//total line-feed count in left sub tree
        bool red;                       //store color for red-black tree (red = true, black = false)

        //helper-methods
        Node* getUncle();

    public:
        //constructor
        Node(BufferPosition* nStart, BufferPosition* nEnd, int nBufferIndex);

        //destructor
        ~Node();

        //getters
        Node* getLeftChild();
        Node* getRightChild();
        Node* getParent();
        BufferPosition* getStart();
        BufferPosition* getEnd();
        int getBufferIndex();
        int getLeftSubTreeTextLength();
        int getLeftSubTreeLineFeedCount();
        bool isRed();

        //setters
        void setLeftChild(Node* nLeftChild);
        void setRightChild(Node* nRightChild);
        void setParent(Node* nParent);
        void setBufferIndex(int nBufferIndex);
        void setStart(BufferPosition* nStart);
        void setEnd(BufferPosition* nEnd);
        void setLeftSubTreeTextLength(int nLeftSubTreeTextLength);
        void setLeftSubTreeLineFeedCount(int nLeftSubTreeLineFeedCount);
        void setRed(bool nRed);

        //other-methods
        Node* getFirstRightAncestor();
        int getLineFeedCount();
        int getTextLength();
        bool isRightInAncestory();        
        Node* getSibling();
        bool isSiblingRed();
        void setSiblingColor(bool red);
        bool isUncleRed();
        void setUncleColor(bool red);
        void editStart(int nIndex, int nOffset);
        void editEnd(int nIndex, int nOffset);
        void editValues(int bufferIndex, BufferPosition* nStart, BufferPosition* nEnd);
        Node* setAndGetInOrderPredecessor(BufferPosition* nStart, BufferPosition* nEnd, int bufferIndex);
        Node* setAndGetInOrderSuccessor(BufferPosition* nStart, BufferPosition* nEnd, int bufferIndex);
};

#endif
