/* dotp.h */

#ifndef _C_DOTP_H
#define _C_DOTP_H

// default vector length
#define DEFAULT_VECTOR_SIZE  128

// assembly function definition
extern float dotp(float *p, float *q, unsigned int N);

#endif // _C_DOTP_H

/* end of file */
    // set up for the dev board
    GPIO_setMasterCore(43, GPIO_CORE_CPU1);
    GPIO_setPinConfig(GPIO_43_SCIRXDA);
    GPIO_setDirectionMode(43, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(43, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(43, GPIO_QUAL_ASYNC);
    //
    // GPIO18 is the SCI Tx pin.
    //

    // Set up for the dev board
    GPIO_setMasterCore(42, GPIO_CORE_CPU1);
    GPIO_setPinConfig(GPIO_42_SCITXDA);
    GPIO_setDirectionMode(42, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(42, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(42, GPIO_QUAL_ASYNC);