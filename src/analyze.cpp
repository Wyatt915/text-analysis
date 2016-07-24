#include "analyze.hpp"

#include <array>
#include <vector>
#include <iostream>
#include <algorithm>

const double LETTERFREQ[] = { 0.08167, 0.01492, 0.02782, 0.04253, 0.12702,
    0.02228, 0.02015, 0.06094, 0.06966, 0.00153, 0.00772, 0.04025,
    0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987, 0.06327,
    0.09056, 0.02758, 0.00978, 0.02361, 0.00150, 0.01974, 0.00074};


std::array<long int, 26> count_chars(std::string in){
    std::array<long int, 26> out;

    for (unsigned int i = 0; i < 26; i++){ out[i] = 0; }

    for (unsigned int i = 0; i < in.length(); i++){
        if(in[i] >= 'A' && in[i] <= 'Z'){
            out[in[i] - 'A']++;
        }
    }
    return out;
}

//the count for the digram "AC" is at [0][2], "BE" is at [1][4], etc.
Matrix<int, 26, 26> count_digrams(std::vector<std::string> in){
    std::string current;
    Matrix<int, 26, 26> count;
    for (size_t i = 0; i < 26; i++) {
        for (size_t j = 0; j < 26; j++) {
            count[i][j] = 0;
        }
    }
    for (size_t i = 0; i < in.size(); i++) {
        current = in[i];
        if(current.length() <= 2){ continue; } //experimental
        for(int j = 0; j < current.length() -1; j++){
            int a = current[j] - 'A';
            int b = current[j + 1] - 'A';
            count[a][b] += 1;
        }
    }
    return count;
}

//the count for the digram "AC" is at [0][2], "BE" is at [1][4], etc.
Matrix<int, 26, 26> count_digrams(std::string in){
    Matrix<int, 26, 26> count;
    for (size_t i = 0; i < 26; i++) {
        for (size_t j = 0; j < 26; j++) {
            count[i][j] = 0;
        }
    }
    for(int j = 0; j < in.length() -1; j++){
        int a = in[j] - 'A';
        int b = in[j + 1] - 'A';
        count[a][b] += 1;
    }
    return count;
}

inline double square(double a){
    return a*a;
}

//chi-squared statistic
//http://www.practicalcryptography.com/cryptanalysis/text-characterisation/chi-squared-statistic/
double chi_sq(std::string in){
    alpha_only(in);
    int len = in.length();
    std::array<double, 26> expected;
    std::array<double, 26> count;

    std::array<long int, 26> c = count_chars(in);
    std::copy(begin(c), end(c), begin(count));

    for(int i = 0; i < 26; i++){
        expected[i] = (float)len * LETTERFREQ[i];
    }

    double chisquared = 0;

    for(int i = 0; i < 26; i++){
        chisquared += square(count[i] - expected[i]) / expected[i];
    }
    return chisquared;
}

//index of coincidence
//http://www.practicalcryptography.com/cryptanalysis/text-characterisation/index-coincidence/
double idx_coin(std::string in){
    alpha_only(in);
    double N = double(in.length()); //since this value gets squared, it is likely to overflow if left as an int type.
    std::array<long int, 26> c = count_chars(in);
    std::array<double, 26> count;
    std::copy(begin(c), end(c), begin(count));
    double numerator = 0.0;
    double denominator = N * (N - 1);   //This is where the overflow would happen.
    for (size_t i = 0; i < 26; i++) {
        numerator += count[i] * (count[i] - 1);
    }
    return numerator / denominator;
}

/**
*  Finds the frequency of occurance of each letter in a given std::string.
*/
std::array<double, 26> frequency(std::string in){
    std::array<long int, 26> count = count_chars(in);
    int sum = std::accumulate(count.begin(), count.end(), 0);
    std::array<double, 26> freq;
    for (int i = 0; i < 26; i++){
        freq[i] = (double)count[i] / (double)sum;
    }
    return freq;
}

/**
*  Prints a histogram of letter frequency.
*  @param in std::string to be analyzed.
*  @param resolution the height of the graph, in lines.
*/
void print_histogram(std::string in, int resolution){
    std::array<double, 26> freq = frequency(in);
    double max_val = *std::max_element(freq.begin(), freq.end());

    for (int i = 0, j = resolution; i < resolution; i++, j--){
        std::cout << ' ';
        for (int k = 0; k < 26; k++){
            if ((freq[k] * (resolution / max_val)) >= j){
                std::cout << "# ";
            }
            else{
                std::cout << "  ";
            }
        }
        //create labels for the vertical axis.
        std::cout << "| ";
        printf("%.3f", 100 * (max_val - (((double)i / resolution)*max_val)));
        std::cout << "%\n";
    }

    std::cout << ' ';
    for (int i = 0; i < 26; i++){
        std::cout << (char)('A' + i) << ' ';
    }
    std::cout << '\n';
}
