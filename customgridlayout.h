#ifndef CUSTOMGRIDLAYOUT_H
#define CUSTOMGRIDLAYOUT_H

#include <QGridLayout>

class CustomGridLayout : public QGridLayout
{
public:
    CustomGridLayout(QWidget *parent, int maxColumnCount);
    ~CustomGridLayout();

    void addWidgetCustom(QWidget* widget);

private:
    int maxColumnCount;
};

#endif // CUSTOMGRIDLAYOUT_H
