//
// Created by Gael Rial Costas on 28/8/21.
//


#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

#include <acuterecorder/RecorderSettings.h>
#include <QFileInfo>

namespace api_utils
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

  bool validateSettings( QWidget *parent ,
                         const RecorderSettings& settings ,
                         const bool folderMode )
  {
    if ( !settings.isValid( ))
    {
      QMessageBox msgBox( parent );
      msgBox.setWindowTitle( QWidget::tr( "Invalid configuration" ));
      msgBox.setText(
        QWidget::tr( "Some recording options are unset or invalid." ));
      msgBox.setIcon( QMessageBox::Icon::Critical );
      msgBox.exec( );
      return false;
    }

    QFileInfo outputVideo{ settings.getOutputPath( ) };
    if ( outputVideo.exists( ) && !folderMode )
    {
      QMessageBox msgBox( parent );
      msgBox.setWindowTitle( QWidget::tr( "Output video exists" ));
      msgBox.setText(
        QWidget::tr( "The output video '%1' already exists. Overwrite?." )
          .arg( outputVideo.absoluteFilePath( )));
      msgBox.setStandardButtons( QMessageBox::Cancel | QMessageBox::Ok );
      msgBox.setDefaultButton( QMessageBox::Ok );
      msgBox.setIcon( QMessageBox::Icon::Warning );
      const auto result = msgBox.exec( );

      if ( result != QMessageBox::Ok ) return false;
    }
    return true;
  }

}
