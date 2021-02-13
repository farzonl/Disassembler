#include "abstractOSFactory.h"
#if defined(_WIN32) || defined(_WIN64)
#include "windowsFactory.h"
#elif __APPLE__
#include "macFactory.h"
#elif __linux__
#include "linuxFactory.h"
#endif

AbstractOSFactory_ptr AbstractOSFactory::createFactory() {
#if defined(_WIN32) || defined(_WIN64)
  return AbstractOSFactory_ptr(new WindowsFactory);
#elif __APPLE__
  return AbstractOSFactory_ptr(new MacFactory);
#elif __linux__
  return AbstractOSFactory_ptr(new LinuxFactory);
#else
  return AbstractOSFactory_ptr();
#endif
}