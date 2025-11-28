#ifndef LOWPASSFILTER_H
#define LOWPASSFILTER_H

#include "Filter.hpp"

class LowPassFilter : public Filter {
public:
    ~LowPassFilter() override;
    void print(std::ostream& os) const override;
};

#endif
