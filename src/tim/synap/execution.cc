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

#include "execution_private.h"

#include <cstdint>
#include <cstring>
#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>
#include <cassert>
#include "handle_private.h"

using namespace synaptics;
using namespace std;

namespace tim {
namespace lite {

ExecutionImpl::ExecutionImpl(const void* executable, size_t executable_size) {
    (void)executable;
    (void)executable_size;
}

ExecutionImpl::~ExecutionImpl() {
    if (!valid_) {
        return;
    }
}

std::shared_ptr<Handle> ExecutionImpl::CreateInputHandle(uint32_t in_idx, uint8_t* buffer, size_t size) {
    auto handle = std::make_shared<HandleImpl>(buffer, size);
    (void)in_idx;
    return handle;
}

std::shared_ptr<Handle> ExecutionImpl::CreateOutputHandle(uint32_t out_idx, uint8_t* buffer, size_t size) {
    auto handle = std::make_shared<HandleImpl>(buffer, size);
    (void)out_idx;
    return handle;
}

Execution& ExecutionImpl::BindInputs(const std::vector<std::shared_ptr<Handle>>& handles) {
    (void)handles;
    if (!IsValid()) {
        return *this;
    }
    return *this;
};

Execution& ExecutionImpl::BindOutputs(const std::vector<std::shared_ptr<Handle>>& handles) {
    (void)handles;
    if (!IsValid()) {
        return *this;
    }
    return *this;
};

Execution& ExecutionImpl::UnBindInput(const std::shared_ptr<Handle>& handle) {
    (void)handle;
    return *this;
}

Execution& ExecutionImpl::UnBindOutput(const std::shared_ptr<Handle>& handle) {
    (void)handle;
    return *this;
}

bool ExecutionImpl::Trigger() {
    if (!IsValid()) {
        return false;
    }
    return false;
};

std::shared_ptr<Execution> Execution::Create(
    const void* executable, size_t executable_size) {
    std::shared_ptr<ExecutionImpl> exec;
    if (executable && executable_size) {
        exec = std::make_shared<ExecutionImpl>(executable, executable_size);
        if (!exec->IsValid()) {
            exec.reset();
        }
    }
    return exec;
}

}
}
