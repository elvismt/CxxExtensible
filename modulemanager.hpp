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

#pragma once
#include <string>
#include <unordered_map>


///
/// \brief Macro to abstract declaration 'decorators'
///
/// In different systems we may need to add different
/// things in the function declaration to be able to
/// pick it from from the central system (in the simplest
/// case 'extern "C"' will sifice) so we hide everything
/// in this macro
#define MODULE_CREATION_FUNCTION \
    extern "C" modules::AbstractModule* __createModule__()


namespace modules {


class AbstractModule {
public:

  virtual ~AbstractModule() {}

  virtual std::string moduleName() const = 0;
  virtual std::string moduleAuthors() const = 0;

};


///
/// \brief Form of the module creation function
///
/// Every dynamically loaded module must expose a
/// function with this signature and defined with
/// the MODULE_CREATION_FUNCTION signature macro
using CreateModuleFunction = AbstractModule* (*) ();


class ModuleManager {
public:

  ~ModuleManager();

  AbstractModule* loadModule(const std::string &name);

protected:

  std::unordered_map<std::string,void*> _dllHandles;
};
}
