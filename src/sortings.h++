#ifndef SORTINGS_H
#define SORTINGS_H

#include <vector>

namespace sortings{

    template<typename T> void bubble_sort( std::vector<T>& vec ){

        for(  size_t count_to=vec.size();  count_to>0;  count_to--  ){

            for( size_t i=1;  i<count_to;  i++ ){
                if( vec[i-1] > vec[i] ){
                    std::swap(vec[i-1], vec[i]);
                }
            }

        }

    }

    template<typename T> void instertion_sort( std::vector<T>& vec ){

        for( size_t i=0;  i<vec.size();  i++ ){

            size_t min_index = i;
            for( size_t j=i;  j<vec.size();  j++ ){
                if( vec[j] < vec[min_index] ){
                    min_index = j;
                }
            }

            if( i != min_index )
                std::swap( vec[i], vec[min_index] );

        }

    }

    template<typename T> void merge_sort( std::vector<T>& vec ){
        
        if( vec.size() == 0 || vec.size() == 1 ){
            return;
        }
        
        if( vec.size() == 2 ){
            if( vec[0] > vec[1] ){
                std::swap(vec[0], vec[1]);
            }
        }

        size_t mid = vec.size() / 2;
        
        std::vector<T> vec1{ vec.begin(), vec.begin()+mid };
        std::vector<T> vec2{ vec.begin()+mid, vec.end() };

        merge_sort(vec1);
        merge_sort(vec2);

        std::vector<T> out_vec;
        out_vec.reserve(vec.size());

        size_t idx1=0, idx2=0;
        while(true){

            if( idx1==vec1.size()  &&  idx2==vec2.size() ){
                break;
            }else if( idx1==vec1.size() ){
                out_vec.push_back(vec2[idx2++]);
            }else if( idx2==vec2.size() ){
                out_vec.push_back(vec1[idx1++]);
            }else if( vec1[idx1] < vec2[idx2] ){
                out_vec.push_back( vec1[idx1++] );
            }else{
                out_vec.push_back( vec2[idx2++] );
            }
        }

        vec = std::move(out_vec);

    }

    template<typename T> void quick_sort( std::vector<T>& vec, size_t low, size_t high ){
        
        if( low >= high ){
            return;
        }

        T& pivot = vec[high-1];

        size_t i = low;

        for( size_t j=low;  j<high-1;  j++ ){
            if( vec[j] < pivot ){
                std::swap( vec[j], vec[i] );
                i++;
            }
        }

        std::swap( vec[i], vec[high-1] );

        quick_sort( vec, low, i );
        quick_sort( vec, i+1, high );


    }

    template<typename T> void quick_sort( std::vector<T>& vec ){
        size_t low = 0;
        size_t high = vec.size();

        quick_sort( vec, low, high );
    }

    
}

#endif