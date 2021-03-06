//===-- AMDGPUELFObjectWriter.cpp - AMDGPU ELF Writer ----------------------==//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
/// \file
//===----------------------------------------------------------------------===//

#include "AMDGPUMCTargetDesc.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCFixup.h"

using namespace llvm;

namespace {

class AMDGPUELFObjectWriter : public MCELFObjectTargetWriter {
public:
  AMDGPUELFObjectWriter(bool Is64Bit, bool HasRelocationAddend);
protected:
  unsigned getRelocType(MCContext &Ctx, const MCValue &Target,
                        const MCFixup &Fixup, bool IsPCRel) const override {
    return Fixup.getKind();
  }

};


} // End anonymous namespace

AMDGPUELFObjectWriter::AMDGPUELFObjectWriter(bool Is64Bit,
                                             bool HasRelocationAddend)
  : MCELFObjectTargetWriter(Is64Bit,
                            ELF::ELFOSABI_AMDGPU_HSA,
                            ELF::EM_AMDGPU,
                            HasRelocationAddend) { }


MCObjectWriter *llvm::createAMDGPUELFObjectWriter(bool Is64Bit,
                                                  bool HasRelocationAddend,
                                                  raw_pwrite_stream &OS) {
  MCELFObjectTargetWriter *MOTW =
      new AMDGPUELFObjectWriter(Is64Bit, HasRelocationAddend);
  return createELFObjectWriter(MOTW, OS, true);
}
