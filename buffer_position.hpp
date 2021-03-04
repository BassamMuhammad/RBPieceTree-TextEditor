#ifndef BUFFER_POSITION_HPP
#define BUFFER_POSITION_HPP

class BufferPosition{
	private:
        int index;			//stores index of Buffer.lineStarts
		int offset;			//stores offset of text stored in Buffer.value
		
	public:
		//constructor
		BufferPosition(int nIndex, int nOffset);
		
		//getters
		int getIndex();
		int getOffset();
		
		//setters
		void setIndex(int nIndex);
		void setOffset(int nOffset);
};
#endif
