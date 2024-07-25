#include "pch.h"
#include "HupergeomSampleGenerator.h"

/**
 * @brief Fills an array with observed frequencies from the model.
 * @return Pointer to the dynamically allocated array containing observed frequencies.
 *
 * This method allocates memory for an array to store the frequency of occurrences for each outcome
 * based on the 'removed' parameter of the modeling distribution. It iterates through the observed
 * frequencies modeled by the generator and increments the count for each observed frequency.
 */

int* HupergeomSampleGenerator::fill_observe_freq() const
{
    int* observe_freq = new int[modeling_distr.Get_removed() + 1]{ 0 };
    for (int i = 0; i < sample_size; ++i)
    {
        ++observe_freq[observed_frequences_modeling[i]];
    }
    return observe_freq;
}


/**
 * @brief Move constructor for HupergeomSampleGenerator.
 * @param _s R-value reference to a HupergeomSampleGenerator object to be moved.
 *
 * This constructor transfers the ownership of resources from the source object `_s` to the newly
 * created object. It sets the source object's observed frequencies pointer to nullptr and resets
 * its sample size to zero to ensure that the source object is left in a valid state.
 */

HupergeomSampleGenerator::HupergeomSampleGenerator(HupergeomSampleGenerator&& _s) noexcept :
    sample_size(_s.sample_size),
    modeling_distr(_s.modeling_distr),
    observed_frequences_modeling(_s.observed_frequences_modeling)
{
    _s.observed_frequences_modeling = nullptr;
    _s.sample_size = 0;
}

/**
 * @brief Copy assignment operator.
 * @param s Reference to the HupergeomSampleGenerator object to copy from.
 * @return HupergeomSampleGenerator& Reference to the current object after copy.
 * Performs a deep copy of the given object to this object.
 */
HupergeomSampleGenerator&HupergeomSampleGenerator::operator=(const HupergeomSampleGenerator& s)
{
    if (this != &s) 
    {
        sample_size = s.sample_size;
        modeling_distr = s.modeling_distr;
        delete[] observed_frequences_modeling;

        if (s.observed_frequences_modeling == nullptr)
        {
            observed_frequences_modeling = nullptr;
            return *this;
        }
        observed_frequences_modeling = new int[s.sample_size];

        for (int i = 0; i < s.sample_size; ++i)
        {
            observed_frequences_modeling[i] = s.observed_frequences_modeling[i];
        }
    }
    return *this;
}

/**
 * @brief Move assignment operator.
 * @param s R-value reference to the HupergeomSampleGenerator object to move from.
 * @return HupergeomSampleGenerator& Reference to the current object after move.
 * Transfers the resources from the given object to this object, leaving the given object in a valid, but empty state.
 */
HupergeomSampleGenerator& HupergeomSampleGenerator:: operator=(HupergeomSampleGenerator&& s) 
{
    if (this != &s) 
    {
        sample_size = s.sample_size;
        modeling_distr = s.modeling_distr;
        delete[] observed_frequences_modeling;
        observed_frequences_modeling = s.observed_frequences_modeling;
        s.observed_frequences_modeling = nullptr;
        s.sample_size = 0;
    }
    return *this;
}

/**
 * @brief Copy constructor.
 * @param _s Reference to the HupergeomSampleGenerator object to copy from.
 * Creates a deep copy of the given object.
 */
HupergeomSampleGenerator::HupergeomSampleGenerator(const HupergeomSampleGenerator& _s) :
    sample_size(_s.sample_size),
    modeling_distr(_s.modeling_distr),
    observed_frequences_modeling(nullptr)
{
    if (sample_size)
    {
        observed_frequences_modeling = new int[sample_size];
        for (int i = 0; i < sample_size; ++i)
        {
            observed_frequences_modeling[i] = _s.observed_frequences_modeling[i];
        }
    }
}