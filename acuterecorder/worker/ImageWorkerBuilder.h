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

#ifndef ACUTERECORDER_IMAGEWORKERBUILDER_H
#define ACUTERECORDER_IMAGEWORKERBUILDER_H

#include "WorkerBuilder.h"

/**
 * Builder for ImageRecorderStorageWorkers.
 */
class ImageWorkerBuilder : public WorkerBuilder
{
public:

  ImageWorkerBuilder( );

  bool isAvailable() const override;

  RecorderStorageWorker *createWorker(
    QObject *object , RecorderSettings& settings ) const override;
};


#endif //ACUTERECORDER_IMAGEWORKERBUILDER_H
