#pragma once

#include "DH.h"



matrix::TMatrix Kinetic::transform(const DH& dh)
{

    double cos_thata2 = cos(dh.thata);
    double sin_thata2 = sin(dh.thata);
    double cos_alpha1 = cos(dh.alpha);
    double sin_alpha1 = sin(dh.alpha);
    double data[16] = { cos_thata2, -sin_thata2 * cos_alpha1, sin_thata2 * sin_alpha1, dh.a_distance * cos_thata2,
                    sin_thata2, cos_thata2 * cos_alpha1, -cos_thata2 * sin_alpha1, sin_thata2 * dh.a_distance,
                    0, sin_alpha1, cos_alpha1, dh.d_distance,
                    0, 0, 0, 1 };
    matrix::TMatrix T(data);
    /*std::cout << T;*/
    return T;
}


matrix::Matrix<double> Kinetic::jacobian(std::vector<double> joints)
{
    //
    matrix::TMatrix An = Fk(joints);
    matrix::Matrix<double> p_n(3, 1);
    p_n[0][0] = An.px;
    p_n[1][0] = An.py;
    p_n[2][0] = An.pz;
    matrix::Matrix<double> J(6, joint_num);
    J[3][joint_num - 1] = An[0][2];
    J[4][joint_num - 1] = An[1][2];
    J[5][joint_num - 1] = An[2][2];

    matrix::Matrix<double> Ai(4, 4);
    Ai.eye();
    for (size_t i = 0; i < joint_num - 1; i++)
    {
        matrix::Matrix<double> z_i(3, 1);
        z_i[0][0] = Ai[0][2];
        z_i[1][0] = Ai[1][2];
        z_i[2][0] = Ai[2][2];

        matrix::Matrix<double> p_i(3, 1);
        p_i[0][0] = Ai[0][3];
        p_i[1][0] = Ai[1][3];
        p_i[2][0] = Ai[2][3];

        matrix::Matrix < double > p_in = p_n - p_i;
        matrix::Matrix< double > cross_pin = cross(z_i, p_in);
        J[0][i] = cross_pin[0][0];
        J[1][i] = cross_pin[1][0];
        J[2][i] = cross_pin[2][0];
        J[3][i] = z_i[0][0];
        J[4][i] = z_i[1][0];
        J[5][i] = z_i[2][0];
        matrix::TMatrix T = transform(arms_[i]);
        //matrix::Matrix m = T.toMatrix();
        Ai = Ai * T.toMatrix();
    }

    return J;
}


matrix::Matrix<double> Kinetic::cross(matrix::Matrix<double> m1, matrix::Matrix<double> m2)
{
    matrix::Matrix<double> res(3, 1);
    res[0][0] = m1[1][0] * m2[2][0] - m1[2][0] * m2[1][0];
    res[1][0] = m1[2][0] * m2[0][0] - m1[0][0] * m2[2][0];
    res[2][0] = m1[0][0] * m2[1][0] - m1[1][0] * m2[0][0];
    return res;
}



