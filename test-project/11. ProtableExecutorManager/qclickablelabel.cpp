#include "qclickablelabel.h"
QClickableLabel::QClickableLabel(QWidget *parent)
    : QLabel(parent)
{

}

QClickableLabel::~QClickableLabel()
{

}

void QClickableLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev)
    emit clicked();
}
