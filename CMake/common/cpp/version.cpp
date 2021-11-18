// generated by CommonLibrary.cmake, do not edit.

#include <@INCLUDE_NAME@/version.h>

namespace @namespace@
{

int Version::getMajor()
{
    return @NAMESPACE@_VERSION_MAJOR;
}

int Version::getMinor()
{
    return @NAMESPACE@_VERSION_MINOR;
}

int Version::getPatch()
{
    return @NAMESPACE@_VERSION_PATCH;
}

int Version::getABI()
{
    return @NAMESPACE@_VERSION_ABI;
}

std::string Version::getString()
{
    return @NAMESPACE@_VERSION_STRING;
}

unsigned long long Version::getRevision()
{
    return @NAMESPACE@_VERSION_REVISION;
}

std::string Version::getRevString()
{
    return @NAMESPACE@_REV_STRING;
}

}
