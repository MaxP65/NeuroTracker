#pragma once

#pragma once

#include <Eigen/Core>
#include "../Config.h"
#include "../Layer.h"
#include "../Utils/Random.h"

class FullyConnectedLayer : public Layer {
public:
	FullyConnectedLayer(const int in_size, const int out_size) :
		Layer(in_size, out_size)
	{
	}
	void init() {
	}
	void randomize() {
	}
	Matrix derrivative() {

	}
	Matrix output(Matrix& prev_layer_data) {
		Matrix res = prev_layer_data;
		for (int i = 0; i < this->m_in_size; i++) {
			res(i, 0) = std::max(0.0, res(i, 0));
		}
		return res;
	}
	Matrix optimize(Scalar stepSize, Matrix& prev_layer_data, Matrix& next_layer_derivative) {
		return next_layer_derivative;
	}
};