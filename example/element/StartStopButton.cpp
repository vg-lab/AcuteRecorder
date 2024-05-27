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

#include "StartStopButton.h"
#include <QVariant>
#include <constant/Styles.h>

StartStopButton::StartStopButton( QWidget *parent ) : QPushButton( parent )
{
  setProperty( "class" , example_styles::START_STOP_BUTTON );
  setProperty( "running" , false );
  setText( "Start" );
}

void StartStopButton::onFinish( )
{
  setText( "Start" );
  setProperty( "running" , false );
  // Refreshes the style
  setStyleSheet( "/**/" );
}

void StartStopButton::onStart( )
{
  setText( "Stop" );
  setProperty( "running" , true );
  // Refreshes the style
  setStyleSheet( "/**/" );
}
