#include <cmath>
#include <stdlib.h>
#include "constants.h"
#include "critical_field.h"
#include "products.h"

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

	double coulomb_log = calculate_coulomb_log(electron_density, electron_temperature);

	//! \return \a REQ-3: Critical field
	/*!
	\f[
	E_\mathrm{c} = \frac{n_\mathrm{e} e^3 \ln \Lambda}{4\pi\epsilon_0^2 m_\mathrm{e} c^2}
	\f]
	*/

	return electron_density * e3 * coulomb_log / pi_e02_me_4_c2;
}

double calculate_coulomb_log(double electron_density, double electron_temperature) {

	//! \a REQ-4: Coulomb logarithm
	/*!
	\f[
	\ln \Lambda = 14.9-0.5 \cdot \log \left(n_e \cdot 10^{-20}\right) + \log \left(t_e \cdot 10^{-3}\right) .
	\f]
	*/

	return 14.9 - 0.5 * log10(electron_density * 1e-20) + log10(electron_temperature * 1e-3);
}

double calculate_dreicer_field(double thermal_electron_collision_time, double electron_temperature){

//! \a REQ-3: Dreicer field
	/*!
\f[
    E_D = \frac{m_\mathrm{e}^2 v^3}{e\tau \cdot T_\mathrm{e}}
\f]
*/

	return me2_c3__e /  (thermal_electron_collision_time * electron_temperature * ITM_EV);
}

double calculate_thermal_electron_collision_time(double electron_density, double electron_temperature){

	double coulomb_log = calculate_coulomb_log(electron_density, electron_temperature);
			
	double therm_speed = sqrt(2*electron_temperature*ITM_EV/ITM_ME);

	return pi_4_e02_me2__e4 * pow(therm_speed,3.0) / (electron_density * coulomb_log);	
}
