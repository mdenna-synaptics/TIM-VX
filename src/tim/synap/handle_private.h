/****************************************************************************
*
*    Copyright (c) 2022 Synaptics Inc.
*
*    Permission is hereby granted, free of charge, to any person obtaining a
*    copy of this software and associated documentation files (the "Software"),
*    to deal in the Software without restriction, including without limitation
*    the rights to use, copy, modify, merge, publish, distribute, sublicense,
*    and/or sell copies of the Software, and to permit persons to whom the
*    Software is furnished to do so, subject to the following conditions:
*
*    The above copyright notice and this permission notice shall be included in
*    all copies or substantial portions of the Software.
*
*    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
*    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
*    DEALINGS IN THE SOFTWARE.
*
*****************************************************************************/

#pragma once

#include <mutex>
#include "tim/lite/handle.h"

namespace tim {
namespace lite {

enum class HandleFlushType {
    HandleFlush = 0,
    HandleInvalidate = 1
};

class HandleImpl : public Handle {
 public:
  HandleImpl(uint8_t* buffer, size_t size)
      : buffer_(buffer), buffer_size_(size) {}

  uint32_t Index() { return index_; }
  bool Flush() override;
  bool Invalidate() override;

  ~HandleImpl();

 private:
  void SetIndex(uint32_t idx) { index_ = idx; }
  uint8_t* buffer_ = nullptr;
  size_t buffer_size_ = 0;
  uint32_t index_;
};

}
}
