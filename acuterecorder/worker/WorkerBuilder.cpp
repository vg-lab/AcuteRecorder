//
// Created by gaeqs on 12/15/21.
//

#include "WorkerBuilder.h"

WorkerBuilder::WorkerBuilder( bool outputToFolder )
{
  outputToFolder_ = outputToFolder;
}

bool WorkerBuilder::isOutputAFolder( ) const
{
  return outputToFolder_;
}
