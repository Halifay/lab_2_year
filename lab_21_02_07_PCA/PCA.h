//
// Created by mikhail on 07.02.2021.
//

#ifndef LAB_21_02_07_PCA_PCA_H
#define LAB_21_02_07_PCA_PCA_H
#include "matrix.cpp"
typedef long double desired_type;


namespace pca {
    class PCA;
}

namespace pca {

    class PCA {
        const desired_type eps = 1e-8;
        Matrix<desired_type> D;

    public:
        PCA();
        PCA(Matrix<desired_type> &);

        void center(Matrix<desired_type> &);

        void autoscaling(Matrix<desired_type> &);

        void nipals(Matrix<desired_type> &, Matrix<desired_type> &, Matrix<desired_type> &, Matrix<desired_type> &);


    };

}

#endif //LAB_21_02_07_PCA_PCA_H
