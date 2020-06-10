/******************************************************************************
 * SlangShader.hpp
 * Copyright (C) 2020  Mel McCalla <melmccalla@gmail.com>
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
#ifndef SRC_GL_SLANGSHADER_HPP_
#define SRC_GL_SLANGSHADER_HPP_

#include <cmrc/cmrc.hpp>
#include <slang.h>

#include "LoggerV2/Log.hpp"

#include "GL/Shader.hpp"
#include "GL/ShaderProgram.hpp"

namespace game_engine::gl {

SlangSession* getSlangSession() {
  static SlangSession* const slangSession = spCreateSession(NULL);
  return slangSession;
}
class SlangShaderProgram {
 public:
  ShaderProgram* loadShaderProgram(const cmrc::file file) const {
    // A compile request represents a single invocation of the compiler,
    // to process some inputs and produce outputs (or errors).
    //
    const SlangCompileRequest* slangRequest =
        spCreateCompileRequest(getSlangSession());

    int targetIndex = spAddCodeGenTarget(slangRequest, SLANG_GLSL);

    // We will specify the desired "profile" for this one target in terms of the
    // DirectX "shader model" that should be supported.
    //
    spSetTargetProfile(slangRequest, targetIndex,
                       spFindProfile(getSlangSession(), "glsl_460"));

    // A compile request can include one or more "translation units," which more
    // or less amount to individual source files (think `.c` files, not the `.h`
    // files they might include).
    //
    // For this example, our code will all be in the Slang language. The user
    // may also specify HLSL input here, but that currently doesn't affect the
    // compiler's behavior much.
    //
    int translationUnitIndex = spAddTranslationUnit(
        slangRequest, SLANG_SOURCE_LANGUAGE_SLANG, nullptr);

    // We will load source code for our translation unit from the file
    // `shaders.slang`. There are also variations of this API for adding source
    // code from application-provided buffers.
    //
    spAddTranslationUnitSourceFile(slangRequest, translationUnitIndex,
                                   "shaders.slang");

    // Next we will specify the entry points we'd like to compile.
    // It is often convenient to put more than one entry point in the same file,
    // and the Slang API makes it convenient to use a single run of the compiler
    // to compile all entry points.
    //
    // For each entry point, we need to specify the name of a function, the
    // translation unit in which that function can be found, and the stage
    // that we need to compile for (e.g., vertex, fragment, geometry, ...).
    //
    char const* vertexEntryPointName = "vertexMain";
    char const* fragmentEntryPointName = "fragmentMain";
    char const* geometryEntryPointName = "geometryMain";
    int vertexIndex = spAddEntryPoint(slangRequest, translationUnitIndex,
                                      vertexEntryPointName, SLANG_STAGE_VERTEX);
    int fragmentIndex =
        spAddEntryPoint(slangRequest, translationUnitIndex,
                        fragmentEntryPointName, SLANG_STAGE_FRAGMENT);
    int geometryIndex =
        spAddEntryPoint(slangRequest, translationUnitIndex,
                        geometryEntryPointName, SLANG_STAGE_GEOMETRY);

    // Once all of the input options for the compiler have been specified,
    // we can invoke `spCompile` to run the compiler and see if any errors
    // were detected.
    //
    const SlangResult compileRes = spCompile(slangRequest);

    // Even if there were no errors that forced compilation to fail, the
    // compiler may have produced "diagnostic" output such as warnings.
    // We will go ahead and print that output here.
    //
    if (auto diagnostics = spGetDiagnosticOutput(slangRequest)) {
      log_.Error("Slang output:  {}", diagnostics);
    }

    // If compilation failed, there is no point in continuing any further.
    if (SLANG_FAILED(compileRes)) {
      spDestroyCompileRequest(slangRequest);
      return nullptr;
    }

    // If compilation was successful, then we will extract the code for
    // our two entry points as "blobs".
    //
    // If you are using a D3D API, then your application may want to
    // take advantage of the fact taht these blobs are binary compatible
    // with the `ID3DBlob`, `ID3D10Blob`, etc. interfaces.
    //

    ISlangBlob* vertexShaderBlob = nullptr;
    spGetEntryPointCodeBlob(slangRequest, vertexIndex, 0, &vertexShaderBlob);

    ISlangBlob* fragmentShaderBlob = nullptr;
    spGetEntryPointCodeBlob(slangRequest, fragmentIndex, 0,
                            &fragmentShaderBlob);

    ISlangBlob* geometryShaderBlob = nullptr;
    spGetEntryPointCodeBlob(slangRequest, geometryIndex, 0,
                            &geometryShaderBlob);

    // We extract the begin/end pointers to the output code buffers
    // using operations on the `ISlangBlob` interface.
    //
    char const* vertexCode =
        static_cast<char const*>(vertexShaderBlob->getBufferPointer());
    char const* vertexCodeEnd = vertexCode + vertexShaderBlob->getBufferSize();

    char const* fragmentCode =
        static_cast<char const*>(fragmentShaderBlob->getBufferPointer());
    char const* fragmentCodeEnd =
        fragmentCode + fragmentShaderBlob->getBufferSize();

    char const* geometryCode =
        static_cast<char const*>(geometryShaderBlob->getBufferPointer());
    char const* geometryCodeEnd =
        geometryCode + geometryShaderBlob->getBufferSize();

    // Once we have extracted the output blobs, it is safe to destroy
    // the compile request and even the session.
    //
    spDestroyCompileRequest(slangRequest);

    const std::string vertex(vertexCode, vertexCodeEnd);
    const std::string fragment(fragmentCode, fragmentCodeEnd);
    const std::string geometry(geometryCode, geometryCodeEnd);

    Shader vertex_shader(vertex, ShaderType::VERTEX);
    Shader fragment_shader(fragment, ShaderType::FRAGMENT);
    Shader geometry_shader(geometry, ShaderType::GEOMETRY);

    ShaderProgram* const program = new ShaderProgram();

    program->Init();
    program->AttachShader(vertex_shader);
    program->AttachShader(fragment_shader);
    program->AttachShader(geometry_shader);

    program->Link();

    // Once we've used the output blobs from the Slang compiler to initialize
    // the API-specific shader program, we can release their memory.
    //
    vertexShaderBlob->release();
    fragmentShaderBlob->release();
    geometryShaderBlob->release();

    return program;
  }

 private:
  logging::Log log_ = logging::Log("main");
};

} /* namespace game_engine::gl */

#endif /* SRC_GL_SLANGSHADER_HPP_ */
