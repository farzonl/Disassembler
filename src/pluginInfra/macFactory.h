#ifndef __mac_factory_h__
#define __mac_factory_h__

#include "abstractOSFactory.h"

class MacDylibLoad : public ILoad {
private:
  void *mDylib = nullptr;
  function_union mDyLibFunctions;

public:
  MacDylibLoad() : ILoad() {}
  virtual bool LoadLibraryFromPath(std::string sLoadPath) override;
  virtual function_union &getLoadedLibrary() override;
  ~MacDylibLoad();
};

class MacFactory : public AbstractOSFactory {
public:
  virtual Load_ptr getLoadLib() final;
};

#endif // __mac_factory_h__