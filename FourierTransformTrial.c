#include "main.h"
#include "stm32f4xx.h"
#include <math.h>
#include <stdio.h>
#include "arm_math.h"              



float32_t buffer_input[1024];
float32_t buffer_input_copy[256];
float32_t buffer_output[1024];
float32_t buffer_output_mag[1024];
float32_t buffer_output_mag_copy[256];
float32_t maxvalue;
uint32_t  maxvalueindex;

arm_rfft_instance_f32 S;
arm_cfft_radix4_instance_f32 S_CFFT;

int main(void)
{

 unsigned int freq, i, z;
 float dt;

 freq = 128;
 dt = 0.001;

 for(i=0; i<512; ++i)
 buffer_input[i] = (float32_t) 30*sin(2*PI*freq*i*dt) + (float32_t) 10*cos(2*PI*freq*2*i*dt);


 arm_rfft_init_f32(&S, &S_CFFT, 512, 0, 1);

 // fft'yi hesaplama
 arm_rfft_f32(&S, buffer_input, buffer_output);

 // Genliklerin hesaplanmasi (yukaridaki buldugumuz X[k] katsayilar)
 arm_cmplx_mag_f32(buffer_output, buffer_output_mag, 512);

 // Maksimum genlik ve indexi hesaplama
 arm_max_f32(buffer_output_mag, 512, &maxvalue, &maxvalueindex);

 
 for(i=0; i<512; ++i)
  buffer_output_mag[i] = 100*buffer_output_mag[i]/maxvalue;

return 0;

}