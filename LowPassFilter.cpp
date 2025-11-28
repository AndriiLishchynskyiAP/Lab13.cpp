#include "LowPassFilter.hpp"

LowPassFilter::~LowPassFilter() {}

void LowPassFilter::print(std::ostream& os) const {
    os << "LowPassFilter: "
       << data_.name << " "
       << data_.f1 << " "
       << data_.r << "\n";
}
