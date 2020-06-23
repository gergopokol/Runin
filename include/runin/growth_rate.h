#ifndef GROWTH_RATE_H_
#define GROWTH_RATE_H_

#include "cell.h"

int is_growth_rate_over_limit(profile pro, double limit, double rho_max);

double calculate_growth_rate(double electron_density, double electron_temperature,
							 double effective_charge, double electric_field);

#endif /* GROWTH_RATE_H_ */
