/******************************************************************************
 * DVDCore.hpp
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
#ifndef SAMPLES_DVD_SRC_DVDCORE_HPP_
#define SAMPLES_DVD_SRC_DVDCORE_HPP_

#include <GameCore.hpp>
#include <Log.hpp>



struct Character {
	GLuint     TextureID;  // ID handle of the glyph texture
	glm::ivec2 Size;       // Size of glyph
	glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
	GLuint     Advance;    // Offset to advance to next glyph
};

class DVDCore : public GameEngine::GameCore {
	public:
		/* Make Singleton */
		static DVDCore& getInstance() {
			static DVDCore instance;
			return instance;
		}

	public:
		void setScale(glm::dvec2 _scale) {
			scale = _scale;
			LOG_D("Scale set to " << scale);
		}
		void setShowFPS(bool enable = false) {
			FPS_shown = enable;
		}
		void showFPS() {
			setShowFPS(true);
		}
		void hideFPS() {
			setShowFPS(false);
		}
		bool isFPSShown() {
			return FPS_shown;
		}
		void toggleFPS() {
			FPS_shown = !FPS_shown;
		}

		void setFullscreen(bool enable = false);
		void toggleFullscreen() {
			isScreenFullscreen = !isScreenFullscreen;
			setFullscreen(isScreenFullscreen);
		}
		bool isFullscreen() {
			return isScreenFullscreen;
		}
		void setFPSCap(size_t cap = 60) {
			FPS_cap = cap;
		}
		void setFPSCapEnabled(bool enable = false) {
			FPS_cap_enabled = enable;
		}
		void toggleFPSCap() {
			FPS_cap_enabled = !FPS_cap_enabled;
			setFPSCapEnabled(FPS_cap_enabled);
		}
		bool isFPSCapEnabled() {
			return FPS_cap_enabled;
		}
		size_t getFPS_Cap() {
			return FPS_cap;
		}
		void setVSyncEnabled(bool enable = false) {
			vsync_enabled = enable;
			if(vsync_enabled) {
				SDL_GL_SetSwapInterval(1);
			} else {
				SDL_GL_SetSwapInterval(0);
			}
		}
		void enableVSync() {
			setVSyncEnabled(true);
		}
		void disableVSync() {
			setVSyncEnabled(false);
		}
		void toggleVSync() {
			vsync_enabled = !vsync_enabled;
			setVSyncEnabled(vsync_enabled);
		}
		bool isVSyncEnabled() {
			return vsync_enabled;
		}
	protected:
		virtual void setup();
		virtual void tick();
		virtual void render();
		void renderLogo();
		void renderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);


	protected:
		unsigned int VBO, VAO, EBO;
		GLuint VAO_text, VBO_text;
		ivec2 prev_mouse_pos = ivec2(0, 0);
		ivec2 curr_mouse_pos = ivec2(0, 0);

		ivec2 prev_wheel_pos = ivec2(0, 0);
		ivec2 curr_wheel_pos = ivec2(0, 0);

		double ticks_per_second = 1000/ms_per_tick;
		size_t tick_counter = 0;
		double fps = 1000;
		double fps_avg = 1000;
		bool FPS_shown = true;

		bool FPS_cap_enabled = false;
		size_t FPS_cap = 60;

		bool isScreenFullscreen = false;
		bool vsync_enabled = false;

		std::array<double, 20> fps_avg_array = {0};
		size_t pos = 0;
		std::string fps_to_render = "100";

		glm::vec3 logo_color = glm::vec3(1.0, 1.0, 1.0);
		glm::vec3 text_color = glm::vec3(1.0, 1.0, 1.0);


		GLuint texture1;
		glm::vec4 pos_vec = glm::vec4(1.0, 1.0, 1.0, 1.0);
		glm::vec3 translate_vec = glm::vec3(0.5, -0.5, 0.0);
		glm::vec3 delta_vec = glm::normalize(glm::vec3(1.0, 0.75, 0.0));
		glm::dvec2 scale = glm::dvec2(1.0,1.0);

		std::map<GLchar, Character> Characters;

		size_t prev_frame_time = 0;
		size_t curr_frame_time = 0;
		SDL_DisplayMode native;
		SDL_DisplayMode current;
};



#endif /* SAMPLES_DVD_SRC_DVDCORE_HPP_ */
