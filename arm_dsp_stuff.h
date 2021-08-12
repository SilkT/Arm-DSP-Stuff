/**
 * This is a library of mainly DSP focused functions that I use in my projects.
 * Many functions depend on CMSIS DSP library but they can be turned off in dsp_stuff_config.h.
 * 
 * https://github.com/SilkT/uart_sens_hal
 *
 * (c) 2021 SilkT
 */

#ifndef __ARM_DSP_STUFF__
#define __ARM_DSP_STUFF__

#include <stdint.h>
#include <math.h>

#include "dsp_stuff_config.h"
#if DSP_STUFF_USE_ARM_MATH
#include "arm_math.h"
#endif

#define _USE_MATH_DEFINES
#ifndef M_PI
#define M_PI  3.14159
#endif

#define FFT_DOBITREVERSE 1

#if DSP_STUFF_USE_ARM_MATH
/**
 * @brief   A wrapper for CMSIS function that doesn't change the input sample but uses more RAM
 * 
 * @param	in - input vector
 * @param 	out - output vector
 * @param	len	- number of elements in vectors
 * @param   dir - direction of FFT
 */
void dofft_f32(float* in, float* out, uint32_t len, uint8_t dir);

/**
 * @brief   Cross correlation between two float32 vectors
 *
 * @param	in1 - first input vector
 * @param	in2	- second input vector
 * @param	len	- number of elements in vectors
 * @param 	out - output vector
 */
void fftcorrelate_f32(float32_t* in1, float32_t* in2, uint32_t len, float32_t* out);

#endif


/**
 * @brief   Blackman filter implementation by Serhii Melnik
 * 
 * @param	in - input vector
 * @param 	out - output vector
 * @param	len	- number of elements in vectors
 */
void filter_blackman_f32(float *sample, int sample_length, float alpha);

#endif
