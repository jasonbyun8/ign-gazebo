// Copyright 2021 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <pybind11/pybind11.h>

#include <iostream>

#include "server_config.hh"

namespace ignition
{
namespace gazebo
{
namespace python
{
void
ServerConfig::destroy()
{
  server_config_.reset();
}

ServerConfig::~ServerConfig()
{

}

ServerConfig::ServerConfig()
{
  server_config_ = std::make_shared<ignition::gazebo::ServerConfig>();
}

bool ServerConfig::SetSdfFile(const std::string &_file)
{
  return server_config_->SetSdfFile(_file);
}

void define_server_config(py::object module)
{
  py::class_<ServerConfig, ignition::utils::python::Destroyable, std::shared_ptr<ServerConfig>>(module, "ServerConfig")
  .def(py::init<>())
  .def(
    "set_sdf_file", &ServerConfig::SetSdfFile,
    "Set sdf file");
}

}  // namespace python
}  // namespace gazebo
}  // namespace ignition
