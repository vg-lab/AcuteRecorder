//
// Created by Gael Rial Costas on 16/8/21.
//
#ifndef QTRECORDER_QTUTILS_H
#define QTRECORDER_QTUTILS_H

#include <QWidget>
#include <iostream>


namespace qt_utils
{

  QWidget *findDeepestChildWithPoint( QWidget *parent , const QPoint& point ,
                                      QWidget *ignore = nullptr );

  QString readStyle( );

}

#endif //QTRECORDER_QTUTILS_H
