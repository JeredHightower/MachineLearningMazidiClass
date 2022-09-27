#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <string>       // std::string
#include <vector>       // std::vector
#include <math.h>       // sqrt

double sum(std :: vector<double> input){
    if (input.empty())
        return 0;
    
    double sum = 0.0;
    for (double i : input)
        sum += i;
    
    return sum;
}

double mean(std :: vector<double> input){
    if (input.empty())
        return 0;
    
    double mean = 0.0;
    for (double i : input)
        mean += i;
    
    return mean / input.size();
}

double median(std :: vector<double> input){
    if (input.empty())
        return 0;

    sort(input.begin(), input.end());

    // Either select middle element or average middle element if size is even
    if(input.size() % 2 == 0){
        return input.at(input.size()/2 - 1);
    }
    else if (input.size() > 1){
        return (input.at(input.size()/2 - 1) + input.at(input.size()/2))/2.0;
    }

    return input.at(0);
    
}

double range(std :: vector<double> input){
    if (input.empty())
        return 0;
    
    sort(input.begin(), input.end());
    
    return input.at(input.size() - 1) - input.at(0);
}

void print_stats(std :: vector<double> input){
    sort(input.begin(), input.end());

    std :: cout << "Sum : " << sum(input) << std :: endl;
    std :: cout << "\nMean : " << mean(input) << std :: endl;
    std :: cout << "\nMedian : " << median(input) << std :: endl;
    std :: cout << "\nRange : " << range(input) << std :: endl;
    std :: cout << input.at(0) << " " << input.at(input.size() -1) << std :: endl;
}

double variance(std :: vector<double> input){
    double input_mean = mean(input);

    double sum = 0.0;

    for(int i = 0; i < input.size(); i++){
        sum += (input.at(i) - input_mean) * (input.at(i) - input_mean);
    }

    return sum / (input.size() - 1);
}

double covar(std :: vector<double> rm, std :: vector<double> medv){
    double rm_mean = mean(rm);
    double medv_mean = mean(medv);

    double sum = 0.0;

    for(int i = 0; i < rm.size(); i++){
        sum += (rm.at(i) - rm_mean) * (medv.at(i) - medv_mean);
    }

    return sum / (rm.size() - 1);
}

double cor(std :: vector<double> rm, std :: vector<double> medv){
    return covar(rm, medv) / (sqrt(variance(rm)) * sqrt(variance(medv)));
}

int main(int argc, char** argv) {
    std :: ifstream inFS; // Input file stream
    std :: string line;
    std :: string rm_in, medv_in;
    const int MAX_LEN = 1000;
    std :: vector<double> rm(MAX_LEN);
    std :: vector<double> medv(MAX_LEN);

    // Try to open file
    std :: cout << "Opening file Boston.csv." << std :: endl;

    inFS.open("Boston.csv");
    if (!inFS.is_open()) {
        std :: cout << "Could not open file Boston.csv." << std :: endl;
        return 1; // 1 indicates error
    }

    // Can now use inFS stream like cin stream
    // Boston.csv should contain two doubles

    std :: cout << "Reading line 1" << std :: endl;
    getline(inFS, line);

    // echo heading
    std :: cout << "heading: " << line << std :: endl;

    int numObservations = 0;
    while (inFS.good()) {

        getline(inFS, rm_in, ',');
        getline(inFS, medv_in, '\n');

        rm.at(numObservations) = std :: stof(rm_in);
        medv.at(numObservations) = std :: stof(medv_in);

        numObservations++;
    }

    rm.resize(numObservations);
    medv.resize(numObservations);

    std :: cout << "new length " << rm.size() << std :: endl;

    std :: cout << "Closing file Boston.csv." << std :: endl;
    inFS.close(); // Done with file, so close it

    std :: cout << "Number of records: " << numObservations << std :: endl;
    
    std :: cout << "\nStats for rm" << std :: endl;
    print_stats(rm);

    std :: cout << "\nStats for medv" << std :: endl;
    print_stats(medv);

    std :: cout << "\nCovariance = " << covar(rm, medv) << std :: endl;

    std :: cout << "\nCorrelation = " << cor(rm, medv) << std :: endl;

    std :: cout << "\nProgram Terminated.";

    return 0;
}