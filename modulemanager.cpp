/*
 * Example of a module-based architecture for a C++ system
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
#include <stdexcept>

#if defined(__linux__) && defined(__GNUC__)
# include <dlfcn.h>
#else
# error "CxxExtensible doesn\'t support your OS or compiler yet"
#endif

namespace modules {

ModuleManager::~ModuleManager() {
  for (auto handle : _dllHandles) {
    dlclose(handle.second);
  }
}


std::unique_ptr<AbstractModule>
ModuleManager::loadModule(const std::string &moduleName, bool lazyLoad) {
  void *handle = nullptr;

  handle = dlopen(moduleName.c_str(), lazyLoad ? RTLD_LAZY : RTLD_NOW);
  if (!handle) {
    throw std::runtime_error("Could not load module library");
  }

  auto createModule = (CreateModuleFunction) dlsym(handle, "__createModule__");
  if (!createModule) {
    throw std::runtime_error("Could not find MODULE_CREATION_FUNCTION in library");
  }

  _dllHandles.emplace(std::make_pair(moduleName, handle));
  return std::unique_ptr<AbstractModule>(createModule());
}
}

