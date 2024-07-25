#include "pch.h"
#include "pValue.h"



/**
 * @brief Constructs a pValue object as a deep copy of an existing one.
 * @param _pv The pValue object to copy from.
 * Copies all the properties and deep copies the mas_p_value array if it exists.
 */
pValue::pValue(const pValue& _pv) :
	num_of_simulations_p_value(_pv.num_of_simulations_p_value),
	mas_p_value(nullptr),
	alpha_significance_level(_pv.alpha_significance_level)
{
	
	if (num_of_simulations_p_value)
	{
		mas_p_value = new double[num_of_simulations_p_value];
		for (int i = 0; i < num_of_simulations_p_value; ++i)
		{
			mas_p_value[i] = _pv.mas_p_value[i];
		}
	}

	for (int i = 0; i < alpha; ++i)
	{
		distribution_func_pvalues[i] = _pv.distribution_func_pvalues[i];
	}
}


/**
 * @brief Constructs a pValue object by transferring ownership of resources from another object.
 * @param other The pValue object to move from.
 * Transfers the mas_p_value pointer and resets the source object to prevent double deletion.
 */
pValue::pValue(pValue&& other) noexcept
	: num_of_simulations_p_value(other.num_of_simulations_p_value),
	  mas_p_value(other.mas_p_value)
{
	for (int i = 0; i < 20; ++i)
	{
		distribution_func_pvalues[i] = other.distribution_func_pvalues[i];
	}
	other.num_of_simulations_p_value = 0;
	other.mas_p_value = nullptr;
}

/**
 * @brief Assigns one pValue object to another by deep copying.
 * @param other The pValue object to assign from.
 * @return A reference to the current object.
 * Deep copies the mas_p_value array and other properties, ensuring proper memory management.
 */
pValue&pValue:: operator=(const pValue& other)
{
	if (this != &other)
	{
		num_of_simulations_p_value = other.num_of_simulations_p_value;
		for (int i = 0; i < 20; ++i)
		{
			distribution_func_pvalues[i] = other.distribution_func_pvalues[i];
		}
		if (other.mas_p_value != nullptr)
		{
			delete[] mas_p_value;
		}
		mas_p_value = new double[num_of_simulations_p_value];

		for (int i = 0; i < num_of_simulations_p_value; ++i)
		{
			mas_p_value[i] = other.mas_p_value[i];
		}
	}
	return *this;
}

/**
 * @brief Moves one pValue object to another.
 * @param other The pValue object to move from.
 * @return A reference to the current object.
 * Transfers the mas_p_value pointer and ensures the other object is left in a valid state.
 */
pValue& pValue:: operator=(pValue&& other) noexcept
{
	if (this != &other)
	{
		num_of_simulations_p_value = other.num_of_simulations_p_value;

		for (int i = 0; i < 20; i++)
		{
			distribution_func_pvalues[i] = other.distribution_func_pvalues[i];
		}
		if (other.mas_p_value != nullptr) 
		{
			delete[] mas_p_value;
		}
		mas_p_value = other.mas_p_value;

		other.num_of_simulations_p_value = 0;
		other.mas_p_value = nullptr;
	}
	return *this;


}

/**
 * @brief Simulates distributions to fill the p-value array.
 * @param d0 The distribution model used for simulation.
 * @param s The sample generator for empirical data.
 * Performs simulations to calculate p-values and stores them in mas_p_value.
 */
void pValue::FillPvalueArr(Distribution& d0, HupergeomSampleGenerator* s)
{

	if (mas_p_value != nullptr) 
	{
		delete[] mas_p_value;
		mas_p_value = nullptr;
	}

	
	mas_p_value = new double[num_of_simulations_p_value];
	for (int i = 0; i < num_of_simulations_p_value; ++i)
	{
		s->Simulate();
		Chi2Histogram h(d0, s);
		h.Chi2();
		mas_p_value[i] = h.Getpvalue();
	}
}

/**
 * @brief Fills the distribution array for p-values.
 * Analyzes the p-value array to calculate the distribution and cumulative frequencies of p-values across simulations.
 */
void pValue::FillDistributionArray()
{
	for (int i = 0; i < num_of_simulations_p_value; ++i)
	{
		if (!isnan(mas_p_value[i]))
			++distribution_func_pvalues[(int)(mas_p_value[i] * alpha)];
	}

	distribution_func_pvalues[0] /= num_of_simulations_p_value;
	for (int i = 1; i < alpha; ++i)
	{
		distribution_func_pvalues[i] /= num_of_simulations_p_value;
		distribution_func_pvalues[i] += distribution_func_pvalues[i - 1];
	}
}
