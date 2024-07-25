#include "pch.h"
#include "Distribution.h"

/**
 * @brief Copy constructor for creating a deep copy of a Distribution object.
 * @param _d The Distribution object to copy from.
 * Deep copies the parameters a, b, and removed, and allocates memory to store the theoretical probabilities,
 * copying each element from the source object.
 */
Distribution::Distribution(const Distribution& _d) :
													a(_d.a),
													b(_d.b),
													removed(_d.removed),
													theoretical_prob(nullptr)
{
	if (removed)
	{
		theoretical_prob = new double[removed + 1];
		for (int i = 0; i < removed + 1; ++i)
		{
			theoretical_prob[i] = _d.theoretical_prob[i];
			Modeling_theoretical_prob();
		}
	}
}

/**
 * @brief Move constructor for transferring ownership of resources from one Distribution object to another.
 * @param _d R-value reference to a Distribution object to move from.
 * Transfers the parameters a, b, and removed, and the pointer to theoretical_prob from _d to this object,
 * leaving _d in a valid, destructible state.
 */
Distribution::Distribution(Distribution&& _d) noexcept : 
														a(_d.a),
														b(_d.b),
														removed(_d.removed),
														theoretical_prob(_d.theoretical_prob)
{
	_d.a = 0;
	_d.b = 0;
	_d.removed = 0;
	_d.theoretical_prob = nullptr;
}


/**
 * @brief Copy assignment operator for assigning one Distribution object to another.
 * @param other The Distribution object to assign from.
 * @return Reference to the current object after copying.
 * Handles self-assignment, deallocates current theoretical_prob memory, and deep copies parameters and theoretical probabilities from other.
 */
Distribution& Distribution::operator =(const Distribution& other) 
{
	if (this != &other) 
	{
		a = other.a;
		b = other.b;
		removed = other.removed;


		delete[] theoretical_prob;
		theoretical_prob = new double[removed+1];

		for (int i = 0; i < removed + 1; ++i)
		{
			theoretical_prob[i] = other.theoretical_prob[i];
		}
	}
	return *this;
}

/**
 * @brief Move assignment operator for moving a Distribution object.
 * @param other R-value reference to a Distribution object to move from.
 * @return Reference to the current object after moving.
 * Transfers parameters and theoretical_prob pointer from other to this object, resets other's parameters, and ensures no memory leak occurs.
 */
Distribution& Distribution::operator =(Distribution&& other) noexcept 
{
	if (this != &other) 
	{
		a = other.a;
		b = other.b;
		removed = other.removed;

		delete[] theoretical_prob;

		theoretical_prob = other.theoretical_prob;
		other.theoretical_prob = nullptr;

		other.a = 0;
		other.b = 0;
		other.removed = 0;
	}
	return *this;
}


/**
 * @brief Models the theoretical probabilities for the hypergeometric distribution.
 * Computes and stores probabilities based on the hypergeometric formula using current parameters.
 * Ensures theoretical_prob is properly allocated to hold all probability values.
 */
void Distribution::Modeling_theoretical_prob()
{
	delete[] theoretical_prob;
	theoretical_prob = new double[removed + 1];

	double p = double(factorial(b) * factorial(a + b - removed) /
		(factorial(b - removed) * factorial(a + b)));

	for (int i = 0; i < removed + 1; ++i)
	{
		theoretical_prob[i] = p;
		p *= double(a - i) * (removed - i) / ((i + 1) * (b - removed + i + 1));
	}
}

/**
 * @brief Returns the name identifier of this distribution.
 * @return A pointer to a character string identifying this distribution type.
 * Useful for generic programming where the distribution's type needs to be known at runtime.
 */
const char* Distribution::name()
{
	return "Hypergeometrical distribution";
}

/**
 * @brief Computes the factorial of a given number N.
 * @param N The number to compute the factorial of.
 * @return The factorial value of N as a double.
 * Factorial is calculated in a straightforward manner, multiplying from 1 up to N.
 */
double Distribution::factorial(int N)
{
	double F = 1;
	for (int i = 1; i <= N; ++i)
	{
		F *= i;
	}
	return F;
}