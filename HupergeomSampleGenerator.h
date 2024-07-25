#pragma once
#include "Distribution.h"
#include <cassert>
#include <random>
#include <ctime>
#include <chrono>

extern std::mt19937 rngRadius;
extern std::default_random_engine generator;


/**
 * @class HupergeomSampleGenerator
 * @brief Class for generating hypergeometric samples.
 *
 * This class provides an interface and a basic implementation for generating samples using
 * a specified distribution. It's designed to work with hypergeometric distributions but can
 * be extended or used as a base for other types of sample generation.
 */
class HupergeomSampleGenerator
{
protected:
 
    int sample_size;///< The size of the sample to be generated. Defines how many data points will be simulated.

 
    Distribution modeling_distr;///< The distribution model used for generating samples. This object contains the parameters and logic necessary for simulation.

  
    int* observed_frequences_modeling; ///< Pointer to an array that will hold the observed frequencies of different outcomes in the generated sample.

public:
    /**
    * @fn virtual void HupergeomSampleGenerator::Simulate() = 0;
    * @brief Virtual method for sample simulation.
    *
    * Implement this method in derived classes to simulate sampling based on specific
    * distribution parameters and update observed frequencies.
    */
    virtual void Simulate() = 0;

    /**
   * @fn int* HupergeomSampleGenerator::fill_observe_freq() const;
   * @brief Fills and returns observed frequencies.
   * @return Pointer to the array containing observed frequencies of the model.
   *
   * Prepares observed frequencies based on the current simulation and returns them
   * for further analysis.
   */
    int* fill_observe_freq() const;

    /**
   * @brief Constructor for HupergeomSampleGenerator with default sample size and distribution.
   */
    HupergeomSampleGenerator() : 
                                sample_size(100),
                                observed_frequences_modeling(nullptr)
    {
        if (sample_size)
        {
            observed_frequences_modeling = new int[sample_size];
        }
    }


    /**
   * @brief Constructor for HupergeomSampleGenerator with specified sample size and distribution.
   * @param _sample_size Size of the sample to generate.
   * @param _d Distribution object to use for sample generation.
   */
    HupergeomSampleGenerator(int _sample_size, const Distribution& _d) : 
                                            sample_size(_sample_size),
                                            observed_frequences_modeling(nullptr),
                                            modeling_distr(_d)
    {
        if (sample_size)
        {
            observed_frequences_modeling = new int[sample_size];
        }
    }

    /**
 * @brief Move constructor for HupergeomSampleGenerator.
 * @param s R-value reference to the HupergeomSampleGenerator object for moving.
 */
    HupergeomSampleGenerator(HupergeomSampleGenerator&& s) noexcept;

 /**
* @brief Copy constructor for HupergeomSampleGenerator.
* @param s Reference to the existing HupergeomSampleGenerator object.
*/
    HupergeomSampleGenerator(const HupergeomSampleGenerator& s);

    HupergeomSampleGenerator& operator=(const HupergeomSampleGenerator& s);

    HupergeomSampleGenerator& operator=(HupergeomSampleGenerator&& s);

    /**
     * @brief Sets a new sample size for the generator, reallocating resources as necessary.
     * @param _sample_size New size for the sample to be generated.
     */
    void Set_sample_size(int _sample_size) 
    {
        sample_size = _sample_size;
        delete[] observed_frequences_modeling;
        observed_frequences_modeling = new int[_sample_size];
    }

    /**
  * @brief Sets a new distribution model for the sample generator.
  * @param _modeling_distr The new distribution model to apply.
  */
    void SetDist(const Distribution& _modeling_distr) 
    {
        modeling_distr.Seta(_modeling_distr.Geta());
        modeling_distr.Setb(_modeling_distr.Getb());
        modeling_distr.Set_removed(_modeling_distr.Get_removed());
    }

    /// @return The current sample size.
    int Get_sample_size() const { return sample_size; }


    /**
  * @brief Sets observed frequencies manually.
  * @param _observed_frequences_modeling Pointer to an array of observed frequencies.
  */
    void SetObservedFrequences(int* _observed_frequences_modeling)
    {
        for (int i = 0; i < sample_size; ++i) 
        {
            observed_frequences_modeling[i] = _observed_frequences_modeling[i];
        }
    }

    /// @return A pointer to the array of observed frequencies.
    int* GetObservedFrequences() const { return observed_frequences_modeling; }

    /**
   * @brief Retrieves the observed frequency at a given index.
   * @param i Index of the frequency to retrieve.
   * @return Observed frequency at the specified index.
   */
    int GetObservedFrequences(int i) const { return observed_frequences_modeling[i]; }

    /// @return The current distribution model used for sample generation.
    Distribution GetDist() const { return modeling_distr; }

    /**
   * @brief Destructor for HupergeomSampleGenerator.
   *
   * Cleans up the dynamically allocated observed frequencies array.
   */
    virtual ~HupergeomSampleGenerator() 
    {
        delete[] observed_frequences_modeling;
        observed_frequences_modeling = nullptr;
    }
};


