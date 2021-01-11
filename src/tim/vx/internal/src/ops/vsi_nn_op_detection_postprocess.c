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
#include <string.h>
#include <stdlib.h>
#include "vsi_nn_types.h"
#include "vsi_nn_log.h"
#include "vsi_nn_node.h"
#include "vsi_nn_prv.h"
#include "vsi_nn_ops.h"
#include "vsi_nn_tensor.h"
#include "vsi_nn_tensor_util.h"
#include "vsi_nn_error.h"
#include "utils/vsi_nn_util.h"
#include "kernel/vsi_nn_kernel.h"
#include "kernel/vsi_nn_kernel_eltwise.h"
#include "utils/vsi_nn_constraint_check.h"

#define _INPUT_NUM          (3)
#define _OUTPUT_NUM         (4)
#define _BOX_INPUT_NUM          (2)
#define _BOX_OUTPUT_NUM         (1)
#define _NMS_INPUT_NUM          (2)
#define _NMS_OUTPUT_NUM         (4)

static vsi_status op_compute
    (
    vsi_nn_node_t * self,
    vsi_nn_tensor_t ** inputs,
    vsi_nn_tensor_t ** outputs
    )
{
    vsi_status status = VSI_FAILURE;
    vsi_nn_kernel_param_t * param0 = NULL;
    vsi_nn_kernel_param_t * param1 = NULL;
    vsi_nn_tensor_t* box_tensors[3] = { NULL };
    vsi_nn_tensor_t* nms_tensors[6] = { NULL };
    vsi_nn_tensor_t* bbox_tensor = NULL;
    vsi_nn_tensor_attr_t attr;
    vsi_nn_detection_postprocess_param * p = &(self->nn_param.detection_postprocess);
    float inv_scale_y, inv_scale_x, inv_scale_h, inv_scale_w;

    memset(&attr, 0, sizeof(vsi_nn_tensor_attr_t));

    attr.size[0] = 4;
    attr.size[1] = inputs[0]->attr.size[1];
    attr.size[2] = inputs[0]->attr.size[2];
    attr.dim_num = 3;
    attr.dtype.vx_type = VSI_NN_TYPE_FLOAT32;
    attr.is_const = FALSE;
    attr.vtl = TRUE;
    bbox_tensor = vsi_nn_CreateTensor( self->graph, &attr );

    inv_scale_y = 1.0f / p->dy;
    inv_scale_x = 1.0f / p->dx;
    inv_scale_h = 1.0f / p->dh;
    inv_scale_w = 1.0f / p->dw;

    if (bbox_tensor)
    {
        param0 = vsi_nn_kernel_param_create();
        vsi_nn_kernel_param_add_float32( param0, "inv_scale_y", inv_scale_y);
        vsi_nn_kernel_param_add_float32( param0, "inv_scale_x", inv_scale_x);
        vsi_nn_kernel_param_add_float32( param0, "inv_scale_h", inv_scale_h);
        vsi_nn_kernel_param_add_float32( param0, "inv_scale_w", inv_scale_w);
        box_tensors[0] = inputs[1];
        box_tensors[1] = inputs[2];
        box_tensors[2] = bbox_tensor;
        self->n = (vx_node)vsi_nn_kernel_selector( self->graph, "detect_post_box",
                                                 &box_tensors[0], _BOX_INPUT_NUM,
                                                 &box_tensors[2], _BOX_OUTPUT_NUM, param0 );

        param1 =vsi_nn_kernel_param_create();
        vsi_nn_kernel_param_add_int32( param1, "nms_type", p->nms_type);
        vsi_nn_kernel_param_add_int32( param1, "max_num_detections", p->max_num_detections);
        vsi_nn_kernel_param_add_int32( param1, "maximum_class_per_detection", p->maximum_class_per_detection);
        vsi_nn_kernel_param_add_int32( param1, "maximum_detection_per_class", p->maximum_detection_per_class);
        vsi_nn_kernel_param_add_float32( param1, "score_threshold", p->score_threshold);
        vsi_nn_kernel_param_add_float32( param1, "iou_threshold", p->iou_threshold);
        vsi_nn_kernel_param_add_int32( param1, "is_bg_in_label", p->is_bg_in_label);
        nms_tensors[0] = inputs[0];
        nms_tensors[1] = bbox_tensor;
        nms_tensors[2] = outputs[0];
        nms_tensors[3] = outputs[1];
        nms_tensors[4] = outputs[2];
        nms_tensors[5] = outputs[3];
        self->n = (vx_node)vsi_nn_kernel_selector( self->graph, "detect_post_nms",
                                                 &nms_tensors[0], _NMS_INPUT_NUM,
                                                 &nms_tensors[2], _NMS_OUTPUT_NUM, param1 );
        vsi_nn_ReleaseTensor( &bbox_tensor );
        vsi_nn_kernel_param_release( &param0 );
        vsi_nn_kernel_param_release( &param1 );
    }
    if( self->n )
    {
        status = VSI_SUCCESS;
    }

    return status;
} /* op_compute() */

static vsi_bool op_check
    (
    vsi_nn_node_t * self,
    vsi_nn_tensor_t ** inputs,
    vsi_nn_tensor_t ** outputs
    )
{
    BEGIN_IO_TYPE_DECL(DETECTION_POSTPROCESS, 3, 1)
        IO_TYPE(D_F32,  D_F32, D_F32, D_F32)
        IO_TYPE(D_U8|Q_ASYM,  D_U8|Q_ASYM, D_U8|Q_ASYM,  D_U8|Q_ASYM)
    END_IO_TYPE_DECL(DETECTION_POSTPROCESS)
    if (!VALIDATE_OP_IO_TYPES(DETECTION_POSTPROCESS, self, inputs, self->input.num, outputs, self->output.num))
    {
        char* desc = generate_op_io_types_desc(inputs,
                self->input.num, outputs, self->output.num);
        VSILOGE("Inputs/Outputs data type not support: %s", desc);
        destroy_op_io_types_desc(desc);
        return FALSE;
    }
    return TRUE;
} /* op_check() */

static vsi_bool op_setup
    (
    vsi_nn_node_t * self,
    vsi_nn_tensor_t ** inputs,
    vsi_nn_tensor_t ** outputs
    )
{
    if( VSI_NN_DIM_AUTO == outputs[0]->attr.dim_num )
    {
        vsi_nn_detection_postprocess_param * p;
        p = &(self->nn_param.detection_postprocess);

        outputs[0]->attr.dim_num = 2;
        outputs[0]->attr.size[0] = p->max_num_detections;
        outputs[0]->attr.size[1] = inputs[0]->attr.size[2];

        outputs[1]->attr.dim_num = 3;
        outputs[1]->attr.size[0] = 4;
        outputs[1]->attr.size[1] = p->max_num_detections;
        outputs[1]->attr.size[2] = inputs[0]->attr.size[2];

        outputs[2]->attr.dim_num = 2;
        outputs[2]->attr.size[0] = p->max_num_detections;
        outputs[2]->attr.size[1] = inputs[0]->attr.size[2];

        outputs[3]->attr.dim_num = 1;
        outputs[3]->attr.size[0] = inputs[0]->attr.size[2];
    }
    return TRUE;
} /* op_setup() */

#ifdef __cplusplus
extern "C" {
#endif
/* Registrar */
DEF_OP_REG
    (
    /* op_name    */ DETECTION_POSTPROCESS,
    /* init       */ NULL,
    /* compute    */ op_compute,
    /* deinit     */ vsi_nn_op_common_deinit,
    /* check      */ op_check,
    /* setup      */ op_setup,
    /* optimize   */ NULL,
    /* input_num  */ _INPUT_NUM,
    /* output_num */ _OUTPUT_NUM
    );
#ifdef __cplusplus
}
#endif
