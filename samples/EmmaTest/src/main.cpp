/******************************************************************************
 * main.cpp
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

#include <math.h>

#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>

#include "absl/flags/usage.h"
#include "absl/hash/hash.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"

#include "GameCore.hpp"
#include "LoggerV2/Log.hpp"
#include "LoggerV2/Telemetry.hpp"

class EmmaTest : public game_engine::GameCore<EmmaTest> {
 public:
  static constexpr std::string_view program_name_ = "EmmaTest";
  void Setup() {}
  void Tick() {}
  void Render() {}
  void RegisterCallbacks() {}
};

using variable = double;
using string = std::string;
void print(variable a) { std::cout << a << std::endl; }
void print(std::string a) { std::cout << a << std::endl; }

variable readFromTerminal() {
  variable x;
  std::cout << "Please enter a number:  ";
  std::cin >> x;
  return x;
}

void f(variable a, variable b, variable c) {
  if (a == b) {
    print("a is equal to b (a = " + std::to_string(a) +
          " and b = " + std::to_string(b) + ")");
  } else if (a == c) {
    print("a is not equal to b and a is equal to c (a = " + std::to_string(a) +
          ", b = " + std::to_string(b) + " and c = " + std::to_string(c) + ")");
  } else {
    print("a is not equal to b and a is not equal to c (a = " +
          std::to_string(a) + ", b = " + std::to_string(b) +
          " and c = " + std::to_string(c) + ")");
  }
}
variable g(variable a) {
  print("log(abs(sin(" + std::to_string(a) +
        "))) = " + std::to_string(log(abs(sin(a)))));
  return a;
}

template <typename T>
int sgn(T val) {
  return (T(0) < val) - (val < T(0));
}

struct Fraction {
  int numerator = 1;
  int denominator = 1;

  int lcm(int a, int b) { return (a * b) / gcd(a, b); }
  int gcd(int a, int b) { return ((a % b) == 0) ? (a / b) : gcd(b, a % b); }
  Fraction inverse() { return Fraction{-numerator, denominator}; }
  Fraction reciprocal() { return Fraction{denominator, numerator}; }
  Fraction simplify() {
    int gcd_ = gcd(numerator, denominator);
    numerator /= gcd_;
    denominator /= gcd_;
    if ((sgn(numerator) == -1) && (sgn(denominator) == -1)) {
      numerator *= -1;
      denominator *= -1;
    }
    int temp = abs(numerator / denominator);
    if ((temp > 0) && ((numerator % denominator) == 0)) {
      numerator /= temp;
      denominator /= temp;
    }
    return *this;
  }
  std::string to_string() {
    return std::to_string(numerator) + "/" + std::to_string(denominator);
  }
};
Fraction operator+(Fraction lhs, Fraction rhs) {
  return Fraction{
      (lhs.numerator * rhs.denominator) + (rhs.numerator * lhs.denominator),
      lhs.denominator * rhs.denominator}
      .simplify();
}
Fraction operator-(Fraction lhs, Fraction rhs) {
  return (lhs + (rhs.inverse())).simplify();
}
Fraction operator*(Fraction lhs, Fraction rhs) {
  return Fraction{lhs.numerator * rhs.numerator,
                  lhs.denominator * rhs.denominator}
      .simplify();
}
Fraction operator/(Fraction lhs, Fraction rhs) {
  return (lhs * (rhs.reciprocal())).simplify();
}

int main(int argc, char** argv) {
  ::absl::SetProgramUsageMessage(
      absl::StrCat("Sample usage:\n\t", argv[0], " [flags...]"));
  //    absl::SetProgramVersionMessage("0.0.1");
  ::absl::ParseCommandLine(argc, argv);

  Fraction fract1;
  Fraction fract2;
  fract1.numerator = 10;
  fract1.denominator = 16;
  fract2.numerator = 4;
  fract2.denominator = 3;

  print("added = " + (fract1 + fract2).to_string());
  print("subtracted = " + (fract1 - fract2).to_string());
  print("multiplied = " + (fract1 * fract2).to_string());
  print("divided = " + (fract1 / fract2).to_string());
  logging::Client log_client = logging::Client("main");
  logging::Log log = logging::Log("main");
  log.RegisterThread("Main");
  logging::Telemetry telem = logging::Telemetry("telemetry");
  logging::ModuleHandle log_module = log.RegisterModule("EmmaTest").value();
  logging::TelemetryChannelHandle t_camera_pitch_ =
      telem.Create("Camera/Pitch", -90.0, -100, 90, 100, true).value();
  logging::TelemetryChannelHandle t_camera_yaw_ =
      telem.Create("Camera/Yaw", 0, -1, 360, 370, true).value();
  logging::TelemetryChannelHandle t_camera_x_ =
      telem.Create("Camera/Pos/X", -10, -10000, 10, 10000, true).value();
  logging::TelemetryChannelHandle t_camera_y_ =
      telem.Create("Camera/Pos/Y", -10, -10000, 10, 10000, true).value();
  logging::TelemetryChannelHandle t_camera_z_ =
      telem.Create("Camera/Pos/Z", -10, -10000, 10, 10000, true).value();
  log.CAPTURE(fract1.numerator, fract1.denominator);
  log.Trace("Test");

  for (size_t i = 0; i < 1000; i++) {
    t_camera_x_.Add(i);
  }
  P7_Exceptional_Flush();

  return 0;

  //  EmmaTest::Main(&argc, &argv);
}
