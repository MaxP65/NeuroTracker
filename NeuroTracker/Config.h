#pragma once
#include "Utils/CustomMath.h"
#include "Utils/DatasetConverter.h"

typedef double Scalar;
//typedef Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic> Matrix;
//typedef Eigen::Matrix < Scalar, Eigen::Dynamic, 1> Vector;
typedef CustomMatrix<Scalar> Matrix;

class Dataset {
public:
	int count = 0;

	std::vector<Matrix> input;
	std::vector<Matrix> output;

};

Dataset fromVector(int count, int per_set_in, int per_set_out, std::vector<Scalar> data) {
	Dataset res;
	res.count = count;
	res.input = std::vector<Matrix>(count);
	res.output = std::vector<Matrix>(count);
	for (int i = 0; i < count; i++) {
		res.input[i] = Matrix(per_set_in, 1);
		res.output[i] = Matrix(per_set_out, 1);
		for (int j = 0; j < per_set_in; j++) {
			res.input[i](j, 0) = data[i * (per_set_in + per_set_out) + j];
		}
		for (int j = 0; j < per_set_in; j++) {
			res.output[i](j, 0) = data[i * (per_set_in + per_set_out) + per_set_in + j];
		}
	}
	return res;
}