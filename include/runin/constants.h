#ifdef ITM_CONSTANTS
    #include <itm_constants.h>
    
#elif IMAS_CONSTANTS
    #include <imas_constants.h>
    
    // value of pi
    #define ITM_PI		IMAS_PI

    // speed of light [m/s]
    #define ITM_C		IMAS_C

    // electron volt [eV]
    #define ITM_EV		IMAS_EV

    // elementary charge [coulomb]
    #define ITM_QE		ITM_EV

    // electron mass [kg]
    #define ITM_ME		IMAS_ME

    // vacuum permeability
    #define ITM_MU0		IMAS_MU0

    // vacuum permittivity
    #define ITM_EPS0	IMAS_EPS0    
    
    // ERROR CODE
    #define ITM_INVALID_INT	-999999999
    
#else
    // value of pi
    #define ITM_PI		3.141592653589793238462643383280

    // speed of light [m/s]
    #define ITM_C		2.99792458e8

    // electron volt [eV]
    #define ITM_EV		1.602176565e-19

    // elementary charge [coulomb]
    #define ITM_QE		ITM_EV

    // electron mass [kg]
    #define ITM_ME		9.10938291e-31

    // vacuum permeability
    #define ITM_MU0		4.0e-7 * ITM_PI

    // vacuum permittivity
    #define ITM_EPS0	1.0 / (ITM_MU0 * ITM_C * ITM_C)

    // ERROR CODE
    #define ITM_INVALID_INT	-999999999

#endif
