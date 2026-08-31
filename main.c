/******************************************************************************
* File Name:   main.c
*
* Description: This is the source code for the PSOC Control C1 MCU: PRNG for ModusToolbox.
*
* Related Document: See README.md
*
*******************************************************************************
* (c) 2026, Infineon Technologies AG, or an affiliate of Infineon
* Technologies AG. All rights reserved.
* This software, associated documentation and materials ("Software") is
* owned by Infineon Technologies AG or one of its affiliates ("Infineon")
* and is protected by and subject to worldwide patent protection, worldwide
* copyright laws, and international treaty provisions. Therefore, you may use
* this Software only as provided in the license agreement accompanying the
* software package from which you obtained this Software. If no license
* agreement applies, then any use, reproduction, modification, translation, or
* compilation of this Software is prohibited without the express written
* permission of Infineon.
*
* Disclaimer: UNLESS OTHERWISE EXPRESSLY AGREED WITH INFINEON, THIS SOFTWARE
* IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* INCLUDING, BUT NOT LIMITED TO, ALL WARRANTIES OF NON-INFRINGEMENT OF
* THIRD-PARTY RIGHTS AND IMPLIED WARRANTIES SUCH AS WARRANTIES OF FITNESS FOR A
* SPECIFIC USE/PURPOSE OR MERCHANTABILITY.
* Infineon reserves the right to make changes to the Software without notice.
* You are responsible for properly designing, programming, and testing the
* functionality and safety of your intended application of the Software, as
* well as complying with any legal requirements related to its use. Infineon
* does not guarantee that the Software will be free from intrusion, data theft
* or loss, or other breaches ("Security Breaches"), and Infineon shall have
* no liability arising out of any Security Breaches. Unless otherwise
* explicitly approved by Infineon, the Software may not be used in any
* application where a failure of the Product or any consequences of the use
* thereof can reasonably be expected to result in personal injury.
*******************************************************************************/

#include "cybsp.h"
#include "cy_utils.h"
#include "cy_retarget_io.h"

/*******************************************************************************
* Macros
********************************************************************************/
#define SCREEN_HEADER "\r\n__________________________________________________"\
           "____________________________\r\n*\t PSOC Control C1 MCU: PRNG: "\
           "Pseudo Random Number Generation\r\n*\r\n*\tThis code example "\
           "demonstrates generating a random numbers\r\n*\tusing the"\
           " Pseudo Random Number generation feature of MCU\r\n*\t"\
           "cryptography block\r\n*\r\n*\tUART Terminal Settings\tBaud Rate:"\
           "115200 bps 8N1 \r\n*"\
           "\r\n__________________________________________________"\
           "____________________________\r\n\n"

#define SCREEN_HEADER1             "\r\n================================================="\
                                   "=============================\r\n"

/* \x1b[2J\x1b[;H - ANSI ESC sequence for clear screen */
#define CLEAR_SCREEN               "\x1b[2J\x1b[;H"

#define PRNG_DELAY_BW_ITERATION    1000

#define PRNG_DELAY                 5

#define LEN_RANDOM_NUM             10

/*******************************************************************************
* Function Name: main
********************************************************************************
* Summary:
* This is the main function for CM0 CPU. It configures the PRNG block to
* generate random number. A new Random number is generated every 5 ms.
* This process repeats every 5 seconds
*
* Parameters:
*  void
*
* Return:
*  int
*
*******************************************************************************/

int main(void)
{
    cy_rslt_t result;

    /* Initialize the device and board peripherals */
    result = cybsp_init();
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    /* Initialize retarget-io to use the debug UART port */
    result = cy_retarget_io_init(CYBSP_DEBUG_UART_HW);

    /* retarget-io init failed. Stop program execution */
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    /* \x1b[2J\x1b[;H - ANSI ESC sequence for clear screen */
    printf(CLEAR_SCREEN);

    printf(SCREEN_HEADER);

    for (;;)
    {
            printf("\nPRN Generated in BYTES\r\n");

            /* Loop for showing the generated random number in BYTES. */
            for (uint32_t i = 1U; i <= LEN_RANDOM_NUM; i++)
            {
                Cy_Delay(PRNG_DELAY);

                /* Checks the validity of the generated random data */
                if(Cy_PRNG_CheckValidStatus())
                {
                    /* the function gives the generated random number by returning the content of WORD register. */
                    printf("%02u: Result in BYTES is 0x%02X \r\n", (unsigned int)i, (uint8_t) Cy_PRNG_GetPseudoRandomNumber());
                }
            }

            /* The function sets the random data block size as byte or word */
            Cy_PRNG_SetRandomDataBlockSize(CY_PRNG_RDBS_WORD);

            printf("\nPRN Generated in WORDS\r\n");

            /* Loop for showing the generated random number in WORDS. */
            for (uint32_t j = 1U; j <= LEN_RANDOM_NUM; j++)
            {
                Cy_Delay(PRNG_DELAY);

                /* Checks the validity of the generated random data */
                if(Cy_PRNG_CheckValidStatus())
                {
                    /* the function gives the generated random number by returning the content of WORD register. */
                    printf("%02u: Result in WORDS is 0x%02X \r\n", (unsigned int)j, (uint16_t) Cy_PRNG_GetPseudoRandomNumber());
                }
            }

            printf(SCREEN_HEADER1);

            Cy_Delay(PRNG_DELAY_BW_ITERATION);
    }
}
/* [] END OF FILE */
