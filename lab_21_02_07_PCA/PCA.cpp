//
// Created by mikhail on 07.02.2021.
//

#include "PCA.h"

using namespace pca;

void PCA::center(Matrix<double>& D)
{
    for(int j = 0; j < D.get_dimensions().second; j++)
    {
        double sum = 0;
        for(int i = 0; i < D.get_dimensions().first; i++)
            sum += D[i][j];
        if(std::abs(sum) > eps)
            for(int i = 0; i < D.get_dimensions().first; i++)
                D[i][j]/sum;
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
        norm_dev /= D.get_dimensions().second;
        norm_dev = sqrt(norm_dev);
        for(int i = 0; i < D.get_dimensions().first; i++)
            D[i][j] /= norm_dev;
    }
}

void PCA::NIPALS(Matrix<double>& D, Matrix<double>& E, Matrix<double>& T, Matrix<double>& P)
{

}
