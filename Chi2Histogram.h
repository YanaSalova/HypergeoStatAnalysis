#pragma once
#include "Distribution.h"
#include "HupergeomSampleGenerator.h"
#include "probdist.h"

/**
 * @class Chi2Histogram
 * @brief Class for performing chi-squared test and generating histograms for hypergeometric distributions.
 *
 * This class calculates chi-squared statistics based on empirical and theoretical frequencies
 * to evaluate the goodness of fit for a hypergeometric distribution. It is designed to work
 * with distributions and sample generators for analyzing sample data.
 */

class Chi2Histogram
{
public:
    /**
   * @brief Default constructor initializing all member variables to zero or nullptr.
   */
	Chi2Histogram() : 
        df(0), 
        pvalue(0), 
        chi2(0), 
        EmpiricalFreq(nullptr),
        TheoreticalFreq(nullptr),
        a(0),
        b(0),
        removed(0),
        sample_size(0),
        SizeEmpiricalFreq(0),
        SizeTheoreticalFreq(0)
    {}

    /**
  * @brief Constructs a Chi2Histogram using a distribution and a sample generator.
  * @param _d0 Distribution object for the theoretical frequencies.
  * @param _s Pointer to a HupergeomSampleGenerator for the empirical frequencies.
  */
	Chi2Histogram(const Distribution& _d0, const HupergeomSampleGenerator* _s);

    /**
   * @brief Copy constructor.
   * @param other The other Chi2Histogram object to copy from.
   */
    Chi2Histogram(const Chi2Histogram& other);

    /**
   * @brief Copy assignment operator.
   * @param other The other Chi2Histogram to assign from.
   * @return Reference to the updated Chi2Histogram.
   */
    Chi2Histogram& operator=(const Chi2Histogram& other);

    /**
   * @brief Move assignment operator.
   * @param other The other Chi2Histogram to move assign from.
   * @return Reference to the updated Chi2Histogram.
   */
    Chi2Histogram& operator=(Chi2Histogram&& other);

    /**
    * @brief Destructor to clean up dynamically allocated memory.
    */
    ~Chi2Histogram()
    {
        if(EmpiricalFreq != nullptr)
            delete[] EmpiricalFreq; 
        EmpiricalFreq = nullptr;

        if (TheoreticalFreq != nullptr)
        delete[] TheoreticalFreq; 
        TheoreticalFreq = nullptr;
    }


	double Getpvalue() const { return pvalue; }
	int Getdf() const { return df; }
	double Getchi2() const { return chi2; }

    /**
  * @brief Calculates chi-squared statistic, degrees of freedom, and p-value.
  */
	void Chi2();

protected:
   
    double pvalue; ///< P-value from chi-squared test indicating goodness of fit.

  
    int df;///< Degrees of freedom for chi-squared test.

    double chi2;///< Chi-squared statistic calculated from empirical and theoretical frequencies.

  
    int a;///< Parameter 'a' from the distribution (e.g., number of black balls).

  
    int b;///< Parameter 'b' from the distribution (e.g., number of white balls).

  
    int removed;///< Number of balls drawn in the distribution.

  
    int sample_size;///< Size of the sample drawn.

  
    double* TheoreticalFreq;///< Array of theoretical frequencies based on the distribution.

   
   int* EmpiricalFreq; ///< Array of observed empirical frequencies from the sample.

   
    int SizeTheoreticalFreq;///< Size of the TheoreticalFreq array.

  
    int SizeEmpiricalFreq;///< Size of the EmpiricalFreq array.
};

