//
// Created by mikhail on 07.02.2021.
//

#include "PCA.h"

using namespace pca;

PCA::PCA(){}

PCA::PCA(Matrix<desired_type> &D):PCA()
{
    std::cout << "start of algorithm" << std::endl;
    Matrix<desired_type> E, T, P;
    this->D = D;
    std::cout << "after D" << std::endl;
    std::cout << this->D << std::endl;
    // std::cout << "center" << std::endl;
    // center(this->D);
    std::cout << this->D << std::endl;
    std::cout << "autoscaling" << std::endl;
    autoscaling(this->D);
    std::cout << this->D << std::endl;
    std::cout << "nipals" << std::endl;
    nipals(this->D, E, T, P);
    std::cout << "result\n" << T*P << std::endl;
}

void PCA::center(Matrix<desired_type>& D)
{
    for(int j = 0; j < D.get_dimensions().second; j++)
    {
        // sum is average value of a column
        desired_type sum = 0;
        for(int i = 0; i < D.get_dimensions().first; i++)
            sum += D[i][j];
        sum /= D.get_dimensions().first;

        // substitute this value from column
        for(int i = 0; i < D.get_dimensions().first; i++)
            D[i][j] -= sum;
    }
}

void PCA::autoscaling(Matrix<desired_type>& D)
{
    for(int j = 0; j < D.get_dimensions().second; j++)
    {
        desired_type norm_dev = 0, mi = 0;
        for(int i = 0; i < D.get_dimensions().first; i++)
            mi += D[i][j];
        mi /= D.get_dimensions().first;
        for(int i = 0; i < D.get_dimensions().first; i++)
            norm_dev += pow(D[i][j] - mi, 2);
        norm_dev /= D.get_dimensions().first - 1;
        norm_dev = sqrt(norm_dev);
        for(int i = 0; i < D.get_dimensions().first; i++)
            D[i][j] = (D[i][j] - mi) / norm_dev;
    }
}

void PCA::nipals(Matrix<desired_type>& D, Matrix<desired_type>& E, Matrix<desired_type>& T, Matrix<desired_type>& P)
{
    // if(t_column < 0 || t_column > D.get_dimensions().first)
    //     throw std::length_error("t_column must not be less than 0 and not bigger than number of rows in given matrix");
    E = Matrix<desired_type>(D);
    std::vector<std::vector<desired_type>> t_vec, p_vec;
    for(int i = 0; i < E.get_dimensions().second; i++) {
        Matrix<desired_type> local_T = Matrix<desired_type>(E.Transpose()[i]).Transpose(); //T is a column with a height of matrix E height
        Matrix<desired_type> local_P;
        Matrix<desired_type> old_T;
        do {
            local_P = (local_T.Transpose() * E) / ((local_T.Transpose() * local_T).sum());
            local_P = local_P.Transpose();
            local_P = local_P / (local_P.norm());
            old_T = local_T;
            local_T = (E * local_P) / (((local_P.Transpose() * local_P).sum()));
            // std::cout << "while condition " << ((old_T - local_T) * ((old_T - local_T).Transpose())).sum() << std::endl;
        } while ((old_T - local_T).norm() > eps);
        Matrix<desired_type> new_D = local_T * local_P.Transpose();
        E = (E - new_D);
        t_vec.push_back(local_T.Transpose()[0]);
        p_vec.push_back(local_P.Transpose()[0]);
    }
    T = Matrix<desired_type>(t_vec).Transpose();
    P = Matrix<desired_type>(p_vec).Transpose();
    std::cout << "scores \n" << T << std::endl;
    std::cout << "loadings \n" << P << std::endl;
    // std::cout << "iter: " << iter << std::endl;
}
