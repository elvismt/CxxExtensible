#
#  Example of a module-based architecture for C++ system
#
#  Copyright (C) 2017  Elvis Teixeira
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#

project(Modules CXX)
cmake_minimum_required(VERSION 3.0)

include_directories(${CMAKE_SOURCE_DIR})

add_library(extension SHARED extension.cpp)
set_target_properties(extension PROPERTIES PREFIX "")

add_executable(system main.cpp modulemanager.cpp)
target_link_libraries(system dl)
