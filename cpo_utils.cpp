#include <stdexcept>
#include "cpo_utils.h"

/*!
\param a
\param b
\param tolerance

\details
\f[
	2 \cdot \left| a-b\right| \le \left( |a| + |b| \right) \cdot tolerance
\f]
*/
bool equal(double a, double b, double tolerance) {
	return abs(a - b) * 2.0 <= (abs(a) + abs(b)) * tolerance;
}

//! Binary search 

int binary_search(const Array<double, 1> &array, int first, int last, double search_key) {
	if (first == last)
		return first;

	if (first > last)
		return -1;

	int mid = (first + last) / 2;
	if (array(mid) <= search_key && search_key < array(mid + 1))
		return mid;

	if (search_key < array(mid))
		return binary_search(array, first, mid - 1, search_key);
	else
		return binary_search(array, mid + 1, last, search_key);
}

int binary_search(const Array<double, 1> &array, double search_key) {
	return binary_search(array, 0, array.rows() - 2, search_key);
}

/*!
linear interpolation

\f[
	y_a = y_i + \frac{y_{i+1}-y_i}{x_{i+1}-x_i}\cdot(x_a -x_i)
\f]

*/

double interpolate(const Array<double, 1> &x, const Array<double, 1> &y, double xa) {

	int rows = x.rows();
	if (rows != y.rows())
		throw std::invalid_argument("Number of rows is different in arrays to interpolate.");

	if (xa <= x(0))
		return y(0);
	if (xa >= x(x.rows() - 1))
		return y(y.rows() - 1);

	int index = binary_search(x, xa);
	if (index < 0)
		throw std::invalid_argument("Binary search failed.");

	return y(index) + (y(index + 1) - y(index)) / (x(index + 1) - x(index)) * (xa - x(index));
}

profile cpo_to_profile(const ItmNs::Itm::coreprof &coreprof, const ItmNs::Itm::coreimpur &coreimpur,
		const ItmNs::Itm::equilibrium &equilibrium) {

	profile pro;

	//! read electron density profile length of dataset: cells	
	int cells = coreprof.ne.value.rows();
	
	//! read electron temperature profile length of dataset, comparing with cells
	if (coreprof.te.value.rows() != cells)
		throw std::invalid_argument("Number of values is different in coreprof ne and te.");

	//! read eparallel profile length of dataset, comparing with cells
	if (coreprof.profiles1d.eparallel.value.rows() != cells)
		throw std::invalid_argument(
				"Number of values is different in coreprof.ne and coreprof.profiles1d.eparallel.");

    //! read data in every $\rho$ 

	for (int rho = 0; rho < cells; rho++) {
		cell celll;
		celll.electron_density = coreprof.ne.value(rho);
		celll.electron_temperature = coreprof.te.value(rho);
		
		/*! local electric field
			\f[ E = \frac{E_\parallel(\rho) B_0}{B_\mathrm{av}(\rho)} \f]
			where B_\mathrm{av} is known on discreate \f$R \f$ major radius and interpolated at $\rho$ normalised minor radius
		*/
		celll.electric_field = coreprof.profiles1d.eparallel.value(rho) * coreprof.toroid_field.b0
				/ interpolate(equilibrium.profiles_1d.rho_tor, equilibrium.profiles_1d.b_av,
						coreprof.rho_tor(rho));

		//! total sum of electric charge in \a rho cell for all ion population
		celll.effective_charge = 0.0;
		for (int ion = 0; ion < coreprof.compositions.ions.rows(); ion++) {
			celll.effective_charge += coreprof.ni.value(rho, ion)
					* coreprof.compositions.ions(ion).zion * coreprof.compositions.ions(ion).zion;
		}
		//! total sum of electric charge in \a rho cell for all impurity population
		for (int impurity = 0; impurity < coreimpur.impurity.rows(); impurity++) {

			for (int ionization_degree = 0;
					ionization_degree < coreimpur.impurity(impurity).z.extent(1);
					ionization_degree++) {

				Array<double, 1> density_profile = coreimpur.impurity(impurity).nz(Range::all(),
						ionization_degree);
				Array<double, 1> charge_profile = coreimpur.impurity(impurity).z(Range::all(),
						ionization_degree);

				//! number of impurities by species
				double nz = interpolate(coreimpur.rho_tor, density_profile, coreprof.rho_tor(rho));
				
				//! charge of impurity
				double z = interpolate(coreimpur.rho_tor, charge_profile, coreprof.rho_tor(rho));

				celll.effective_charge += nz * z * z;
			}
		}

		// Assume sum of n_i * Z_i equals electron density because of quasi-neutrality
		celll.effective_charge /= celll.electron_density;

		pro.push_back(celll);
	}

	return pro;
}


// IMAS utilities
profile cpo_to_profile_imas(const IdsNs::IDS::core_profiles &core_profiles, const IdsNs::IDS::equilibrium &equilibrium, int timeindex){

	profile pro;

	//! read electron density profile length of dataset: cells	
	int cells = core_profiles.profiles_1d[timeindex].grid.rho_tor.rows();
	
	//! read electron temperature profile length of dataset, comparing with cells
	if (core_profiles.te.value.rows() != cells)
		throw std::invalid_argument("Number of values is different in core_profiles ne and te.");

	//! read eparallel profile length of dataset, comparing with cells
	if (core_profiles.profiles1d.eparallel.value.rows() != cells)
		throw std::invalid_argument(
				"Number of values is different in core_profiles.ne and core_profiles.profiles1d.eparallel.");

    //! read data in every $\rho$ 

	for (int rho = 0; rho < cells; rho++) {
		cell celll;
		celll.electron_density = .profiles_1d[timeindex].electrons.density.value(rho);
		celll.electron_temperature = .profiles_1d[timeindex].electrons.temperature.value(rho);
		
		/*! local electric field
			\f[ E = \frac{E_\parallel(\rho) B_0}{B_\mathrm{av}(\rho)} \f]
			where B_\mathrm{av} is known on discreate \f$R \f$ major radius and interpolated at $\rho$ normalised minor radius
		*/
		celll.electric_field = core_profiles.profiles1d.eparallel.value(rho) * core_profiles.toroid_field.b0
				/ interpolate(equilibrium.profiles_1d.rho_tor, equilibrium.profiles_1d.b_av,
						core_profiles.profiles_1d[timeindex].grid.rho_tor(rho));

		//! total sum of electric charge in \a rho cell for all ion population
		celll.effective_charge = 0.0;
		for (int ion = 0; ion < core_profiles.compositions.ions.rows(); ion++) {
			celll.effective_charge += core_profiles.ni.value(rho, ion)
					* core_profiles.compositions.ions(ion).zion * core_profiles.compositions.ions(ion).zion;
		}
		//! total sum of electric charge in \a rho cell for all impurity population
		for (int impurity = 0; impurity < coreimpur.impurity.rows(); impurity++) {

			for (int ionization_degree = 0;
					ionization_degree < coreimpur.impurity(impurity).z.extent(1);
					ionization_degree++) {

				Array<double, 1> density_profile = coreimpur.impurity(impurity).nz(Range::all(),
						ionization_degree);
				Array<double, 1> charge_profile = coreimpur.impurity(impurity).z(Range::all(),
						ionization_degree);

				//! number of impurities by species
				double nz = interpolate(coreimpur.rho_tor, density_profile, core_profiles.rho_tor(rho));
				
				//! charge of impurity
				double z = interpolate(coreimpur.rho_tor, charge_profile, core_profiles.rho_tor(rho));

				celll.effective_charge += nz * z * z;
			}
		}

		// Assume sum of n_i * Z_i equals electron density because of quasi-neutrality
		celll.effective_charge /= celll.electron_density;

		pro.push_back(celll);
	}

	return pro;
}
