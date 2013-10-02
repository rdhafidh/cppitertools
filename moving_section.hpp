#ifndef MOVING_SECTION_HPP
#define MOVING_SECTION_HPP

#include "iterator_range.hpp"
#include <vector>
#include <algorithm>

namespace iter {
    template <typename Container>
        struct moving_section_iter;
    template <typename Container>
        iterator_range<moving_section_iter<Container>>
        moving_section(Container & container, size_t s) {
            auto begin = moving_section_iter<Container>(container,s);
            auto end = moving_section_iter<Container>(container);
            return iterator_range<moving_section_iter<Container>>(begin,end);
        }

    template <typename Container>
        struct moving_section_iter {
            Container & container;
            using Iterator = decltype(container.begin());
            std::vector<Iterator> section;
            size_t section_size = 0;
            moving_section_iter(Container & c, size_t s) :
                container(c),section_size(s) {
                    for (size_t i = 0; i < section_size; ++i) 
                        section.push_back(container.begin()+i);
                }
            moving_section_iter(Container & c) : container(c)
            //creates the end iterator
            {
                section.push_back(container.end());
            }

            moving_section_iter & operator++() {
                for (auto & iter : section) {
                    ++iter;
                }
                return *this;
                //std::for_each(section.begin(),section.end(),[](Iterator & i){++i;});
            }
            bool operator!=(const moving_section_iter & rhs) {
               return this->section.back() != rhs.section.back();
            }
            auto operator*() -> std::vector<decltype(*(section.front()))>
            {
                std::vector<decltype(*(section.front()))&> vec(section.front(),section.back()+1);
                //for (auto iter : section) {
                  //  vec.push_back(*iter);
                //}
                return vec;
            }
        };
}

#endif //MOVING_SECTION_HPP
