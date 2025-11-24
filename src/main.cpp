#include "testing.h++"
#include "sortings.h++"

#include <iostream>
#include <functional>
#include <vector>
#include <string>
#include <sstream>


template<typename T> void test_algo(    const std::string& algo_name,
                                        std::function<void(std::vector<T>&)> sorter,
                                        std::vector<int>& arr, bool print ){

    auto time = testing::measure_time([&](){
        if( print ) testing::print_vector(arr);
        sorter(arr);
        if( print ) testing::print_vector(arr);
    });
    
    std::cout << algo_name << ": " << time << std::endl;

}



enum State{
    READING,
    SIZE,
    ARRAY
};

enum Sorting{
    BUBBLE,
    INSERT,
    MERGE,
    QUICK
};



int main(int argc, char **argv){
    
    if( argc == 1 ){
        std::cout << "\t-a      -> enter array. to close the array use the -d flag\n";
        std::cout << "\t-s      -> enter the size of the array, the array will contain random elements\n";
        std::cout << "\t-p      -> print the output and the input array\n";
        std::cout << "\t-sb     -> bubble sort\n";
        std::cout << "\t-si     -> insertion sort\n";
        std::cout << "\t-sm     -> merge sort\n";
        std::cout << "\t-sq     -> quick sort\n";
        return 0;
    }

    std::vector<int> vec = testing::create_random_array<int>( 100, [](){return rand() % 200 - 100;} );
    std::vector<Sorting> sorts;
    bool to_print=false;

    std::stringstream stream;
    for( int i=1;  i<argc;  i++ ){
        stream << argv[i];
    }

    State state = State::READING;
    while( stream ){
        std::string s;
        stream >> s;

        switch (state)
        {
        case State::READING:{
            if( s == "-s" ){
                state = State::SIZE;
            }else if( s == "-a" ){
                state = State::ARRAY;
                vec = std::vector<int>();
            }else if( s == "-p" ){
                to_print = true;
            }else if( s == "-sb" ){
                sorts.push_back( Sorting::BUBBLE );
            }else if( s == "-si" ){
                sorts.push_back( Sorting::INSERT );
            }else if( s == "-sm" ){
                sorts.push_back( Sorting::MERGE );
            }else if( s == "-sq" ){
                sorts.push_back( Sorting::QUICK );
            }
        }break;
        case State::SIZE:{
            vec = testing::create_random_array<int>(std::stoull(s), [](){return rand() % 200 - 100;});
        }break;
        case State::ARRAY:{
            if( s == "-d" ){
                state = State::READING;
            }else{
                vec.push_back( std::stoi(s) );
            }
        }
        default:
            break;
        }
    }



    
    for( auto& a : sorts ){
        switch ( a ){
        case Sorting::BUBBLE:{
            test_algo<int>(
                "Bubble sort",
                sortings::bubble_sort<int>,
                vec,
                to_print 
            );
        }break;
        case Sorting::INSERT:{
            test_algo<int>(
                "Insertion sort",
                sortings::instertion_sort<int>,
                vec,
                to_print 
            );
        }break;
        case Sorting::MERGE:{
            test_algo<int>(
                "Merge sort",
                sortings::merge_sort<int>,
                vec,
                to_print 
            );
        }break;
        case Sorting::QUICK:{
            test_algo<int>(
                "Quick sort",
                static_cast<void(*)(std::vector<int>&)>(sortings::quick_sort<int>),
                vec,
                to_print 
            );
        }break;
        default:
            break;
        }
    }

    
    return 0;
}