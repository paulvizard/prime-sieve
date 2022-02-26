#include <iostream>
#include <vector>

// Sieve of Eratosthenes

class PrimeSieve
{
    uint8_t *m_primes;

    int m_maxPrimes;

    /**
     * Removes a number for the sieve
     * @param number
     */
    inline void RemoveNumber(int number)
    {
//        std::cout << "Removing " << number << "\n";

        int byte = number / 8;
        uint8_t bit = number % 8;
        m_primes[byte] = m_primes[byte] | (1 << bit);
    }

    /**
     * Checks a bit in the sieve
     * @param number
     * @return true or false
     */
    inline bool CheckNumber(int number)
    {
        int byte = number / 8;
        uint8_t bit = number % 8;
        bool t = (m_primes[byte] >> bit) & 0x1;
        return t;
    }

    /**
     * Process a number
     * @param number
     * @param max
     */
    void ProcessNumber(int number, int max)
    {
        if (CheckNumber(number))
        {
//            std::cout << "Skipping " << number << "\n";
            return;
        }

        // Get all multiples of number
        for (int i = 2; i <= max / number; i++)
        {
            auto multiple = number * i;
            RemoveNumber(multiple);
        }
    }

public:
    /**
     * Run the sieve
     * @param maxNumber
     */
    void RunSieve(int maxNumber)
    {
        std::cout << "Looking for primes below " << maxNumber << " with C++\n";

        m_maxPrimes = maxNumber;
        // Create a bunch of bits
        m_primes = new uint8_t[maxNumber / 8 + 1];
        memset(&m_primes[0], 0, maxNumber / 8 + 1);

        // Remove 1
        RemoveNumber(1);

        for (int i = 2; i < maxNumber; i++)
        {
            ProcessNumber(i, maxNumber);
        }
    }

    /**
     * Print primes
     * @return
     */
    int PrintPrimes()
    {
        int found = 0;
        for (int i = 1; i < m_maxPrimes; i++)
        {
            auto bit = CheckNumber(i);
            if (!bit)
            {
                found++;
                //                std::cout << i << "\n";
            }
        }

        std::cout << "Found " << found << " prime numbers\n";

        return found;
    }
};

/**
 * Main
 * @return
 */
int main()
{
    PrimeSieve sieve;

    auto start = std::chrono::high_resolution_clock::now();
    sieve.RunSieve(1000000000);
    auto end = std::chrono::high_resolution_clock::now();

    auto dur = end - start;
    auto i_millis = std::chrono::duration_cast<std::chrono::milliseconds>(dur);

    std::cout << "Processing took " << i_millis.count() << "ms" << std::endl;

    sieve.PrintPrimes();
    return 0;
}
