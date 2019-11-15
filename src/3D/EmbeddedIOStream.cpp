/******************************************************************************
 * EmbeddedIOStream.cpp
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

#include "EmbeddedIOStream.hpp"

#include <Log.hpp>

#include <iterator>

namespace GameEngine {
namespace _3D {

size_t EmbeddedIOStream::Read(void* pvBuffer, size_t pSize, size_t pCount)  {
//	LOG_D("Reading " << pCount << " items of size " << pSize << " (" << (pSize * pCount) << " bytes) "
//			<< "from " << file.filename() << " at position " << position);
	size_t requested_end = position + (pSize*pCount);
	if(requested_end > file.size()) {
		requested_end = file.size();
	}
	std::copy(file.begin() + position, file.begin() + requested_end, (char*) pvBuffer);
//	std::string str;
//	str.assign((char*)pvBuffer, pCount);
//	LOG_D("Contents of pvBuffer = " << str);
//	str.assign(file.begin(), pCount);
//	LOG_D("Contents of file = " << str);
	size_t old_pos = position;
	position = requested_end;
	return (requested_end - old_pos) / pSize;
}
size_t EmbeddedIOStream::Write(__attribute__((unused))const void* pvBuffer, __attribute__((unused))size_t pSize, __attribute__((unused))size_t pCount)  {
//	LOG_E("Writing to file " << file.filename());
	return 0;
}
aiReturn EmbeddedIOStream::Seek(size_t pOffset, aiOrigin pOrigin)  {
//	LOG_D("Seeking to " << pOffset << " in file " << file.filename());
	size_t req_pos = position;
	switch(pOrigin) {
		case aiOrigin_SET:
			req_pos = pOffset;
			break;
		case aiOrigin_CUR:
			req_pos += pOffset;
			break;
		case aiOrigin_END:
			req_pos = file.size() - pOffset;
			break;
		case _AI_ORIGIN_ENFORCE_ENUM_SIZE:
			break;
	}
	if(req_pos > file.size()) {
		return aiReturn_FAILURE;
	}
	position = req_pos;
	return aiReturn_SUCCESS;
}
size_t EmbeddedIOStream::Tell() const  {
	return position;
}
size_t EmbeddedIOStream::FileSize() const {
//	LOG_D("Getting file size of " << file.filename() << ".  File is " << file.size() << " bytes.");
	return file.size();
}
void EmbeddedIOStream::Flush() {}

} /* namespace GameEngine */
} /* namespace _3D */