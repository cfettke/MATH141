#include <iostream>     // For standard input and output
#include <vector>       // For using std::vector
#include <algorithm>    // For algorithms like sort, lower_bound, etc.
#include <string>       // For using std::string
#include <map>          // For using std::map
#include <set>          // For using std::set
#include <stdexcept>    // For exception handling
#include <random>

// Namespace to avoid prefixing std::
using namespace std;


// function to generate permutation of probabilities. the point of this is to simulate a random process of 
// who would see the dishwasher first, as if someone with a higher probability always was the first to see it,
// the results would not be accurate
void generatePerm(vector<int>& permutation) {
    random_device rd;
    mt19937 generator(rd());
    int len = permutation.size() - 1;
    uniform_int_distribution<int> distribution(0, len);
    for(int i = 0; i < permutation.size() * 10; i++) {
        int random_number = distribution(generator);
        swap(permutation[i % (len + 1)], permutation[random_number % (len + 1)]);
    }
}


int main() {
    vector<double> people = {.3, .6};
    vector<int> permutation;
    int hourCap = 15;                       // maximum number of hours before results stop being counted
    int count = 0;                          // keeps track of total number of hours spent 
    int totalTests = 10000;                 //total number of times to run the simulation
    int curOut;
    vector<int> hourCompleted(hourCap,0);

    //generate permutiation 0 to n
    for(int i = 0; i < people.size(); i++) {
        permutation.push_back(i);
    }


    random_device rd;
    mt19937 generator(rd());
    uniform_real_distribution<double> distribution(0.0, 1.0);
    generatePerm(permutation);
    curOut = permutation[0];

    for(int numTests = 0; numTests < totalTests; numTests++) {
        int i = 0;                                                                              //hours that it took to unload;
        bool b = 1;
        while(b && i < hourCap) {
            generatePerm(permutation);
            for(int j = 0; j < people.size(); j++) {
                double random_number = distribution(generator);
                if(random_number <= people[permutation[j]]/* && permutation[j] != curOut*/) {
                    //curOut = permutation[j];
                    //cout << "cur out = " << curOut << endl;
                    b = false;
                    count += i;
                    j = people.size();
                }             
            }
            i++;
        }
        //cout << i << endl;
        hourCompleted[i - 1]++;
    }
    for(int i = 0; i < hourCompleted.size(); i++) {
        cout << "hour: " << i << ", number times finished at this hour:  " << hourCompleted[i] << endl;
    }
    cout << (float)(count) / (float)(totalTests) << endl;

    return 0;
}


