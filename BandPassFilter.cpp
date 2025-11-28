#include "BandPassFilter.hpp"

BandPassFilter::~BandPassFilter() {}

void BandPassFilter::print(std::ostream& os) const {
    os << "BandPassFilter: "
       << data_.name << " "
       << data_.f1 << " "
       << data_.f2 << " "
       << data_.r << "\n";
}
