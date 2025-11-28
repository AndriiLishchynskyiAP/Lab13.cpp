#ifndef FILTERDATA_H
#define FILTERDATA_H

#include <string>
#include <sstream>
#include <algorithm>

struct FilterData {
    std::string type;
    std::string name;
    double f1;
    double f2;
    double r;

    FilterData() : type("LP"), name(""), f1(0), f2(0), r(0) {}

    FilterData operator+(const FilterData& other) const {
        FilterData res;
        res.type = type == other.type ? type : "Mixed";
        res.name = name + "+" + other.name;
        res.f1 = std::min(f1, other.f1);
        res.f2 = std::max(f2, other.f2);
        res.r = r + other.r;
        return res;
    }

    std::string toString() const {
        std::ostringstream oss;
        oss << type << " " << name << " " << f1 << " " << f2 << " " << r;
        return oss.str();
    }
};

#endif
