#include <cmath>
#include <stdlib.h>
#include "runin/constants.h"
#include "runin/critical_field.h"
#include "runin/products.h"

/* Critical field warning

The module outputs an integer value (0 or 1) which indicates, whether electric field is above the critical level, thus runaway generation is possible. When the electric field exceeds the critical level this warning raises, a value of 1 is outputted. However it does not mean that runaway electrons are present, the warning only signs the possibility.

*/

int is_field_critical(profile pro, double rho_max) {

	for (std::vector<cell>::iterator it = pro.begin(); it != pro.end(); ++it) {
		if ( (abs(it->electric_field)) > (calculate_critical_field(it->electron_density, it->electron_temperature) )
		  && (it->rho < rho_max) )
			return 1;
	}

	return 0;
}

double calculate_critical_field(double electron_density, double electron_temperature) {

	// Coulomb logarithm
	double coulomb_log = calculate_coulomb_log(electron_density, electron_temperature);

	// Critical field	
	return electron_density * e3 * coulomb_log / pi_e02_me_4_c2;
}

double calculate_coulomb_log(double electron_density, double electron_temperature) {

	// Coulomb logarithm	
	return 14.9 - 0.5 * log(electron_density * 1e-20) + log(electron_temperature * 1e-3);
}

double calculate_dreicer_field(double electron_density, double electron_temperature){

	// Dreicer field
	return  calculate_critical_field(electron_density, electron_temperature) * me_c2 / electron_temperature / ITM_EV ;
}

double calculate_thermal_electron_collision_time(double electron_density, double electron_temperature){

	double coulomb_log = calculate_coulomb_log(electron_density, electron_temperature);
			
	double therm_speed = sqrt(2*electron_temperature*ITM_EV/ITM_ME);

	return pi_4_e02_me2__e4 * pow(therm_speed,3.0) / (electron_density * coulomb_log);	
}
