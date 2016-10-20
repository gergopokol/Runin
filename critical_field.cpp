#include <cmath>
#include <stdlib.h>
#include "critical_field.h"
#include "constants.h"


//! \f$ e^3 \f$
double e3 = pow(ITM_QE, 3);

//! \f$ 4\pi\epsilon_0^2 m_\mathrm{e} c^2 \f$
double pi_e02_me_4_c2 = ITM_PI * pow(ITM_EPS0, 2) * ITM_ME * 4.0 * pow(ITM_C, 2);



/*! Critical field warning

\details The module outputs an integer value (0 or 1) which indicates, whether electric field is above the critical level, thus runaway generation is possible. When the electric field exceeds the critical level this warning raises, a value of 1 is outputted. However it does not mean that runaway electrons are present, the warning only signs the possibility.

\param pro profile


 4.1.3 Functional Requirements
\return \a REQ-1: If a radius exists where electric field is above critical, returns 1.	
\return \a REQ-2: If electric field is below critical across the whole profile, returns 0.
\return \a REQ-3: Critical electric field 

*/
int is_field_critical(profile pro) {

	//! maximal normalised minor radius
	double rho_max = 0.95;

	for (std::vector<cell>::iterator it = pro.begin(); it != pro.end(); ++it) {
		if ( (calculate_critical_field(it->electron_density, it->electron_temperature) > (abs(it->electric_field)))
		  && (it->rho < rho_max) )
			return 1;
	}

	return 0;
}

double calculate_critical_field(double electron_density, double electron_temperature) {
	
	//! \a REQ-4: Coulomb logarithm
	/*!
	\f[
		\ln \Lambda = 14.9-0.5 \cdot \log \left(n_e \cdot 10^{-20}\right) + \log \left(t_e \cdot 10^{-3}\right) .
	\f]
	*/
	double coulomb_log = 14.9 - 0.5 * log(electron_density * 1e-20)
			+ log(electron_temperature * 1e-3);


	//! \return \a REQ-3: Critical field
	/*!
	\f[
		E_\mathrm{c} = \frac{n_\mathrm{e} e^3 \ln \Lambda}{4\pi\epsilon_0^2 m_\mathrm{e} c^2}
	\f]
	*/
	return electron_density * e3 * coulomb_log / pi_e02_me_4_c2;
}
