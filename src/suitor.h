//===-- suitor.h - Suitor class definition -------*- C++ -*-===//
//
// This software uses the MIT license.
// See https://mit-license.org/ for license information.
//
//===----------------------------------------------------------------------===//
///
/// This file was an attempt at using classes before the rewrite.
///
//===----------------------------------------------------------------------===//

// deprecated

#ifndef SUITOR_CLASS_h
#define SUITOR_CLASS_h

#include "resources.h"

class Suitor {
private:
  bool hasSpy = false, hasHandmaid = false;

  int tokenCount = 0;

public:
  void GainSpy() { hasSpy = true; }
  void RemoveSpy() { hasSpy = false; }
  void GainHandmaid() { hasHandmaid = true; }
  void RemoveHandmaid() { hasHandmaid = false; }
  void GainToken() { tokenCount++; }

  int GetTokenCount() { return tokenCount; }

  bool HandmaidStatus() { return hasHandmaid; }
  bool SpyStatus() { return hasSpy; }
};

Suitor suitor1, suitor2, suitor3, suitor4, suitor5, suitor6;

std::vector<Suitor> suitorObjects{suitor1, suitor2, suitor3,
                                  suitor4, suitor5, suitor6};

#endif