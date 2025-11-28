#ifndef FILTER_H
#define FILTER_H

#include <string>
#include <iostream>
#include "FilterData.hpp"

class Filter {
public:
    virtual ~Filter();
    void loadFromData(const FilterData& d);
    FilterData toData() const;
    virtual void print(std::ostream& os) const;
    
protected:
    FilterData data_;
};

std::ostream& operator<<(std::ostream& os, const Filter& f);

#endif
