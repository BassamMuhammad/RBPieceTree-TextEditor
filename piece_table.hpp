#ifndef PIECE_TABLE_HPP
#define PIECE_TABLE_HPP
#include <vector>
#include "buffer.hpp"
#include "node.hpp"

class PieceTable{
	private:
        vector<Buffer> buffers;		 //store texts
		Node* rootNode; 			//store root node
		
    public:
		//getters
        vector<Buffer> getBuffers();
		Node* getRootNode(); 
		
		//setter
		void setRootNode(Node* nRootNode);
		
        //other-methods
        void addBuffer(Buffer buffer);
        void fixRootNode();
		void fixLeftSubTreeProps(Node* node);
};
#endif
