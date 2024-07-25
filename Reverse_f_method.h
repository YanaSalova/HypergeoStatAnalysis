#pragma once
#include "HupergeomSampleGenerator.h"


/**
 * @class Reverse_f_method
 * @brief Implements simulation of a hypergeometric distribution using the reverse F method.
 *
 * Inherits from HupergeomSampleGenerator to provide an implementation of the `Simulate` method,
 * which performs simulation of drawing samples according to a hypergeometric distribution by employing
 * the reverse F method. This class is specifically designed for scenarios where the reverse F method
 * is the preferred approach for generating samples with hypergeometric distribution characteristics.
 */

class Reverse_f_method : public HupergeomSampleGenerator
{
public:

    /**
     * @brief Default constructor for Reverse_f_method, initializes with default parameters.
     */
    Reverse_f_method() : HupergeomSampleGenerator() {};

    /**
  * @brief Constructor for Reverse_f_method with specified sample size and distribution.
  * @param _sample_size Size of the sample to generate.
  * @param _d Distribution model to use for sample generation.
  */
    Reverse_f_method(int _sample_size, Distribution _d) :
        HupergeomSampleGenerator(_sample_size, _d) {};

    /**
  * @brief Simulates drawing a sample using the reverse F method.
  *
  * Overrides the pure virtual `Simulate` method from HupergeomSampleGenerator to provide
  * the logic specific to simulating the drawing of samples based on the reverse F method.
  */
    void Simulate() override;

    /**
 * @brief Destructor for Reverse_f_method.
 */
    virtual ~Reverse_f_method() = default;
};
