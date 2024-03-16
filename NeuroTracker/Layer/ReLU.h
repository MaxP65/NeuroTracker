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
	Matrix output(Matrix& prev_layer_data) {
		Matrix res = prev_layer_data;
		for (int i = 0; i < this->m_in_size; i++) {
			res(i, 0) = std::max(0.0, res(i, 0));
		}
		return res;
	}
	Matrix optimize(Scalar stepSize, Matrix& prev_layer_data, Matrix& next_layer_derivative) {
		Matrix derrivative(prev_layer_data.Row(), next_layer_derivative.Col();
		for (int i = 0; i < derrivative.Row()) {
			for (int i = 0; i < derrivative.Col()) {

			}
		}
		return next_layer_derivative;
	}
};