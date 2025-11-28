#include "Filter.hpp"

Filter::~Filter() {}

void Filter::loadFromData(const FilterData& d) {
    data_ = d;
}

FilterData Filter::toData() const {
    return data_;
}

void Filter::print(std::ostream& os) const {
    os << "Filter: " << data_.toString() << "\n";
}

std::ostream& operator<<(std::ostream& os, const Filter& f) {
    f.print(os);
    return os;
}
