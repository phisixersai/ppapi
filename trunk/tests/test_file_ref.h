// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PAPPI_TESTS_TEST_FILE_REF_H_
#define PAPPI_TESTS_TEST_FILE_REF_H_

#include <string>

#include "ppapi/tests/test_case.h"

class TestFileRef : public TestCase {
 public:
  explicit TestFileRef(TestInstance* instance) : TestCase(instance) {}

  // TestCase implementation.
  virtual bool Init();
  virtual void RunTest();

 private:
  std::string TestGetFileSystemType();
  std::string TestGetName();
  std::string TestGetPath();
  std::string TestGetParent();
};

#endif  // PAPPI_TESTS_TEST_FILE_REF_H_