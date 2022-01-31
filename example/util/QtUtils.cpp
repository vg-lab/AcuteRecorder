//
// Created by Gael Rial Costas on 28/8/21.
//


#include <QWidget>
#include <QFile>
#include <QTextStream>

namespace qt_utils
{

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
