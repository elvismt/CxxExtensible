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

namespace extension_module {

///
/// \brief Provides the extension module's functionality
///
/// The module must be a subclass of modules::AbstractModule
/// or of some of it's subclasses. The base class must be
/// picked from some system public header, where 'system' is
/// the system that you are extending.
class ExtensionModule : public modules::AbstractModule {
public:

  ExtensionModule(const std::string &moduleName,
              const std::string &authorName)
    : _moduleName{moduleName}
    , _authorName{authorName} {}


  virtual std::string moduleName() const override {
    return _moduleName;
  }
  
  virtual std::string moduleAuthors() const override {
    return _authorName;
  }

private:

  std::string _moduleName;
  std::string _authorName;
};
}


/// This is the only function exported by the module
MODULE_CREATION_FUNCTION {
  return new extension_module::ExtensionModule(
    "Extension Module", "Elvis Teixeira");
}
