#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import os.path
path = os.getcwd()

for root, dirs, files in os.walk(path):
  if (root.find("pybind11") != -1) or root.endswith("/openssl") or root.endswith("/zlib") or (root.find("/build/generated/") != -1) or (root.find("cmake-build-debug/") != -1) or (root.find("cmake-build-release") != -1) or (root.find("CMakeFiles") != -1):
    continue
  for name in files:
    if (name.endswith(".h") or name.endswith(".m") or name.endswith(".mm") or name.endswith(".hpp") or name.endswith(".cpp") or name.endswith(".java")):
      localpath = root + '/' + name
      print localpath
      os.system("clang-format -i %s -style=File" %(localpath))
