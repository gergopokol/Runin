#include <gtest/gtest.h>
#include "critical_field.h"
#include "growth_rate.h"
#include "cell.h"

const double reference_te = 1e5;
const double reference_ne = 1e21;
const double reference_dreicer_field = 4.7823;
const double reference_electric_field = 0.93588;
const double reference_growth_rate_2 = 7.5813e22;
const double reference_growth_rate_1 = 5.536e22;
const double reference_thermal_electron_collision_time = 4.4596e-4;
const double reference_Zeff_1 = 1.0;
const double reference_Zeff_2 = 1.2;
const double reference_electric_field_1 = 1.0;
const double reference_electric_field_2 = 1.2;
const double reference_Coulomb_log = 18.35387764;
const double reference_rho_max = 0.95;


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
TEST(Simpletest, SimpleTest)
{
	EXPECT_EQ(1,1);
}

/*
TEST(CoulombLog, CalculateCoulombLog) {
	EXPECT_NEAR(reference_Coulomb_log, calculate_coulomb_log(reference_ne, reference_te), 0.0001);
}

TEST(CriticalField, CalculateCriticalField) {
	EXPECT_NEAR(reference_electric_field, calculate_critical_field(reference_ne, reference_te), 0.0001);
}

TEST(GrowthRate, CalculateDreicerField) {
	EXPECT_NEAR(reference_dreicer_field, calculate_dreicer_field(reference_ne, reference_te), 0.01);
}

TEST(GrowthRate, CalculateThermalElectronCollisionTime) {
	EXPECT_NEAR(reference_thermal_electron_collision_time, calculate_thermal_electron_collision_time(reference_ne,reference_te), 0.0001);
}

TEST(GrowthRate, CalculateGrowthRate_1) {
	EXPECT_NEAR(reference_growth_rate_1, calculate_growth_rate(reference_ne, reference_te, reference_Zeff_1, reference_electric_field_1), 1e18);
}

TEST(GrowthRate, CalculateGrowthRate_2) {
	EXPECT_NEAR(reference_growth_rate_2, calculate_growth_rate(reference_ne, reference_te, reference_Zeff_2, reference_electric_field_2), 1e18);
}

TEST(CriticalField, IsFieldCritical) {
	cell cell1, cell2;

	//increasing critical field
	cell1.electron_density = 1.1*reference_ne;
	cell1.electron_temperature = reference_te;
	cell1.electric_field = reference_electric_field;

	//decreasing critical field
	cell2.electron_density = 0.9*reference_ne;
	cell2.electron_temperature = reference_te;
	cell2.electric_field = reference_electric_field;

	profile pro;
	pro.push_back(cell1);
	EXPECT_NEAR(0, is_field_critical(pro, reference_rho_max), 0.1);
	EXPECT_NEAR(reference_electric_field, calculate_critical_field(reference_ne,reference_te), 0.1);

	pro.push_back(cell2);
	EXPECT_NEAR(1, is_field_critical(pro, reference_rho_max), 0.1);

}

TEST(GrowthRate, IsGrowthRateOverLimit) {
	cell cell1, cell2;

	cell1.electron_density = 0.9*reference_ne;
	cell1.electron_temperature = reference_te;
	cell1.effective_charge = reference_Zeff_1;
	cell1.electric_field = reference_electric_field_1;

	cell2.electron_density = 1.1*reference_ne;
	cell2.electron_temperature = reference_te;
	cell2.effective_charge = reference_Zeff_2;
	cell2.electric_field = reference_electric_field_2;

	profile pro;
	pro.push_back(cell1);
	EXPECT_EQ(1, is_growth_rate_over_limit(pro, reference_growth_rate_1, reference_rho_max));

	pro.push_back(cell2);
	EXPECT_EQ(0, is_growth_rate_over_limit(pro, reference_growth_rate_2, reference_rho_max));
}*/
