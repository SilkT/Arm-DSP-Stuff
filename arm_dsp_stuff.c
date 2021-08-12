#include "arm_dsp_stuff.h"

#if DSP_STUFF_USE_ARM_MATH
/**
 * @brief   A wrapper for CMSIS function that doesn't change the input sample but uses more RAM
 * 
 * @param	in - input vector
 * @param 	out - output vector
 * @param	len	- number of elements in vectors
 * @param   dir - direction of FFT
 */
void dofft_f32(float* in, float* out, uint32_t len, uint8_t dir)
{
	static float32_t in_temp[FFT_SIZE];
	arm_rfft_fast_instance_f32 S;
	arm_rfft_fast_init_f32(&S, len);
	switch (dir) {
		case 1:
			arm_rfft_fast_f32(&S, in, out, dir);
			break;
		default:
			arm_copy_f32(in, in_temp, len);
			arm_rfft_fast_f32(&S, in_temp, out, dir);
			break;
	}
}

/**
 * @brief   Cross correlation between two float32 vectors
 *
 * @param	in1 - first input vector
 * @param	in2	- second input vector
 * @param	len	- number of elements in vectors
 * @param 	out - output vector
 */
void fftcorrelate_f32(float32_t* in1, float32_t* in2, uint32_t len, float32_t* out)
{
	static float32_t in1_f[FFT_SIZE*2];
	static float32_t in2_f[FFT_SIZE*2];
	dofft_f32(in1, in1_f, len, 0);
	arm_cmplx_conj_f32(in1_f, in1_f, FFT_SIZE);
	dofft_f32(in2, in2_f, len, 0);
	arm_cmplx_mult_cmplx_f32(in1_f, in2_f, in1_f, FFT_SIZE);
	dofft_f32(in1_f, out, len, 1);
}

#endif


/**
 * @brief   Blackman filter implementation by Serhii Melnik
 * 
 * @param	in - input vector
 * @param 	out - output vector
 * @param	len	- number of elements in vectors
 */
void filter_blackman_f32(float *sample, int sample_length, float alpha)
{
    //filter coefficients
    float a0 = (1-alpha)*0.5;
    float a1 = 0.5;
    float a2 = alpha*0.5;
    
    float k = 2*M_PI/sample_length;
    float k2 = k*2;

    //filtering
    float arg = 0, arg2 = 0;
    for(int i=0; i<sample_length; i++)
    {
        arg += k;
        arg2 += k2;
        sample[i] *= a0 - a1*cos(arg) + a2*cos(arg2);
    }
}
