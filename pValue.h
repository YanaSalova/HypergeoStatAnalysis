#pragma once
#include "Chi2Histogram.h"
const int alpha = 20;

/**
 * @class pValue
 * @brief Manages the computation and storage of p-values from statistical simulations.
 *
 * This class is designed to simulate distributions, calculate p-values for each simulation,
 * and assess the significance of these p-values against a specified alpha significance level.
 */
class pValue
{
protected:

	double* mas_p_value;///< Dynamic array storing p-values from simulations.


	int num_of_simulations_p_value;///< Number of simulations to perform for p-value calculation.


	double distribution_func_pvalues[alpha]{ 0 };///< Static array holding the distribution function of p-values.


	double alpha_significance_level;///< Alpha significance level for statistical tests.


public:
	/**
 * @brief Default constructor initializing member variables with default values.
 */
	pValue() : num_of_simulations_p_value(1000),
		       alpha_significance_level(0.05),
		       mas_p_value(nullptr)
	{
		if(num_of_simulations_p_value)
			mas_p_value = new double[num_of_simulations_p_value];
	}

	/**
 * @brief Constructor specifying the number of simulations for p-value calculations.
 * @param _pvalue_size The number of simulations to perform.
 */
	pValue(int _pvalue_size) :
		num_of_simulations_p_value(_pvalue_size),
		mas_p_value(nullptr),
		alpha_significance_level(0.05) 
	{
		if(num_of_simulations_p_value)
			mas_p_value = new double[num_of_simulations_p_value];
	
	}

	/**
   * @brief Copy constructor.
   * @param other The `pValue` object to copy from.
   */
	pValue(const pValue& other);


	/**
   * @brief Move constructor.
   * @param other The `pValue` object to move.
   */
	pValue(pValue&& other) noexcept;


	/**
   * @brief Copy assignment operator.
   * @param other The `pValue` object to assign from.
   * @return A reference to the current object.
   */
	pValue& operator=(const pValue& other);


	/**
  * @brief Move assignment operator.
  * @param other The `pValue` object to move assign from.
  * @return A reference to the current object.
  */
	pValue& operator=(pValue&& other) noexcept;

	/**
  * @brief Destructor to clean up dynamically allocated memory for p-values.
  */
	~pValue()
	{
		if(mas_p_value!= nullptr)
			delete[] mas_p_value;

		mas_p_value = nullptr;
	}



	/**
	 * @brief Fills the p-value array by performing simulations based on a given distribution and sample generator.
	 * @param d0 The distribution model used for simulations.
	 * @param s The sample generator for empirical data generation.
	 */
	void FillPvalueArr(Distribution& d0, HupergeomSampleGenerator* s);

	/**
   * @brief Computes the distribution of p-values across all simulations.
   */
	void FillDistributionArray();

	double* GetPvalueArr() {return mas_p_value;}

	int GetPvaluesize() const {return num_of_simulations_p_value;}

	void SetPvaluesize(int _pvalue_size) 
	{
		num_of_simulations_p_value = _pvalue_size; 
	}

	
	double* GetDistributionArray() { return distribution_func_pvalues; }

	void SetAlpha(double _alpha_significance_level)
	{
		alpha_significance_level = _alpha_significance_level;
	}
	double GetAlpha() const { return alpha_significance_level; }
};

