#ifndef KRUSKALTENSOR_H
#define KRUSKALTENSOR_H
#include <cstdint>
#include <iostream>
#include "typedefs.h"
#include "splatt.h"
template<size_t T_amt_dims>
class KruscalTensor {
public:
    KruscalTensor(splatt_csf * tensors, double * cpd_opts) {
        int ret = splatt_cpd_als(tensors, 10, cpd_opts, &m_factored);
        //TODO check for errors

    }

    TensorNumber getVal(uint32_t coords [T_amt_dims]) {

    }

private:
    splatt_kruskal m_factored;      //saves modes in row_major
};

#endif // KRUSKALTENSOR_H
