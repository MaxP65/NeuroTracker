#pragma once
#include <vector>

template<typename T>
class CustomMatrix
{
private:
    size_t row_;
    size_t col_;
    std::vector<T> data_;
public:
    size_t Row() { return row_; }
    size_t Col() { return col_; }

    size_t size() {
        return data_.size();
    }
    CustomMatrix() {

    }

    CustomMatrix(size_t row, size_t col, const std::vector<T>& data) {
        if ((row * col) != data.size())
            throw std::invalid_argument("Data size does not match the dimension");
        row_ = row;
        col_ = col;
        data_ = data;

    }
    CustomMatrix(size_t row, size_t col, const  T& val)
        : row_{ row }, col_{ col }, data_{ std::vector<T>(row * col, val) } { }

    CustomMatrix(size_t row, size_t col)
        : row_{ row }, col_{ col }, data_{ std::vector<T>(row * col, 0) } { }

    T& operator()(const size_t i, const size_t j)
    {
        return data_.at(col_ * i + j);
    }

    T operator()(const size_t i, const size_t j) const
    {
        return data_.at(col_ * i + j);
    }

    CustomMatrix Col(const size_t k) {
        CustomMatrix res(row_, 1);
        for (int i = 0; i < row_; i++) {
            res(i, 0) = this->operator()(i, k);
        }
        return res;
    }

    void setCol(const size_t k, const CustomMatrix& col) {
        for (int i = 0; i < row_; i++) {
            this->operator()(i, k) = col(i, 0);
        }
    }

    CustomMatrix<T> operator*(const CustomMatrix& rhs)
    {
        //std::cout << "multiply " << data_.size() << "x" << col_ << " " << rhs.data_.size() << "x" << rhs.col_ << " ";
        if (col_ != rhs.row_)
            throw std::runtime_error("Unequal size in Matrix*");
        CustomMatrix res(row_, rhs.col_, 0.0);
        for (int i = 0; i != row_; ++i)
        {
            for (int j = 0; j != rhs.col_; ++j)
            {
                for (int k = 0; k != rhs.row_; ++k)
                {
                    res(i, j) += rhs(k, j) * this->operator()(i, k);
                }
            }
        }

        return res;
    }

    CustomMatrix<T> operator+(const CustomMatrix& rhs)
    {
        if (col_ != rhs.col_)
            throw std::runtime_error("Unequal size in Matrix*");
        CustomMatrix res(rhs.row_, col_, 0.0);
        for (int i = 0; i != rhs.row_; ++i)
        {
            for (int j = 0; j != col_; ++j)
            {
                res(i, j) += rhs(i, j) + this->operator()(i, j);
            }
        }

        return res;
    }
};