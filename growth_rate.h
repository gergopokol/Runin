#ifndef GROWTH_RATE_H_
#define GROWTH_RATE_H_

#include "constants.h"

int is_growth_rate_over_limit(profile pro, double limit);

double calculate_growth_rate(double electron_density, double electron_temperature,
		double effective_charge, double electric_field);
		
double calculate_thermal_electron_collision_time(double electron_density, double electron_temperature);

#endif /* GROWTH_RATE_H_ */
