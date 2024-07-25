#pragma once
#include "HupergeomSampleGenerator.h"


/**
 * @class Bernulli_Method
 * @brief Implements the simulation of a hypergeometric distribution using the Bernoulli method.
 *
 * Inherits from HupergeomSampleGenerator to provide a specific implementation of the `Simulate` method,
 * which performs simulation of drawing samples according to a hypergeometric distribution using
 * the Bernoulli sampling method. This class is tailored for scenarios where the Bernoulli method
 * is preferred for generating hypergeometrically distributed samples.
 */

class Bernulli_Method : public HupergeomSampleGenerator
{
public:
 
    /**
 * @brief Default constructor for Bernulli_Method, initializing with default parameters.
 */
    Bernulli_Method() : HupergeomSampleGenerator() {};

    /**
 * @brief Constructor for Bernulli_Method with specified sample size and distribution.
 * @param _sample_size Size of the sample to generate.
 * @param _d Distribution model to use for sample generation.
 */
    Bernulli_Method(int _sample_size, const Distribution& _d) :
        HupergeomSampleGenerator(_sample_size, _d) {};

    /**
 * @brief Simulates drawing a sample using the Bernoulli method.
 *
 * Overrides the pure virtual `Simulate` method from HupergeomSampleGenerator to provide
 * the specific logic for simulating the drawing of samples based on the Bernoulli method.
 */
    void Simulate() override;

    /**
 * @brief Destructor for Bernulli_Method.
 */
    ~Bernulli_Method() override {};
};

