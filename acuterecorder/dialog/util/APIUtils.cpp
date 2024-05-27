/*
 * Copyright (c) 2021-2024 VG-Lab/URJC.
 *
 * Authors: Gael Rial Costas <gael.rial.costas@urjc.es>
 *
 * This file is part of AcuteRecorder <https://github.com/vg-lab/AcuteRecorder>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

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
