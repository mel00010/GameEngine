/******************************************************************************
 * EmbeddedIOHandler.cpp
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

#include "EmbeddedIOHandler.hpp"

#include <Log.hpp>

namespace GameEngine {
namespace _3D {

bool EmbeddedIOHandler::Exists(const char* pFile) const {
//	LOG_D("Testing for existence of " << pFile << ".  File " << (fs.exists(pFile) ? "exists" : "does not exist") << ".");
	return fs.exists(pFile);
}
char EmbeddedIOHandler::getOsSeparator() const {
	return '/';
}
Assimp::IOStream* EmbeddedIOHandler::Open(const char* pFile, const char* pMode) {
//	LOG_D("Opening file " << pFile);
	cmrc::file file = fs.open(pFile);
	EmbeddedIOStream* ios = new EmbeddedIOStream(file);
	io_streams.push_back(ios);
	return ios;
}
void EmbeddedIOHandler::Close( Assimp::IOStream* pFile) {
//	LOG_D("Closing file");
	auto it = std::find(io_streams.begin(), io_streams.end(), pFile);
	if (it == io_streams.end()) {
		return;
	}
	EmbeddedIOStream* file = *it;
	io_streams.erase(it);
	delete file;
}

} /* namespace _3D */
} /* namespace GameEngine */

