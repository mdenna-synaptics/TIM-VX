/****************************************************************************
*
*    Copyright (c) 2022 Vivante Corporation
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
#ifndef TIM_VX_OPS_ROI_POOL_H_
#define TIM_VX_OPS_ROI_POOL_H_

#include <array>
#include "tim/vx/direct_map_op.h"
#include "tim/vx/types.h"

namespace tim {
namespace vx {
namespace ops {

/**
 * ## ROI_POOL
 *
 * Select and scale the feature map of each region of interest to a unified output
 * size by max-pooling.
 * 
 *    pool_type : only support max-pooling  (MAX)
 *    scale : The ratio of image to feature map (Range: 0 < scale <= 1) 
 *    size : The size of roi pooling (height/width)
 *
 */

class ROI_Pool : public DirectMapOp {
 public:
  ROI_Pool(Graph* graph, PoolType type, float scale,
            const std::array<uint32_t, 2>& size);

  std::shared_ptr<Operation> Clone(
      std::shared_ptr<Graph>& graph) const override;

 protected:
  const PoolType type_;
  const float scale_;
  std::array<uint32_t, 2> size_;
};

}  // namespace ops
}  // namespace vx
}  // namespace tim

#endif /* TIM_VX_OPS_ROI_POOL_H_ */
