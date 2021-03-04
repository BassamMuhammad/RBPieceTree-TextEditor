#ifndef RB_PIECE_TREE_HPP
#define RB_PIECE_TREE_HPP
#include "piece_table.hpp"
#include "cursor_position.hpp"

class RBPieceTree{
    private:
        PieceTable* pieceTable;

        //helper-methods
        Node* makeNewNode(int startIndex, int startOffset, int endIndex, int endOffset, int bufferIndex);
        void insertNode(Node* node, int textLength, int lineFeedsSize);
        void invertColor(Node* node);
        void leftRotation(Node* lowestNode);
        void rightRotation(Node* lowestNode);
        void leftRightRotation(Node* lowestNode);
        void rightLeftRotation(Node* lowestNode);
        void fixUncleRed(Node* lowestNode);
        void decideRotations(Node* lowestNode);
        void fixChildrenRed(Node* node);
        void fixRBTOnInsert(Node* node);
        void fixRBTOnDel(Node* node);
        void searchNode(Node* node, int column, string text);
        void helperDelLetter(Node* node, int index);
        void splitNode(Node* node, int splitOffset, bool fromDel);
        int addTextToBuffer(string text);
        void deleteNode(Node* node);
        void updateNode(Node* node, int splitOffset, string text);
        void helperPrint(Node* node);
        string helperGetLine(Node* node, int row);
        string helperGetText(Node* node);

    public:
        //constructor
        RBPieceTree();

        void insertText(string text);               //insert text at end
        void deleteLetter(int column);              //delete letter
        void updateText(string text, int column);   //insert text at a position
        string getText();                           //get all the text
        string getLine(int row);                    //get a line of text


};
#endif
