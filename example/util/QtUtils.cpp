//
// Created by Gael Rial Costas on 28/8/21.
//


#include <QWidget>
#include <QFile>
#include <QTextStream>

namespace qt_utils
{

  QWidget *findDeepestChildWithPoint( QWidget *parent , const QPoint& point ,
                                      QWidget *ignore )
  {
    if ( ignore == parent ) ignore = nullptr;

    auto& list = parent->children( );

      foreach( QObject *o , list )
      {
        if ( o == ignore ) continue;
        if ( auto *w = dynamic_cast<QWidget *>(o))
        {
          if ( w->geometry( ).contains( point ))
          {
            return findDeepestChildWithPoint( w ,
                                              w->mapFromParent( point ) ,
                                              ignore );
          }
        }
      }

    return parent;
  }

  QString readStyle( )
  {
    QFile file( ":/style.css" );

    if ( !file.open( QFile::ReadOnly | QFile::Text )) return "";
    QTextStream in( &file );

    QString value = in.readAll( );

    file.close( );

    return value;
  }

}
