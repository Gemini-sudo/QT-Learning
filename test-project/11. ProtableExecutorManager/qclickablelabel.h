#ifndef QCLICKABLELABEL_H
#define QCLICKABLELABEL_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>

class QClickableLabel : public QLabel
{
    Q_OBJECT

public:
    QClickableLabel(QWidget *parent = 0);
    ~QClickableLabel();

protected:
    virtual void mouseReleaseEvent(QMouseEvent *ev);

signals:
    void clicked(void);
};

#endif // QCLICKABLELABEL_H
