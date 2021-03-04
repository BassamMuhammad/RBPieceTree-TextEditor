#ifndef CURSOR_POSITION_HPP
#define CURSOR_POSITION_HPP

class CursorPosition{
	private:
		int row;		//the row in which cursor is
		int column;		//the column in which cursor is
		
	public:
		//constructor
		CursorPosition(int nRow, int nColumn);

		//getters
		int getRow();
		int getColumn();
		
		//setters
		void setRow(int nRow);
		void setColumn(int nColumn);
};
#endif
