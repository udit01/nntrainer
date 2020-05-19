/**
 * Copyright (C) 2020 Samsung Electronics Co., Ltd. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *   http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/**
 * @file nntrainer.h
 * @date 02 April 2020
 * @brief NNTrainer C-API Header.
 *        This allows to construct and control NNTrainer Model.
 * @see	https://github.com/nnstreamer/nntrainer
 * @author Jijoong Moon <jijoong.moon@samsung.com>
 * @bug No known bugs except for NYI items
 */

#ifndef __TIZEN_MACHINELEARNING_NNTRAINER_H__
#define __TIZEN_MACHINELEARNING_NNTRAINER_H__

#include <stdbool.h>
#include <stddef.h>

#include <tizen_error.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/**
 * @addtogroup CAPI_ML_NNTRAINER_MODULE
 * @{
 */

/**
 * @brief A handle of an NNTrainer model.
 * @since_tizen 6.x
 */
typedef void *ml_nnmodel_h;

/**
 * @brief A handle of an NNTrainer layer.
 * @since_tizen 6.x
 */
typedef void *ml_nnlayer_h;

/**
 * @brief A handle of an NNTrainer optimizer.
 * @since_tizen 6.x
 */
typedef void *ml_nnopt_h;

/**
 * @brief Enumeration for the error codes of NNTrainer.
 * @since_tizen 6.x
 */
typedef enum {
  ML_ERROR_NONE = TIZEN_ERROR_NONE,                                   /**< Success! */
  ML_ERROR_INVALID_PARAMETER = TIZEN_ERROR_INVALID_PARAMETER,         /**< Invalid parameter */
  ML_ERROR_UNKNOWN = TIZEN_ERROR_UNKNOWN,                             /**< Unknown error */
  ML_ERROR_TIMED_OUT = TIZEN_ERROR_TIMED_OUT,                         /**< Time out */
  ML_ERROR_NOT_SUPPORTED = TIZEN_ERROR_NOT_SUPPORTED,                 /**< The feature is not supported */
  ML_ERROR_PERMISSION_DENIED = TIZEN_ERROR_PERMISSION_DENIED,         /**< Permission denied */
  ML_ERROR_OUT_OF_MEMORY = TIZEN_ERROR_OUT_OF_MEMORY,                 /**< Out of memory (Since 6.0) */
  ML_ERROR_CANNOT_ASSIGN_ADDRESS = TIZEN_ERROR_CANNOT_ASSIGN_ADDRESS, /**< Cannot assign requested address */
  ML_ERROR_BAD_ADDRESS = TIZEN_ERROR_BAD_ADDRESS,                     /**< Bad Address */
} ml_error_e;

/**
 * @brief Enumeration for the neural network layer type of NNTrainer.
 * @since_tizen 6.x
 */
typedef enum {
  ML_LAYER_TYPE_INPUT = 0, /**< Input Layer */
  ML_LAYER_TYPE_FC,        /**< Fully Connected Layer */
  ML_LAYER_TYPE_UNKNOWN    /**< Unknown Lyaer */
} ml_layer_type_e;


/**
 * @brief Constructs the neural network model.
 * @details Use this function to create Neural Netowrk Model.
 * @since_tizen 6.x
 * @param[out] model The NNTrainer Model handler from the given description.
 * @return @c 0 on success. Otherwise a negative error value.
 * @retval #ML_ERROR_NONE Successful.
 * @retval #ML_ERROR_CANNOT_ASSIGN_ADDRESS Cannot assign object.
 */
int ml_nnmodel_construct(ml_nnmodel_h *model);

/**
 * @brief Constructs the neural network model with configuration file.
 * @details Use this function to create Neural Netowrk Model.
 * @since_tizen 6.x
 * @param[in] model_conf The location of nntrainer model configuration file.
 * @param[out] model The NNTrainer Model handler from the given description.
 * @return @c 0 on success. Otherwise a negative error value.
 * @retval #ML_ERROR_NONE Successful.
 * @retval #ML_ERROR_INVALID_PARAMETER Invalid parameter.
 * @retval #ML_ERROR_CANNOT_ASSIGN_ADDRESS Cannot assign object.
 */
int ml_nnmodel_construct_with_conf(const char *model_conf, ml_nnmodel_h *model);

/**
 * @brief initialize the neural network model with configuration file.
 * @details Use this function to initialize neural network model
 * @since_tizen 6.x
 * @param[in] model The NNTrainer model handler from the given description.
 * @return @c 0 on success. Otherwise a negative error value.
 * @retval #ML_ERROR_NONE Successful.
 * @retval #ML_ERROR_INVALID_PARAMETER Invalid Parameter.
 */
int ml_nnmodel_compile_with_conf(ml_nnmodel_h model);

/**
 * @brief initialize the neural network model.
 * @details Use this function to initialize neural network model
 * @since_tizen 6.x
 * @param[in] model The NNTrainer model handler from the given description.
 * @param[in] optimizer The NNTrainer optimizer handler from the given description.
 * @param[in] ... hyper parmeter for compile model
 * @return @c 0 on success. Otherwise a negative error value.
 * @retval #ML_ERROR_NONE Successful.
 * @retval #ML_ERROR_INVALID_PARAMETER Invalid Parameter.
 */
int ml_nnmodel_compile(ml_nnmodel_h model, ml_nnopt_h optimizer, ...);

/**
 * @brief train the neural network model.
 * @details Use this function to train neural network model
 * @since_tizen 6.x
 * @param[in] model The NNTrainer model handler from the given description.
 * @param[in] ...  hyper parmeter for train model
 * @return @c 0 on success. Otherwise a negative error value.
 * @retval #ML_ERROR_NONE Successful.
 * @retval #ML_ERROR_INVALID_PARAMETER Invalid Parameter.
 */
int ml_nnmodel_train_with_file(ml_nnmodel_h model, ...);

/**
 * @brief train the neural network model.
 * @details Use this function to train neural network model
 * @since_tizen 6.x
 * @param[in] model The NNTrainer model handler from the given description.
 * @param[in] train_func function pointer for train
 * @param[in] val_func function pointer for val
 * @param[in] test_func function pointer for test
 * @param[in] ...  hyper parmeter for train model
 * @return @c 0 on success. Otherwise a negative error value.
 * @retval #ML_ERROR_NONE Successful.
 * @retval #ML_ERROR_INVALID_PARAMETER Invalid Parameter.
 */
int ml_nnmodel_train_with_generator(ml_nnmodel_h model,
                                    bool (*train_func)(float *, float *, int *),
                                    bool (*val_func)(float *, float *, int *),
                                    bool (*test_func)(float *, float *, int *),
                                    ...);

/**
 * @brief Destructs the neural network model.
 * @details Use this function to delete Neural Netowrk Model.
 * @since_tizen 6.x
 * @param[in] model The NNTrainer model handler from the given description.
 * @return @c 0 on success. Otherwise a negative error value.
 * @retval #ML_ERROR_NONE Successful.
 * @retval #ML_ERROR_INVALID_PARAMETER Invalid Parameter.
 */
int ml_nnmodel_destruct(ml_nnmodel_h model);

/**
 * @brief add layer into the neural network model
 * @details Use this function to add layer
 * @since_tizen 6.x
 * @param[out] model The NNTrainer model handler from the given description.
 * @param[int] layer The NNTrainer layer handler
 * @return @c 0 on success. Otherwise a negative error value.
 * @retval #ML_ERROR_NONE Successful.
 * @retval #ML_ERROR_INVALID_PARAMETER Invalid Parameter.
 */
int ml_nnmodel_add_layer(ml_nnmodel_h model, ml_nnlayer_h layer);

/**
 * @brief Create the neural network layer.
 * @details Use this function to create Neural Netowrk Layer.
 * @since_tizen 6.x
 * @param[out] layer The NNTrainer Layer handler from the given description.
 * @param[in]  type The NNTrainer Layer type
 * @return @c 0 on success. Otherwise a negative error value.
 * @retval #ML_ERROR_NONE Successful.
 * @retval #ML_ERROR_INVALID_PARAMETER Invalid parameter.
 * @retval #ML_ERROR_CANNOT_ASSIGN_ADDRESS Cannot assign object.
 */
int ml_nnlayer_create(ml_nnlayer_h *layer, ml_layer_type_e type);

/**
 * @brief Delete the neural network layer.
 * @details Use this function to delete Neural Netowrk Layer.
 * @since_tizen 6.x
 * @param[in] layer The NNTrainer layer handler from the given description.
 * @return @c 0 on success. Otherwise a negative error value.
 * @retval #ML_ERROR_NONE Successful.
 * @retval #ML_ERROR_INVALID_PARAMETER Invalid Parameter.
 */
int ml_nnlayer_delete(ml_nnlayer_h layer);

/**
 * @brief Set the neural network layer Property.
 * @details Use this function to set Neural Netowrk Layer Property.
 * @since_tizen 6.x
 * @param[in] layer The NNTrainer Layer handler from the given description.
 * @param[in]  ... Property values with NULL for termination.
 * @return @c 0 on success. Otherwise a negative error value.
 * @retval #ML_ERROR_NONE Successful.
 * @retval #ML_ERROR_INVALID_PARAMETER Invalid parameter.
 */
int ml_nnlayer_set_property(ml_nnlayer_h layer, ...);

/**
 * @brief Create the neural network optimizer.
 * @details Use this function to create Neural Netowrk Optimizer.
 * @since_tizen 6.x
 * @param[out] layer The NNTrainer Optimizer handler from the given description.
 * @param[in]  type The NNTrainer Optimizer type
 * @return @c 0 on success. Otherwise a negative error value.
 * @retval #ML_ERROR_NONE Successful.
 * @retval #ML_ERROR_INVALID_PARAMETER Invalid parameter.
 */
int ml_nnoptimizer_create(ml_nnopt_h *opt, const char *type);

/**
 * @brief Delete the neural network optimizer.
 * @details Use this function to delete Neural Netowrk Optimizer.
 * @since_tizen 6.x
 * @param[in] layer The NNTrainer optimizer handler from the given description.
 * @return @c 0 on success. Otherwise a negative error value.
 * @retval #ML_ERROR_NONE Successful.
 * @retval #ML_ERROR_INVALID_PARAMETER Invalid Parameter.
 */
int ml_nnoptimizer_delete(ml_nnopt_h opt);
  

/**
 * @brief Set the neural network optimizer property.
 * @details Use this function to set Neural Netowrk Optimizer Property.
 * @since_tizen 6.x
 * @param[in] layer The NNTrainer Optimizer handler from the given description.
 * @param[in]  ... Property values with NULL at the end.
 * @return @c 0 on success. Otherwise a negative error value.
 * @retval #ML_ERROR_NONE Successful.
 * @retval #ML_ERROR_INVALID_PARAMETER Invalid parameter.
 */
int ml_nnoptimizer_set_property(ml_nnopt_h opt,...);

 /**
 * @}
 */
#ifdef __cplusplus
}

#endif /* __cplusplus */
#endif /* __TIZEN_MACHINELEARNING_NNTRAINER_H__ */
