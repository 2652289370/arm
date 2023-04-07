#pragma once
#include <iostream>
#include <memory>
#include <stdarg.h>
#include "matrix.h"
#include <math.h>
#include <vector>

#define PI 3.1415926
#define DEBUG

template <typename T, size_t N> size_t
getArraySize(T(&)[N])
{
    return N;
}

#define arraysize(array) (getArraySize(array))



struct DH
{
public:
    typedef std::shared_ptr<DH> Ptr;
    double alpha = 0.0;
    double thata = 0.0;
    double a_distance = 0.0;
    double d_distance = 0.0;
private:

public:
    DH() = default;
    DH(float al, float tha, double a, double d) :alpha(al), thata(tha), a_distance(a), d_distance(d)
    {}
    ~DH() {}
};



class Kinetic
{
private:
    size_t joint_num;
    DH* arms_ = new DH[joint_num]();
public:
    Kinetic(DH* arms, size_t num) : joint_num(num)
    {
        for (size_t i = 0; i < joint_num; i++)
        {
            arms_[i] = arms[i];
        }

    }

    /**
     * @brief 计算两个相邻杆件变换矩阵
     * @param dh 输入dh参数
    */
    matrix::TMatrix transform(const DH& dh);

    /**
     * @brief 实现机械臂正向运动学
     * @param joints 关节角度
    */
    template<typename T, typename ...Args>
    matrix::TMatrix Fk(T joint_value, Args ...args)
    {
        size_t n = sizeof...(args);
        int index = joint_num - n - 1;
        if (index < 0)
        {
            throw("error:intput joints num not correct");
        }
        arms_[index].thata = static_cast<double>(joint_value);
        return transform(arms_[index]) * Fk(args...);
    }

    template<typename T>
    matrix::TMatrix Fk(T joint_value)
    {
        arms_[joint_num - 1].thata = static_cast<double>(joint_value);
        return transform(arms_[joint_num - 1]);
    }

    matrix::TMatrix Fk(std::vector<double> joints)
    {
        size_t i = 0;
        for (auto arg : joints)
        {
            arms_[i].thata = arg;
            i++;
        }
        matrix::TMatrix res;
        res.eye();
        for (size_t i = 0; i < joint_num; i++)
        {
            res = res * transform(arms_[i]);
        }
        return res;
    }

    /**
    * @brief 生成机械臂雅可比矩阵
    * @param joints关节值
    */
    matrix::Matrix<double> jacobian(std::vector<double> joints);

 
    std::vector<std::vector<double>> Ik( matrix::TMatrix & pose)
    {
        std::vector<std::vector<double>> joints;
        
        return joints;
    }
    ~Kinetic() {}

private:
    /**
     * @brief 向量叉乘
    */
    matrix::Matrix<double> cross(matrix::Matrix<double> m1, matrix::Matrix<double> m2);
};




