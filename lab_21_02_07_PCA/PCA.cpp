//
// Created by mikhail on 07.02.2021.
//

#include "PCA.h"

using namespace pca;

void PCA::center(Matrix<double>& D)
{
    for(int j = 0; j < D.get_dimensions().second; j++)
    {
        // sum is average value of a column
        double sum = 0;
        for(int i = 0; i < D.get_dimensions().first; i++)
            sum += D[i][j];
        sum /= D.get_dimensions().first;

        // substitute this value from column
        for(int i = 0; i < D.get_dimensions().first; i++)
            D[i][j] -= sum;
    }
}

void PCA::scaling(Matrix<double>& D)
{
    for(int j = 0; j < D.get_dimensions().second; j++)
    {
        double norm_dev = 0, mi = 0;
        for(int i = 0; i < D.get_dimensions().first; i++)
            mi += D[i][j];
        for(int i = 0; i < D.get_dimensions().first; i++)
            norm_dev += pow(D[i][j] - mi, 2);
        norm_dev /= D.get_dimensions().first;
        norm_dev = sqrt(norm_dev);
        for(int i = 0; i < D.get_dimensions().first; i++)
            D[i][j] = (D[i][j] - mi) / norm_dev;
    }
}

void PCA::NIPALS(Matrix<double>& D, Matrix<double>& T, Matrix<double>& P)
{
    Matrix<double> t(D.get_dimensions().first, 1, 1);
    Matrix<double> p = ((t.Transpose()*D)/(t.Transpose()*t).sum()).Transpose();
    t = (D*p)/(p.Transpose()*p).sum();
    std::cout << "Approximation\n" << t*p << std::endl;
    std::cout << "Real matrix\n" << D << std::endl;
}
