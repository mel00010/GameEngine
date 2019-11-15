/******************************************************************************
 * EmbeddedIOHandler.hpp
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
#ifndef SRC_3D_EMBEDDEDIOHANDLER_HPP_
#define SRC_3D_EMBEDDEDIOHANDLER_HPP_

#include "EmbeddedIOStream.hpp"

#include <assimp/IOSystem.hpp>
#include <assimp/IOStream.hpp>

#include <map>

namespace GameEngine {
namespace _3D {

class EmbeddedIOHandler : public Assimp::IOSystem {
	public:
		EmbeddedIOHandler(cmrc::embedded_filesystem& _fs) : fs(_fs) {}

	public:
		// -------------------------------------------------------------------
		/** @brief Tests for the existence of a file at the given path.
		 *
		 * @param pFile Path to the file
		 * @return true if there is a file with this path, else false.
		 */
		virtual bool Exists( const char* pFile) const override;

		// -------------------------------------------------------------------
		/** @brief Returns the system specific directory separator
		 *  @return System specific directory separator
		 */
		virtual char getOsSeparator() const override;

		// -------------------------------------------------------------------
		/** @brief Open a new file with a given path.
		 *
		 *  When the access to the file is finished, call Close() to release
		 *  all associated resources (or the virtual dtor of the IOStream).
		 *
		 *  @param pFile Path to the file
		 *  @param pMode Desired file I/O mode. Required are: "wb", "w", "wt",
		 *         "rb", "r", "rt".
		 *
		 *  @return New IOStream interface allowing the lib to access
		 *         the underlying file.
		 *  @note When implementing this class to provide custom IO handling,
		 *  you probably have to supply an own implementation of IOStream as well.
		 */
		virtual Assimp::IOStream* Open(const char* pFile, const char* pMode = "rb") override;

		// -------------------------------------------------------------------
		/** @brief Closes the given file and releases all resources
		 *    associated with it.
		 *  @param pFile The file instance previously created by Open().
		 */
		virtual void Close( Assimp::IOStream* pFile) override;

	protected:
		cmrc::embedded_filesystem& fs;
		std::vector<EmbeddedIOStream*> io_streams;
};

} /* namespace _3D */
} /* namespace GameEngine */

#endif /* SRC_3D_EMBEDDEDIOHANDLER_HPP_ */