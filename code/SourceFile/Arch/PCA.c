#include "PCA.h"


uint16_t   PCA_Value;


void Pca_Init(void)
{
    CCON = 0;                       // Initial PCA control register
                                    // PCA timer stop running
                                    // Clear CF flag
                                    // Clear all module interrupt flag
    CL = 0;                         // Reset PCA base timer
    CH = 0;
    CMOD = 0x00;                    // Set PCA timer clock source as Fosc/12
                                    // Disable PCA timer overflow interrupt
    PCA_Value = T1000Hz;
    CCAP0L = PCA_Value;
    CCAP0H = PCA_Value >> 8;        // Initial PCA module-0
    
    CCAPM0 = 0x49;                  // PCA module-0 work in 16-bool timer mode and enable PCA interrupt
    
    PPCA = 1;
    
    CR = 0;                         // PCA timer stop
}






