#include "buffer_position.hpp"

BufferPosition::BufferPosition(int nIndex, int nOffset){
	index = nIndex;
	offset = nOffset;
}

int BufferPosition::getIndex(){return index;}

int BufferPosition::getOffset(){return offset;}
		
void BufferPosition::setIndex(int nIndex){index = nIndex;}

void BufferPosition::setOffset(int nOffset){offset = nOffset;}
