/****************************************************************************
*
*    Copyright (c) 2020 Vivante Corporation
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
#ifndef _VSI_NN_OP_REDUCEMAX_INTERNAL_H
#define _VSI_NN_OP_REDUCEMAX_INTERNAL_H

#include "vsi_nn_types.h"

#define VSI_NN_REDUCEMAX_SH_KERNEL_IDX(_AXIS, _INPUT_TYPE, _OUTPUT_TYPE, _IMAGE_DIMS) \
    VSI_NN_REDUCEMAX_AXIS##_AXIS##_##_INPUT_TYPE##TO##_OUTPUT_TYPE##_##_IMAGE_DIMS##_KERNEL,

enum {
    REDUCEMAX_CPU_KERNEL,
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(0, F16, F16, IMAGE)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(0, F16, I16, IMAGE)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(0, F16, I8, IMAGE)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(0, F16, U8, IMAGE)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(0, I16, I16, IMAGE)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(0, I8,  I8, IMAGE)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(0, U8,  U8, IMAGE)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(0, I16, F16, IMAGE)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(0, I8,  F16, IMAGE)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(0, U8,  F16, IMAGE)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(0, F16, F16, IMAGE_2D)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(0, F16, I16, IMAGE_2D)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(0, F16, I8,  IMAGE_2D)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(0, F16, U8,  IMAGE_2D)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(0, I16, I16, IMAGE_2D)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(0, I8,  I8,  IMAGE_2D)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(0, U8,  U8,  IMAGE_2D)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(0, I16, F16, IMAGE_2D)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(0, I8,  F16, IMAGE_2D)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(0, U8,  F16, IMAGE_2D)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(1, F16, F16, IMAGE)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(1, F16, I16, IMAGE)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(1, F16, I8, IMAGE)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(1, F16, U8, IMAGE)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(1, I16, I16, IMAGE)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(1, I8,  I8, IMAGE)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(1, U8,  U8, IMAGE)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(1, I16, F16, IMAGE)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(1, I8,  F16, IMAGE)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(1, U8,  F16, IMAGE)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(1, F16, F16, IMAGE_2D)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(1, F16, I16, IMAGE_2D)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(1, F16, I8,  IMAGE_2D)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(1, F16, U8,  IMAGE_2D)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(1, I16, I16, IMAGE_2D)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(1, I8,  I8,  IMAGE_2D)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(1, U8,  U8,  IMAGE_2D)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(1, I16, F16, IMAGE_2D)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(1, I8,  F16, IMAGE_2D)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(1, U8,  F16, IMAGE_2D)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(2, F16, F16, IMAGE)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(2, F16, I16, IMAGE)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(2, F16, I8, IMAGE)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(2, F16, U8, IMAGE)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(2, I16, I16, IMAGE)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(2, I8,  I8, IMAGE)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(2, U8,  U8, IMAGE)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(2, I16, F16, IMAGE)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(2, I8,  F16, IMAGE)
    VSI_NN_REDUCEMAX_SH_KERNEL_IDX(2, U8,  F16, IMAGE)
    REDUCEMAX_KERNEL_COUNTS,
};

enum {
    REDUCEMAX_INPUT = 0,

    REDUCEMAX_INPUTS_COUNT,

    REDUCEMAX_OUTPUT = 0,

    REDUCEMAX_OUTPUTS_COUNT,

    REDUCEMAX_PARAM_COUT = REDUCEMAX_INPUTS_COUNT + REDUCEMAX_OUTPUTS_COUNT,
};

#define _VSI_NN_REDUCEMAX_LOCAL_TENSOR_NUM 2

typedef struct _vsi_nn_reducemax_lcl_data
{
    vx_tensor   local_tensor[_VSI_NN_REDUCEMAX_LOCAL_TENSOR_NUM];
    uint32_t    hash_idx;
    vsi_bool    execute_on_sw;
} vsi_nn_reducemax_lcl_data;

typedef struct _vsi_nn_reducemax_internal_param
{
    vsi_nn_reducemax_lcl_data  local;
    vx_int32    *axis;
    vx_uint32   axis_num;
    vx_bool     keep_dim;
} vsi_nn_reducemax_internal_param;

#endif

