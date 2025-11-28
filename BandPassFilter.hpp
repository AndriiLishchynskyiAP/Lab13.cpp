#ifndef BANDPASSFILTER_H
#define BANDPASSFILTER_H

#include "Filter.hpp"

class BandPassFilter : public Filter {
public:
    ~BandPassFilter() override;
    void print(std::ostream& os) const override;
};

#endif
