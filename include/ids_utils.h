#ifndef IDS_UTILS_H_
#define IDS_UTILS_H_

#include <UALClasses.h>
#include "plasma_structures.h"

bool equal(double a, double b, double tolerance);

int binary_search(const Array<double, 1> &array, double search_key);

double interpolate(const Array<double, 1> &x, const Array<double, 1> &y, double xa);

double fill_rho_tor_norm(const IdsNs::IDS::core_profiles &core_profiles, const IdsNs::IDS::equilibrium &equilibrium, int cpindex, int timeindex);
		
plasma_profile ids_to_profile(const IdsNs::IDS::core_profiles &core_profiles, const IdsNs::IDS::equilibrium &equilibrium, int timeindex);

#endif /* IDS_UTILS_H_ */
