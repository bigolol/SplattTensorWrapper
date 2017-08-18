#ifndef COOTENSORITEM_H
#define COOTENSORITEM_H
#include <cstdint>
#include <iostream>
#include "typedefs.h"

template<size_t T_amt_dims>
class CooTensorItem {
public:
    CooTensorItem(uint32_t coords[T_amt_dims], TensorNumber val) : m_val{val} {
        for(uint32_t i = 0; i < T_amt_dims; ++i) {
            m_coords[i] = coords[i];
        }
    }

    bool operator<(const CooTensorItem& rhs) const {
        for(uint32_t i = 0; i < T_amt_dims; ++i) {
            if(m_coords[i] > rhs.m_coords[i]) return false;
            else if(m_coords[i] < rhs.m_coords[i]) return true;
        }
        return false;
    }

    bool operator>(const CooTensorItem& rhs) const { return rhs < *this; }
    bool operator<=(const CooTensorItem& rhs) const { return !(*this > rhs); }
    bool operator>=(const CooTensorItem& rhs) const { return !(*this < rhs); }

    bool operator==(const CooTensorItem& rhs) const {
        for(uint32_t i = 0; i < T_amt_dims; ++i) {
            if(m_coords[i] != rhs.m_coords[i])
                return false;
        }
        return true;
    }

    bool operator!=(const CooTensorItem& rhs) const {return !(*this==rhs);}

    uint32_t * getCoords() {
        return m_coords;
    }

    TensorNumber getVal() const {
        return m_val;
    }

    void changeVal(TensorNumber newVal) {
        m_val = newVal;
    }

    void printToStdout() const {
        std::cout << '[';
        for(uint32_t i = 0; i < T_amt_dims - 1; ++i) {
            std::cout << m_coords[i] << ", ";
        }
        std::cout << m_coords[T_amt_dims - 1] << "] ";
        std::cout << m_val << '\n';
    }

private:
    uint32_t m_coords[T_amt_dims];
    TensorNumber m_val;
};



#endif // COOTENSORITEM_H
