#ifndef TESTING_H
#define TESTING_H

#include <functional>
#include <chrono>
#include <vector>
#include <string>
#include <iostream>

namespace testing{

    double measure_time( std::function<void()> func ){
        using namespace std::chrono;
        auto tws = system_clock::now();

        func();

        return duration<double>( system_clock::now() - tws ).count();
    }

    template<typename T> void print_vector( const std::vector<T>& vec,
                                            const std::string& start="{ ", 
                                            const std::string& end=" }",
                                            const std::string& sep=", " ) {
    
        std::cout << start;
        for( size_t i=0;  i<vec.size()-1;  i++ ){
            std::cout << vec[i] << sep;
        }
        std::cout << vec[vec.size()-1];
        std::cout << end;

    }

    template<typename T> std::vector<T> create_random_array( size_t size, std::function<T()> random_generator ){
        std::vector<T> out;
        out.reserve(size);

        for( size_t _=0;  _<size;  _++ ){
            out.push_back(
                random_generator()
            );
        }

        return out;
    }

}

#endif