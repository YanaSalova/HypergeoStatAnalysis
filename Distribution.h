#pragma once


/**
 * @class Distribution
 * @brief Models a hypergeometric distribution for a given set of black and white balls.
 *
 * This class encapsulates the hypergeometric distribution, characterized by 'a' as the number of black balls,
 * 'b' as the number of white balls in the population, and 'removed' as the number of balls drawn from the population.
 * It computes theoretical probabilities for drawing a specific number of black balls in the sample.
 */
class Distribution
{
protected:
 
    int a;; ///< Number of black balls in the population.

  
    int b; ///< Number of white balls in the population.

    
    int removed;///< Number of balls drawn from the population.

  
    double* theoretical_prob;///< Array of theoretical probabilities for drawing each possible number of black balls.

public:

    /**
     * @brief Constructs a Distribution object with default parameters.
     * Initializes 'a', 'b', and 'removed' with default values and allocates memory for theoretical probabilities.
     */
    Distribution() : a(20), b(35), removed(15), theoretical_prob(nullptr) 
    {
        if (removed)
        {
            theoretical_prob = new double[removed + 1]{0};
            Modeling_theoretical_prob();
        }
    }

    /**
    * @brief Constructor with specified parameters for the distribution.
    * @param _a Number of black balls in the population.
    * @param _b Number of white balls in the population.
    * @param _removed Number of balls drawn from the population.
    */
    Distribution(int _a, int _b, int _removed) : a(_a), b(_b), removed(_removed),
                                                  theoretical_prob(nullptr)
    {
        if (removed)
        {
            theoretical_prob = new double[removed + 1]{ 0 };
            Modeling_theoretical_prob();
        }
    }


    /**
 * @brief Copy constructor.
 * @param other The Distribution object to copy from.
 */
	Distribution(const Distribution& other);

    /**
 * @brief Move constructor.
 * @param _d The Distribution object to move.
 */
	Distribution(Distribution&& _d) noexcept;

    /**
  * @brief Copy assignment operator.
  * @param other The Distribution object to assign from.
  * @return Reference to this updated object.
  */
    Distribution& operator =(const Distribution& other);

    /**
 * @brief Move assignment operator.
 * @param other The Distribution object to move assign from.
 * @return Reference to this updated object.
 */
    Distribution& operator =(Distribution&& other) noexcept;

    /**
 * @brief Destructor to clean up dynamically allocated memory for theoretical probabilities.
 */
	~Distribution() 
    { 
        if(theoretical_prob!= nullptr)
            delete[] theoretical_prob; 
        theoretical_prob = nullptr;
    }


    /**
 * @brief Returns the name of the distribution.
 * @return A constant character pointer to the name of the distribution.
 */
	const char* name();

    /**
 * @brief Models and calculates theoretical probabilities based on the current distribution parameters.
 */
	void Modeling_theoretical_prob();

	int Geta() const { return a; }
	int Getb() const { return b; }
	int Get_removed() const{ return removed; }
	double* GetTheoretical_prob() { return theoretical_prob; }
    double GetTheoretical_prob(int i) const { return theoretical_prob[i];}


	void Seta(int _a) { a = _a; }
	void Setb(int _b) { b = _b;}
	void Set_removed(int _removed) { removed = _removed;}
    /**
 * @brief Calculates the factorial of a number.
 * @param N The number to calculate the factorial for.
 * @return The factorial of N.
 */
	double factorial(int N);

};

