#include <stdexcept>
#include "ids_utils.h"

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


int get_digit(int number, int digit){

	int number2,number3;
	for (int i = 0; i < digit; i++){
		number2 = number/10;
		number3 = number - 10*number2;		
		number = number2; 		
	}	
	
	return number3;
}


// if rho_tor_norm empty, we need to fill it up

int fill_rho_tor_norm(const IdsNs::IDS::core_profiles &core_profiles, const IdsNs::IDS::equilibrium &equilibrium, int timeindex){
    
	int N_rho = core_profiles.profiles_1d(timeindex).grid.rho_tor.rows();
	int N_rho_norm = core_profiles.profiles_1d(timeindex).grid.rho_tor_norm.rows();

    if (N_rho_norm==0){
        core_profiles.profiles_1d(timeindex).grid.rho_tor_norm.resize(N_rho, 1);
    }
    
    for (int i = 0; i < N_rho; i++){
        core_profiles.profiles_1d(timeindex).grid.rho_tor_norm(i) = interpolate(equilibrium.time_slice(timeindex).profiles_1d.rho_tor,
            equilibrium.time_slice(timeindex).profiles_1d.rho_tor_norm,
		    core_profiles.profiles_1d(timeindex).grid.rho_tor(i));
    }

}


// IMAS utilities
// https://portal.iter.org/departments/POP/CM/IMDesign/Data%20Model/CI/imas-3.7.3/html_documentation.html
profile ids_to_profile(const IdsNs::IDS::core_profiles &core_profiles, const IdsNs::IDS::equilibrium &equilibrium, int timeindex){

	profile pro;

	//! read electron density profile length of dataset: N_rho
	int N_rho = core_profiles.profiles_1d(timeindex).grid.rho_tor.rows();
	
    //! read data in every $\rho$ 
	for (int i = 0; i < N_rho; i++) {
		cell celll;
		celll.electron_density = core_profiles.profiles_1d(timeindex).electrons.density(i);
		celll.electron_temperature = core_profiles.profiles_1d(timeindex).electrons.temperature(i);
		
		/*! local electric field
			\f[ E = \frac{E_\parallel(\rho) B_0}{B_\mathrm{av}(\rho)} \f]
			where B_\mathrm{av} is known on discreate \f$R \f$ major radius and interpolated at $\rho$ normalised minor radius
		*/
				
		celll.electric_field = core_profiles.profiles_1d(timeindex).e_field.parallel(i) *  equilibrium.vacuum_toroidal_field.b0(timeindex) /		
				interpolate(equilibrium.time_slice(timeindex).profiles_1d.rho_tor, equilibrium.time_slice(timeindex).profiles_1d.b_field_average,
						core_profiles.profiles_1d(timeindex).grid.rho_tor(i));
						
		//! total sum of electric charge in \a rho cell
		celll.effective_charge = core_profiles.profiles_1d(timeindex).zeff(i);

		pro.push_back(celll);
	}

	return pro;
}
