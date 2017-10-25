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

#include <iostream>
#include <memory>
#include "modulemanager.hpp"

int main() {
  // This is the main system, that has an extension manager
  // that is able to load new modules compiled by users
  // at runtime :)

  modules::ModuleManager moduleManager;
  std::unique_ptr<modules::AbstractModule> extension(
        moduleManager.loadModule("./extension.so"));

  std::cout << "Loaded module [" << extension->moduleName() << ']' << std::endl;
  std::cout << "Written by [" << extension->moduleAuthors() << ']' << std::endl;

  return 0;
}
