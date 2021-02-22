//
// Created by mikhail on 07.02.2021.
//

#ifndef LAB_21_02_07_PCA_PCA_H
#define LAB_21_02_07_PCA_PCA_H
#include "matrix.cpp"


namespace pca {

    class PCA {
        const double eps = 1e-8;

        void center(Matrix<double> &);

        void scaling(Matrix<double> &);

        void NIPALS(Matrix<double> &, Matrix<double>&, Matrix<double> &, Matrix<double> &);


    };

}

#endif //LAB_21_02_07_PCA_PCA_H
