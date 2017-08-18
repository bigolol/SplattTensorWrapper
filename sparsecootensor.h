#ifndef SPARSECOOTENSOR_H
#define SPARSECOOTENSOR_H
#include<splatt.h>
#include<boost/container/flat_set.hpp>
#include "typedefs.h"
#include "cootensoritem.h"
#include "kruskaltensor.h"

template<size_t T_amt_dims>
class SparseCooTensor {
public:
    SparseCooTensor(double *cpd_opts) : m_cpd_opts(cpd_opts) {}
    ~SparseCooTensor(){}

    TensorNumber getVal(uint32_t coords[T_amt_dims]) {
        CooTensorItem<T_amt_dims> elem{coords, 0};
        const auto iter = std::lower_bound(
                    m_coo_elements.begin(), m_coo_elements.end(), elem);
        if(iter != m_coo_elements.end() && (*iter) == elem) {
            return iter->getVal();
        } else {
            return 0.0;
        }
    }

    void addVal(uint32_t coords[T_amt_dims], TensorNumber val) {
        CooTensorItem<T_amt_dims> elem{coords, val};
        const auto iter = std::lower_bound(
                    m_coo_elements.begin(), m_coo_elements.end(), elem);
        if(iter != m_coo_elements.end() && (*iter) == elem) {
            iter->changeVal(val);
        } else {
            m_coo_elements.push_back(elem);
            std::sort(m_coo_elements.begin(), m_coo_elements.end());
        }
    }

    void printToStdout() const {
        for(const auto& iter : m_coo_elements) {
            iter.printToStdout();
        }
    }

    KruscalTensor<T_amt_dims> factorize() {
        splatt_val_t  * vals = new splatt_val_t[m_coo_elements.size()];
        splatt_idx_t  ** inds = new splatt_idx_t*[T_amt_dims];
        for(size_t i = 0; i < T_amt_dims; ++i) {
            inds[i] = new splatt_idx_t[m_coo_elements.size()];
        }
        for(size_t i = 0; i < m_coo_elements.size(); ++i) {
            auto& elem = m_coo_elements[i];
            vals[i] = elem.getVal();
            for(size_t j = 0; j < T_amt_dims; ++j) {
                inds[j][i] = elem.getCoords()[j];
            }
        }
        splatt_csf * tensors;
        splatt_idx_t nmodes = T_amt_dims;
        int ret = splatt_csf_convert(
                    nmodes, m_coo_elements.size(), inds,
                    vals, &tensors, m_cpd_opts);
        for(size_t i = 0; i < m_coo_elements.size(); ++i) {
            delete[] inds[i];
        }
        delete[] inds;
        return KruscalTensor<T_amt_dims>{tensors, m_cpd_opts};
    }
private:

    double *m_cpd_opts;
    std::vector<CooTensorItem<T_amt_dims>> m_coo_elements;
};


#endif // SPARSECOOTENSOR_H
