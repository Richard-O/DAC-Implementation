#include "customgridlayout.h"

CustomGridLayout::CustomGridLayout(QWidget *parent, int maxColumnCount)
    :QGridLayout(parent)
{
    this->maxColumnCount = maxColumnCount;
}

void CustomGridLayout::addWidgetCustom(QWidget* widget){
    int current_row = 0;
    int current_column = 0;

    while( itemAtPosition(current_row, current_column) != 0 )
    {
        if( current_column == (maxColumnCount-1) )
        {
            current_column = 0;
            ++current_row;
        }
        else
        {
            ++current_column;
        }
    }

    QGridLayout::addWidget( widget, current_row, current_column );
}



CustomGridLayout::~CustomGridLayout(){

}
