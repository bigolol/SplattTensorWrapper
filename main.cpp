        #include <iostream>

    using namespace std;
    #include <iostream>
    #include "tensorlib.h"



    int main()
    {
        TensorLib tensorLib;
        SparseCooTensor<3> threeDimTensor = tensorLib.getSparseTensor<3>();

        threeDimTensor.factorize();
        return 0;
    }
