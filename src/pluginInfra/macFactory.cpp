#include <cassert>
#include <dlfcn.h>

#include "macFactory.h"

Load_ptr MacFactory::getLoadLib() { return Helper::makeShared<MacDylibLoad>(); }

bool MacDylibLoad::LoadLibraryFromPath(std::string sLoadPath) {
  if (AbstractOSFactory::doesFileExist(sLoadPath)) {
    return false;
  }
  mDylib = dlopen(sLoadPath.c_str(), RTLD_LAZY);
  if (mDylib == nullptr) {
    return false;
  }

  for (int i = 0; i < disasmImpl::NUM_FUNCTIONS; i++) {
    mDyLibFunctions.func_ptr[i] = reinterpret_cast<func_ptr_t>(
        dlsym(mDylib, DynamicLibMgr::getDynamicLibFunctionName(i)));
    assert(mDyLibFunctions.func_ptr[i] != nullptr);
  }
  mDyLibFunctions.by_type.initalize();
  return mDyLibFunctions.by_type.isInitalized();
}

function_union &MacDylibLoad::getLoadedLibrary() { return mDyLibFunctions; }

MacDylibLoad::~MacDylibLoad() {
  if (mDylib != nullptr) {
    mDyLibFunctions.by_type.shutdown();
    assert(mDyLibFunctions.by_type.isInitalized() == false);
    dlclose(mDylib);
    mDylib = nullptr;
  }
}