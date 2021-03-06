/*
 * Copyright (c) 2021 Farzon Lotfi All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __Dynamic_Lib_Mgr_H__
#define __Dynamic_Lib_Mgr_H__

#if defined(_WIN32) || defined(_WIN64)
#define CALL_CONV __stdcall
#else
#define CALL_CONV
#endif

#include "interfaces/instruction.h"
#include "interfaces/types.h"
#include <memory>

class AbstractDisassembler;
typedef int(CALL_CONV *func_ptr_t)();

typedef struct disasmImpl {
  void (*Initalize)(Archtype archType);
  bool (*IsInitalized)();
  AbstractDisassembler *(*GetDisassembler)();
  void (*Decode)(const unsigned char *, size_t);
  void (*Clear)();
  const std::vector<Instruction> *(*GetInstructions)();

  static const int NUM_FUNCTIONS = 6;
} disasmImpl;

typedef union {
  disasmImpl by_type;
  func_ptr_t func_ptr[disasmImpl::NUM_FUNCTIONS];
} function_union;

class DynamicLibMgr {
private:
  DynamicLibMgr() = delete;

public:
  static int loadDynamicLibs(std::vector<std::string> &dylibPaths);
  static bool loadDynamicLib(const std::string &sLoadPath);
  static void unloadDynamicLib(const std::string &dylibPath);
  static void setDefaultDynamicLib(const std::string &dylibPath);
  static const char *getDynamicLibFunctionName(int index);
  static bool isInitalized();
  static void initalize(Archtype archType);
  static AbstractDisassembler *getDisassembler();
  static void decode(const unsigned char *code, size_t size);
  static void clear();
  static void getInstructions(std::vector<Instruction> &instructions);
};

#endif // __Dynamic_Lib_Mgr_H__