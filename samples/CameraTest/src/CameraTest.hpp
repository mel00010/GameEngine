/******************************************************************************
 * CameraTest.hpp
 * Copyright (C) 2019  Mel McCalla <melmccalla@gmail.com>
 *
 * This file is part of GameEngine.
 *
 * GameEngine is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GameEngine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GameEngine.  If not, see <http://www.gnu.org/licenses/>.
 *****************************************************************************/
#ifndef SAMPLES_CAMERATEST_SRC_CAMERATEST_HPP_
#define SAMPLES_CAMERATEST_SRC_CAMERATEST_HPP_

#include <limits>
#include <string>
#include <vector>

#include <cmrc/cmrc.hpp>

#include "LoggerV2/Client.hpp"
#include "LoggerV2/Log.hpp"
#include "LoggerV2/Telemetry.hpp"

#include "3D/Camera.hpp"
#include "3D/Model.hpp"
#include "3D/Skybox.hpp"
#include "GameCore.hpp"

CMRC_DECLARE(camera_test);

using namespace game_engine;

namespace camera_test {

inline constexpr int kFrameDebugPrintIntervalMs = 1000;

inline constexpr float kCameraMoveMultiplier = 0.125f;
inline constexpr float kCameraVertMoveMultiplier = 0.025f;
inline constexpr int kCameraRotationFactor = 10;

inline constexpr float kNanosuitMoveRandRadius = 5.0f;
inline constexpr float kNanosuitScale = 0.05f;
inline constexpr glm::vec3 kNanosuitPosition = glm::vec3(1.0, 0.0, 0.0);
inline constexpr glm::vec3 kNanosuitColor = glm::vec4(1.0, 1.0, 1.0, 1.0);

inline constexpr glm::vec3 kCubePosition = glm::vec3(0.0, 0.5, 0.0);
inline constexpr float kCubeScale = 0.25f;
inline constexpr glm::vec3 kCubeRotation =
    glm::vec3(glm::radians(0.1f), glm::radians(0.2f), glm::radians(-0.3f));
inline constexpr glm::vec4 kCubeColor = glm::vec4(1.0, 1.0, 1.0, 1.0);

inline constexpr float kAxesScale = 0.1f;
inline constexpr glm::vec4 kAxesColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

inline constexpr glm::vec3 kGridRotation =
    glm::vec3(glm::radians(91.0f), glm::radians(90.0f), glm::radians(0.0f));
inline constexpr glm::vec3 kGridColor = glm::vec4(1.0, 1.0, 0.0, 1.0);

class CameraTest final : public game_engine::GameCore<CameraTest> {
 public:
  static constexpr std::string_view program_name_ = "CameraTest";
  void Setup();
  void Tick();
  void Render();
  void RegisterCallbacks();

 protected:
  const cmrc::embedded_filesystem fs_ = cmrc::camera_test::get_filesystem();
  logging::ModuleHandle log_module_{};
  logging::TelemetryChannelHandle t_camera_pitch_{};
  logging::TelemetryChannelHandle t_camera_yaw_{};
  logging::TelemetryChannelHandle t_camera_x_{};
  logging::TelemetryChannelHandle t_camera_y_{};
  logging::TelemetryChannelHandle t_camera_z_{};

  _3D::Camera camera_;
  //  _3D::Skybox skybox_;
  //  _3D::Model cube_;
  _3D::Model axes_;
  std::vector<_3D::Model> nanosuits_;
  _3D::Model grid_;
};

} /* namespace camera_test */

#endif /* SAMPLES_CAMERATEST_SRC_CAMERATEST_HPP_ */
