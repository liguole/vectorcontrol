/*
Copyright (C) 2014-2015 Thiemar Pty Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <stdint.h>

void __attribute__((weak)) default_handler(void) {
    while (1u);
}

void __attribute__ ((weak, alias ("default_handler")))
stm32_reserved(void);
void __start(void) __attribute__ ((no_instrument_function));

/* Function prototypes for each defined vector */
#define UNUSED(x)
#define VECTOR(x, y) void __attribute__ ((weak, alias ("default_handler"))) \
                     x(void);

/* Standard vectors */
VECTOR(stm32_nmi, 2)
VECTOR(stm32_hardfault, 3)
VECTOR(stm32_mpu, 4)
VECTOR(stm32_busfault, 5)
VECTOR(stm32_usagefault, 6)
UNUSED(7)
UNUSED(8)
UNUSED(9)
UNUSED(10)
VECTOR(stm32_svcall, 11)
VECTOR(stm32_dbgmonitor, 12)
UNUSED(13)
VECTOR(stm32_pendsv, 14)
VECTOR(stm32_systick, 15)

#if defined(CONFIG_STM32_STM32F302)
    /* STM32F30X-specific vectors */
    #include <stm32f30xxx_vectors.h>
#elif defined(CONFIG_STM32_STM32F446)
    /* STM32F44X-specific vectors */
    #include <stm32f44xxx_vectors.h>
#else
    #pragma error "Invalid chip"
#endif /* defined(CONFIG_STM32_STM32F302) */

#undef VECTOR
#undef UNUSED


extern uint32_t __stack;

typedef void (* const vector_entry)(void);

__attribute__ ((section(".app_vectors"),used))
vector_entry app_vectors[] = {
    (vector_entry)&__stack,
    __start,

#define UNUSED(x) (vector_entry)(stm32_reserved),
#define VECTOR(x, y) (vector_entry)x,

/* Standard vectors */
VECTOR(stm32_nmi, 2)
VECTOR(stm32_hardfault, 3)
VECTOR(stm32_mpu, 4)
VECTOR(stm32_busfault, 5)
VECTOR(stm32_usagefault, 6)
VECTOR(stm32_reserved, 7)
VECTOR(stm32_reserved, 8)
VECTOR(stm32_reserved, 9)
VECTOR(stm32_reserved, 10)
VECTOR(stm32_svcall, 11)
VECTOR(stm32_dbgmonitor, 12)
VECTOR(stm32_reserved, 13)
VECTOR(stm32_pendsv, 14)
VECTOR(stm32_systick, 15)

#if defined(CONFIG_STM32_STM32F302)
    /* STM32F30X-specific vectors */
    #include <stm32f30xxx_vectors.h>
#elif defined(CONFIG_STM32_STM32F446)
    /* STM32F44X-specific vectors */
    #include <stm32f44xxx_vectors.h>
#else
    #pragma error "Invalid chip"
#endif /* defined(CONFIG_STM32_STM32F302) */

#undef VECTOR
#undef UNUSED
};
