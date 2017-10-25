/*
 * Example of a module-based architecture for C++ system on linux
 *
 * Copyright (C) 2017  Elvis Teixeira
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "modulemanager.hpp"
#include <dlfcn.h>
#include <iostream>

namespace modules {

ModuleManager::~ModuleManager() {
    for (auto handle : dllHandles) {
        dlclose(handle.second);
    }
}


AbstractModule* ModuleManager::loadModule(const std::string &moduleName) {
  void *handle = nullptr;

  handle = dlopen(moduleName.c_str(), RTLD_LAZY);
  if (!handle) {
    std::cout << "Error loading library " << moduleName << std::endl;
    return nullptr;
  }

  auto createModule = (CreateModuleFunction) dlsym(handle, "__createModule__");
  if (!createModule) {
    std::cout << "Error loading createModule() from module " << moduleName << std::endl;
    return nullptr;
  }

  dllHandles.emplace(std::make_pair(moduleName, handle));
  return createModule();
}
}
