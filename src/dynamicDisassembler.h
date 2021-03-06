/*
 * Copyright (c) 2021 Farzon Lotfi All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __Dynamic_Disassembler_H__
#define __Dynamic_Disassembler_H__

#include "interfaces/interfaceDisassembler.h"

class DynamicDisassembler : public AbstractDisassembler {
public:
  DynamicDisassembler(Archtype archType);
  virtual ~DynamicDisassembler();
  virtual void Decode(const unsigned char *code, size_t size) final;
  virtual void Clear() final;
};

#endif // __Dynamic_Disassembler_H__
