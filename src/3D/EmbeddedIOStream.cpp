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

#include "3D/EmbeddedIOStream.hpp"

#include <iterator>

#include "LoggerV2/Log.hpp"

namespace game_engine {
namespace _3D {

size_t EmbeddedIOStream::Read(void* pvBuffer, size_t pSize, size_t pCount) {
  log_.Debug("Reading {}  items of size  ({} bytes) from {} at position {}.",
             pCount, pSize, (pSize * pCount), file_.filename(), position_);

  size_t requested_end = position_ + (pSize * pCount);
  if (requested_end > file_.size()) {
    requested_end = file_.size();
  }
  std::copy(file_.begin() + position_, file_.begin() + requested_end,
            static_cast<char*>(pvBuffer));
  //	std::string str;
  //	str.assign((char*)pvBuffer, pCount);
  //	log_.Debug("Contents of pvBuffer = {}", str);
  //	str.assign(file.begin(), pCount);
  //	log_.Debug("Contents of file = {}", str);
  size_t old_pos = position_;
  position_ = requested_end;
  return (requested_end - old_pos) / pSize;
}
size_t EmbeddedIOStream::Write(__attribute__((unused)) const void* pvBuffer,
                               __attribute__((unused)) size_t pSize,
                               __attribute__((unused)) size_t pCount) {
  log_.Error("Writing to file {}!  Writing is not enabled!", file_.filename());
  return 0;
}
aiReturn EmbeddedIOStream::Seek(size_t pOffset, aiOrigin pOrigin) {
  log_.Debug("Seeking to {} in file {}.", pOffset, file_.filename());
  size_t req_pos = position_;
  switch (pOrigin) {
    case aiOrigin_SET:
      req_pos = pOffset;
      break;
    case aiOrigin_CUR:
      req_pos += pOffset;
      break;
    case aiOrigin_END:
      req_pos = file_.size() - pOffset;
      break;
    case _AI_ORIGIN_ENFORCE_ENUM_SIZE:
      break;
  }
  if (req_pos > file_.size()) {
    return aiReturn_FAILURE;
  }
  position_ = req_pos;
  return aiReturn_SUCCESS;
}
size_t EmbeddedIOStream::Tell() const { return position_; }
size_t EmbeddedIOStream::FileSize() const {
  log_.Debug("Getting file size of {}.  File is {} bytes.", file_.filename(),
             file_.size());
  return file_.size();
}
void EmbeddedIOStream::Flush() {}

}  // namespace _3D
}  // namespace game_engine
