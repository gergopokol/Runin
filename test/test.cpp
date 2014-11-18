#include <gtest/gtest.h>
#include "../cpo_utils.h"
#include "../critical_field.h"
#include "../growth_rate.h"

TEST(Equal, Tolerance) {
	EXPECT_TRUE(equal(1.0, 1.1, 0.1));
	EXPECT_TRUE(equal(-10.0, -11.0, 0.1));
	EXPECT_TRUE(equal(-10.0, 10.0, 2.0));
	EXPECT_FALSE(equal(1.0, 1.2, 0.1));
	EXPECT_FALSE(equal(-10.0, -12.0, 0.1));
}

TEST(BinarySearch, FindExistingValue) {
	blitz::Array<double, 1> ar(10);
	ar = 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0;
	EXPECT_EQ(0, binary_search(ar, 0.0));
	EXPECT_EQ(1, binary_search(ar, 1.0));
	EXPECT_EQ(2, binary_search(ar, 2.0));
	EXPECT_EQ(3, binary_search(ar, 3.0));
	EXPECT_EQ(4, binary_search(ar, 4.0));
	EXPECT_EQ(5, binary_search(ar, 5.0));
	EXPECT_EQ(6, binary_search(ar, 6.0));
	EXPECT_EQ(7, binary_search(ar, 7.0));
	EXPECT_EQ(8, binary_search(ar, 8.0));
	EXPECT_EQ(8, binary_search(ar, 9.0));
}

TEST(BinarySearch, FindValue) {
	blitz::Array<double, 1> ar(10);
	ar = 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0;
	EXPECT_EQ(0, binary_search(ar, 0.01));
	EXPECT_EQ(0, binary_search(ar, 0.99));
	EXPECT_EQ(1, binary_search(ar, 1.01));
	EXPECT_EQ(1, binary_search(ar, 1.99));
	EXPECT_EQ(6, binary_search(ar, 6.1));
	EXPECT_EQ(6, binary_search(ar, 6.5));
	EXPECT_EQ(7, binary_search(ar, 7.2));
	EXPECT_EQ(8, binary_search(ar, 8.01));
	EXPECT_EQ(8, binary_search(ar, 8.99));
}

TEST(Interpolate, Matching) {
	blitz::Array<double, 1> x(10), y(10);
	x = 0.0, 1.0, 2.0, 3.0, 4.0, 4.2, 4.6, 8.0, 8.5, 9.0;
	y = 0.0, 1.0, 2.0, 4.0, 8.0, 4.0, 2.0, 0.0, -2.0, 0.0;

	for (int i = 0; i < x.rows(); i++) {
		EXPECT_DOUBLE_EQ(y(i), interpolate(x, y, x(i)));
	}
}

TEST(Interpolate, Extrapolate) {
	blitz::Array<double, 1> x(10), y(10);
	x = 0.0, 1.0, 2.0, 3.0, 4.0, 4.2, 4.6, 8.0, 8.5, 9.0;
	y = 0.0, 1.0, 2.0, 4.0, 8.0, 4.0, 2.0, 0.0, -2.0, -1.0;
	EXPECT_DOUBLE_EQ(0.0, interpolate(x, y, -1.2));
	EXPECT_DOUBLE_EQ(0.0, interpolate(x, y, -100.2));
	EXPECT_DOUBLE_EQ(-1.0, interpolate(x, y, 9.1));
	EXPECT_DOUBLE_EQ(-1.0, interpolate(x, y, 900.1));

}

TEST(Interpolate, Intrapolate) {
	blitz::Array<double, 1> x(10), y(10);
	x = 0.0, 1.0, 2.0, 3.0, 4.0, 4.2, 4.6, 8.0, 8.5, 9.0;
	y = 0.0, 1.0, 2.0, 4.0, 8.0, 4.0, 2.0, 0.0, -2.0, 0.0;
	EXPECT_NEAR(0.5, interpolate(x, y, 0.5), 0.000001);
	EXPECT_NEAR(1.5, interpolate(x, y, 1.5), 0.000001);
	EXPECT_NEAR(3.0, interpolate(x, y, 2.5), 0.000001);
	EXPECT_NEAR(4.4, interpolate(x, y, 3.1), 0.000001);
	EXPECT_NEAR(7.6, interpolate(x, y, 3.9), 0.000001);
	EXPECT_NEAR(5.0, interpolate(x, y, 4.15), 0.000001);
	EXPECT_NEAR(3.75, interpolate(x, y, 4.25), 0.000001);
	EXPECT_NEAR(1.0, interpolate(x, y, 6.3), 0.000001);
	EXPECT_NEAR(-1.6, interpolate(x, y, 8.4), 0.000001);
	EXPECT_NEAR(-1.0, interpolate(x, y, 8.75), 0.000001);
}

ItmNs::Itm::coreprof coreprof;
ItmNs::Itm::coreimpur coreimpur;
ItmNs::Itm::equilibrium equilibrium;

void create_cpo() {
	coreprof.rho_tor.resize(5);
	coreprof.rho_tor = 0.0, 1.0, 2.0, 4.0, 8.0;

	coreprof.ne.value.resize(5);
	coreprof.te.value.resize(5);
	coreprof.ne.value = 10.0, 11.0, 12.0, 14.0, 18.0;
	coreprof.te.value = 20.0, 21.0, 22.0, 24.0, 28.0;

	coreprof.profiles1d.e_b.value.resize(5);
	coreprof.profiles1d.e_b.value = 1.0, 2.0, 3.0, 5.0, 9.0;

	equilibrium.profiles_1d.rho_tor.resize(8);
	equilibrium.profiles_1d.rho_tor = 0.0, 1.0, 1.5, 2.0, 5.0, 10.0, 12.0, 15.0;
	equilibrium.profiles_1d.b_av.resize(8);
	equilibrium.profiles_1d.b_av = 5.5, 1.5, 5.5, 2.5, 1.6, 11.6, 15.5, 55.5;

	coreprof.ni.value.resize(5, 2);
	coreprof.ni.value = 1, 2, 3, 4, 5, 6, 7, 8, 9, 10;

	coreprof.compositions.ions.resize(2);
	coreprof.compositions.ions(0).zion = 2.0;
	coreprof.compositions.ions(1).zion = 3.0;

	coreimpur.rho_tor.resize(6);
	coreimpur.rho_tor = 0.0, 1.0, 1.5, 2.0, 6.0, 10.0;

	coreimpur.impurity.resize(2);
	coreimpur.impurity(0).z.resize(6, 2);
	coreimpur.impurity(0).z = 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24;
	coreimpur.impurity(1).z.resize(6, 2);
	coreimpur.impurity(1).z = 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12;

	coreimpur.impurity(0).nz.resize(6, 2);
	coreimpur.impurity(0).nz = 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2;
	coreimpur.impurity(1).nz.resize(6, 2);
	coreimpur.impurity(1).nz = 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12;
}

TEST(CpoToProfil, ElectronDensity) {
	create_cpo();
	profile pro = cpo_to_profile(coreprof, coreimpur, equilibrium);

	ASSERT_EQ(5, pro.size());

	EXPECT_DOUBLE_EQ(10.0, pro[0].electron_density);
	EXPECT_DOUBLE_EQ(11.0, pro[1].electron_density);
	EXPECT_DOUBLE_EQ(12.0, pro[2].electron_density);
	EXPECT_DOUBLE_EQ(14.0, pro[3].electron_density);
	EXPECT_DOUBLE_EQ(18.0, pro[4].electron_density);
}

TEST(CpoToProfil, ElectronTemperature) {
	create_cpo();
	profile pro = cpo_to_profile(coreprof, coreimpur, equilibrium);

	ASSERT_EQ(5, pro.size());

	EXPECT_DOUBLE_EQ(20.0, pro[0].electron_temperature);
	EXPECT_DOUBLE_EQ(21.0, pro[1].electron_temperature);
	EXPECT_DOUBLE_EQ(22.0, pro[2].electron_temperature);
	EXPECT_DOUBLE_EQ(24.0, pro[3].electron_temperature);
	EXPECT_DOUBLE_EQ(28.0, pro[4].electron_temperature);
}

TEST(CpoToProfil, ElectricField) {
	create_cpo();
	profile pro = cpo_to_profile(coreprof, coreimpur, equilibrium);

	ASSERT_EQ(5, pro.size());

	EXPECT_DOUBLE_EQ(1.0 / 5.5, pro[0].electric_field);
	EXPECT_DOUBLE_EQ(2.0 / 1.5, pro[1].electric_field);
	EXPECT_DOUBLE_EQ(3.0 / 2.5, pro[2].electric_field);
	EXPECT_DOUBLE_EQ(5.0 / 1.9, pro[3].electric_field);
	EXPECT_DOUBLE_EQ(9.0 / 7.6, pro[4].electric_field);
}

TEST(CpoToProfil, EffectiveCharge) {
	create_cpo();
	profile pro = cpo_to_profile(coreprof, coreimpur, equilibrium);

	ASSERT_EQ(5, pro.size());

	EXPECT_NEAR(3.46000, pro[0].effective_charge, 0.00001);
	EXPECT_NEAR(131.24, pro[3].effective_charge, 0.01);
}

TEST(CriticalField, CalculateCriticalField) {
	EXPECT_NEAR(0.93588, calculate_critical_field(1e21, 1e5), 0.0001);
}

TEST(CriticalField, IsFieldCritical) {
	cell cell1, cell2;

	cell1.electron_density = 1.1e21;
	cell1.electron_temperature = 1e5;
	cell1.electric_field = 0.93588;

	cell2.electron_density = 0.9e21;
	cell2.electron_temperature = 1e5;
	cell2.electric_field = 0.93588;

	profile pro;
	pro.push_back(cell1);
	EXPECT_EQ(0, is_field_critical(pro));

	pro.push_back(cell2);
	EXPECT_EQ(1, is_field_critical(pro));
}

TEST(GrowthRate, CalculateGrowthRate) {
	EXPECT_NEAR(6.73973e22, calculate_growth_rate(1e21, 1e5, 1.5, 1.2), 1e18);
}

TEST(GrowthRate, IsGrowthRateOverLimit) {
	cell cell1, cell2;

	cell1.electron_density = 1.1e21;
	cell1.electron_temperature = 1e5;
	cell1.effective_charge = 1.5;
	cell1.electric_field = 1.2;

	cell2.electron_density = 0.9e21;
	cell2.electron_temperature = 1e5;
	cell1.effective_charge = 1.5;
	cell2.electric_field = 1.2;

	profile pro;
	pro.push_back(cell1);
	EXPECT_EQ(0, is_growth_rate_over_limit(pro, 6.73973e22));

	pro.push_back(cell2);
	EXPECT_EQ(1, is_growth_rate_over_limit(pro, 6.73973e22));
}
