/******************************************************************************
 * EmbeddedIOStream.hpp
 * Copyright (C) 2019  Mel McCalla <melmccalla@gmail.com>
 *
 * This file is part of GameEngineMin.
 *
 * GameEngineMin is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GameEngineMin is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GameEngineMin.  If not, see <http://www.gnu.org/licenses/>.
 *****************************************************************************/
#ifndef SRC_3D_EMBEDDEDIOSTREAM_HPP_
#define SRC_3D_EMBEDDEDIOSTREAM_HPP_

#include <assimp/IOStream.hpp>

#include <cmrc/cmrc.hpp>

namespace GameEngine {
namespace _3D {
class EmbeddedIOHandler;
} /* namespace GameEngine */
} /* namespace _3D */



namespace GameEngine {
namespace _3D {

class EmbeddedIOStream : public Assimp::IOStream {
	protected:
		EmbeddedIOStream(cmrc::file _file) : file(_file), position(0) {}
		friend EmbeddedIOHandler;
	public:
		/** @brief Read from the file
		 *
		 * See fread() for more details
		 * This fails for write-only files */
		virtual size_t Read(void* pvBuffer,
			size_t pSize,
			size_t pCount) override;

		// -------------------------------------------------------------------
		/** @brief Write to the file
		*
		* See fwrite() for more details
		* This fails for read-only files */
		virtual size_t Write(const void* pvBuffer,
			size_t pSize,
			size_t pCount) override;

		// -------------------------------------------------------------------
		/** @brief Set the read/write cursor of the file
		 *
		 * Note that the offset is _negative_ for aiOrigin_END.
		 * See fseek() for more details */
		virtual aiReturn Seek(size_t pOffset,
			aiOrigin pOrigin) override;

		// -------------------------------------------------------------------
		/** @brief Get the current position of the read/write cursor
		 *
		 * See ftell() for more details */
		virtual size_t Tell() const override;

		// -------------------------------------------------------------------
		/** @brief Returns filesize
		 *  Returns the filesize. */
		virtual size_t FileSize() const override;

		// -------------------------------------------------------------------
		/** @brief Flush the contents of the file buffer (for writers)
		 *  See fflush() for more details.
		 */
		virtual void Flush() override;

	protected:
		cmrc::file file;
		size_t position;
};

} /* namespace GameEngine */
} /* namespace _3D */

#endif /* SRC_3D_EMBEDDEDIOSTREAM_HPP_ */
