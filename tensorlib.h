#ifndef TENSORLIB_H
#define TENSORLIB_H
#include "splatt.h"
#include "sparsecootensor.h"
class TensorLib {
public:
    TensorLib() {
        m_cpd_opts = splatt_default_opts();
    }
    ~TensorLib() {
        splatt_free_opts(m_cpd_opts);
    }

    template<size_t T_amt_dims>
    SparseCooTensor<T_amt_dims> getSparseTensor(){ return SparseCooTensor<T_amt_dims>(m_cpd_opts); }

private:
    double * m_cpd_opts;

};

#endif // TENSORLIB_H
