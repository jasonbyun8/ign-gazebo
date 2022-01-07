/*
 * Copyright (C) 2021 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/
#ifndef IGNITION_GAZEBO_PARAMETERS_HH_
#define IGNITION_GAZEBO_PARAMETERS_HH_

#include <ignition/gazebo/EntityComponentManager.hh>
#include <ignition/gazebo/components/ParameterDeclarationCmd.hh>
#include <ignition/gazebo/components/ParametersRegistry.hh>

namespace ignition
{
namespace gazebo
{
// Inline bracket to help doxygen filtering.
inline namespace IGNITION_GAZEBO_VERSION_NAMESPACE {
  /// \brief Declare a parameter
  template<typename ComponentT>
  bool
  DeclareParameter(EntityComponentManager &_ecm, const std::string & parameter_name, ComponentKey cmpKey)
  {
    auto worldEntity = _ecm.EntityByComponents(components::World());
    if (kNullEntity == worldEntity) {
      return false;
    }
    auto * declarations = _ecm.Component<components::ParameterDeclarationCmd>(worldEntity);
    if (!declaration) {
      _ecm.CreateComponent<components::ParameterDeclarationCmd>(worldEntity, msgs::ParameterDeclarations{});
      declarations = _ecm.Component<components::ParameterDeclarationCmd>(worldEntity);
      if (!declarations) {
        return false;
      }
    }
    auto * declaration = declarations->add_declarations();
    declaration->set_type(ComponentT::Type::typeName);
    declaration->set_name(parameter_name);
    declaration->set_component_id(cmpKey.second);
    declaration->set_component_type_id(cmpKey.first);
    return true;
  }
}
}
}

#endif