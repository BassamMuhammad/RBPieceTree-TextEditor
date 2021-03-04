#include "cursor_position.hpp"

CursorPosition::CursorPosition(int nRow, int nColumn){
	row = nRow;
	column = nColumn;
}

int CursorPosition::getRow(){return row;}

int CursorPosition::getColumn(){return column;}
		
void CursorPosition::setRow(int nRow){row = nRow;}

void CursorPosition::setColumn(int nColumn){column = nColumn;}
