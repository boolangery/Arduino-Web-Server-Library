#include "HtmlArray.h"

PROGMEM prog_char HtmlArray_elem[] = "<table>%s</table>";
PROGMEM prog_char HtmlArray_column[] = "</td>#<td>";
PROGMEM prog_char HtmlArray_row[] = "<tr>#</tr>";

PROGMEM const char *HtmlArray_tab[] = {   
  HtmlArray_elem, HtmlArray_column, HtmlArray_row
};

HtmlArray::HtmlArray(int row, int column): HtmlObject(0), _nRow(row), _nColumn(column)
{
    
}


String HtmlArray::getHtml() const
{
    String tmpRow, tmpColumn;
    
    for (int i=0; i<_nRow; i++)
        tmpRow += "<tr>#</tr>";
        // tmpRow = "<tr>#</tr><tr>#</tr>"
        
    for (int i=0; i<_nColumn; i++)
        tmpColumn += "</td>$<td>";
        // tmpColumn = "</td>#<td></td>#<td>"
        
    tmpRow.replace("#", tmpColumn);
    
    tmpColumn = "<table>#</table>";
    tmpColumn.replace("#", tmpRow);
    return getFormatedString(tmpColumn);
}
