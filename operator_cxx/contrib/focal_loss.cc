/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/*!
 * \file focal_loss.cc
 * \brief
 * \author Chenxia Han
*/

#include "./focal_loss-inl.h"

namespace mxnet {
namespace op {

template<>
Operator *CreateOp<cpu>(FocalLossParam param, int dtype) {
  Operator *op = nullptr;
  MSHADOW_REAL_TYPE_SWITCH(dtype, DType, {
    op = new FocalLossOp<cpu, DType>(param);
  });
  return op;
}

Operator *FocalLossProp::CreateOperatorEx(Context ctx, std::vector<TShape> *in_shape,
                                         std::vector<int> *in_type) const {
  std::vector<TShape> out_shape, aux_shape;
  std::vector<int> out_type, aux_type;
  CHECK(InferType(in_type, &out_type, &aux_type));
  CHECK(InferShape(in_shape, &out_shape, &aux_shape));
  DO_BIND_DISPATCH(CreateOp, param_, in_type->at(0));
}

DMLC_REGISTER_PARAMETER(FocalLossParam);

MXNET_REGISTER_OP_PROPERTY(_contrib_FocalLoss, FocalLossProp)
.describe("Focal loss for dense object detection")
.add_argument("data", "NDArray-or-Symbol", "Data")
.add_argument("label", "NDArray-or-Symbol", "Label")
.add_arguments(FocalLossParam::__FIELDS__());

}  // namespace op
}  // namespace mxnet
