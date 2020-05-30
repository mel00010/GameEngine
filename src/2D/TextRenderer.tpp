/******************************************************************************
 * TextRenderer.tpp
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
#ifndef SRC_2D_TEXTRENDERER_TPP_
#define SRC_2D_TEXTRENDERER_TPP_

#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "2D/TextRenderer.hpp"
#include "LoggerV2/Log.hpp"
#include "Renderer.hpp"
#include "Vertex.hpp"

namespace game_engine {
namespace _2D {

template <typename Renderer>
void TextRenderer::Init(Renderer& renderer) {
  FT_Library ft;
  FT_Face face;

  if (FT_Init_FreeType(&ft) != 0) {
    log_.Error("Freetype:  Could not init FreeType Library");
    throw EXIT_FAILURE;
  }

  if (FT_New_Face(ft, "/usr/share/fonts/truetype/msttcorefonts/arial.ttf", 0,
                  &face) != 0) {
    log_.Error("Freetype: Failed to load font");
    throw EXIT_FAILURE;
  }
  FT_Set_Pixel_Sizes(face, 0, 48);
  if (FT_Load_Char(face, 'X', FT_LOAD_RENDER) != 0) {
    log_.Error("Freetype: Failed to load Glyph");
    throw EXIT_FAILURE;
  }

  renderer.DisableByteAlignementRestriction();

  for (uint8_t c = 0; c < 128; c++) {
    // Load character glyph
    if (FT_Load_Char(face, c, FT_LOAD_RENDER) != 0) {
      log_.Error("Freetype: Failed to load Glyph");
      continue;
    }

    FT_Bitmap bitmap = face->glyph->bitmap;

    // Generate texture
    _3D::Texture texture;
    texture.LoadTextureFromMemory(
        renderer, glm::ivec2(bitmap.width, bitmap.rows),
        _3D::PixelFormat{GL_RED, GL_RED}, bitmap.buffer, ShaderPrograms::TEXT,
        _3D::TextureType::DIFFUSE);

    // Now store character for later use
    Character character = {
        texture,
        glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
        glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
        face->glyph->advance.x};
    characters_.insert(std::pair<GLchar, Character>(c, character));
  }
  renderer.DisableByteAlignementRestriction();

  FT_Done_Face(face);
  FT_Done_FreeType(ft);

  // Update VBO for each character
  const std::vector<Vertex> vertices = {
      Vertex(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f),
             glm::vec2(1.0f, 1.0f)),  // top right
      Vertex(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f),
             glm::vec2(1.0f, 0.0f)),  // bottom right
      Vertex(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f),
             glm::vec2(0.0f, 0.0f)),  // bottom left
      Vertex(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f),
             glm::vec2(0.0f, 1.0f))  // top left
  };
  const std::vector<GLuint> indices = {0, 1, 3, 1, 2, 3};

  handle_ = renderer.GenerateVbo(ShaderPrograms::TEXT, vertices, indices);
  valid_ = true;
}

template <typename Renderer>
void TextRenderer::RenderTextRelativeToTopRight(const Renderer& renderer,
                                                const std::string text,
                                                const float x, const float y,
                                                const float scale,
                                                const glm::vec3 color) {
  glm::ivec2 size = renderer.GetWindowSize();
  RenderText(renderer, text, size.x - x, size.y - y, scale, color);
}
template <typename Renderer>
void TextRenderer::RenderText(const Renderer& renderer, const std::string text,
                              const float _x, const float _y, const float scale,
                              const glm::vec3 color) {
  float x = _x;
  float y = _y;
  renderer.UseShader(ShaderPrograms::TEXT);
  renderer.EnableBlending();
  if (!valid_) {
    log_.Error("Text renderer not valid!");
    return;
  }

  glm::ivec2 size = renderer.GetWindowSize();

  glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(size.x), 0.0f,
                                    static_cast<float>(size.y));
  renderer.SetMatrices(ShaderPrograms::TEXT, glm::mat4(1), glm::mat4(1),
                       projection);

  // Activate corresponding render state
  renderer.SetColor(ShaderPrograms::TEXT, glm::vec4(color, 1.0));
  // Iterate through all characters
  for (std::string::const_iterator c = text.cbegin(); c != text.cend(); c++) {
    Character ch = characters_[*c];

    float xpos = x + ch.bearing.x * scale;
    float ypos = y - (ch.size.y - ch.bearing.y) * scale;

    float w = ch.size.x * scale;
    float h = ch.size.y * scale;
    std::vector<Vertex> vertices = {
        Vertex(glm::vec3(xpos + w, ypos, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f),
               glm::vec2(1.0f, 1.0f)),  // top right
        Vertex(glm::vec3(xpos + w, ypos + h, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f),
               glm::vec2(1.0f, 0.0f)),  // bottom right
        Vertex(glm::vec3(xpos, ypos + h, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f),
               glm::vec2(0.0f, 0.0f)),  // bottom left
        Vertex(glm::vec3(xpos, ypos, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f),
               glm::vec2(0.0f, 1.0f))  // top left
    };
    const std::vector<GLuint> indices = {0, 1, 3, 1, 2, 3};
    // Render glyph texture over quad
    renderer.BindTexture(ShaderPrograms::TEXT, "texture_diffuse0", ch.texture,
                         0);
    //		renderer.setSwizzleMask(GL_RED, GL_RED, GL_RED, GL_ONE);
    // Update content of VBO memory
    handle_ = renderer.UpdateVbo(handle_, vertices, indices);

    // Render quad
    renderer.Render(handle_, _3D::Primitive::TRIANGLES);
    // Now advance cursors for next glyph (note that advance is number of 1/64
    // pixels)
    x += (ch.advance >> 6) *
         scale;  // Bitshift by 6 to get value in pixels (2^6 = 64)
  }
  renderer.DisableBlending();

  //	renderer.setSwizzleMask(GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA);
  renderer.UseShader(ShaderPrograms::DEFAULT);
}

} /* namespace _2D */
} /* namespace game_engine */

#endif /* SRC_2D_TEXTRENDERER_TPP_ */
