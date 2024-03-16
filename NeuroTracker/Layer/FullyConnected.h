#pragma once

#include "../Config.h"
#include "../Layer.h"
#include "../Utils/Random.h"

class FullyConnectedLayer : public Layer {
private:
	Matrix m_weight;
	Matrix m_bias;
public:
	FullyConnectedLayer(const int in_size, const int out_size) :
		Layer(in_size, out_size), m_weight(out_size, in_size), m_bias(out_size, 1)
	{
	}
	void init() {
		this->m_weight = Matrix(this->m_out_size, this->m_in_size);
		this->m_bias = Matrix(this->m_out_size, 1);
	}
	void randomize() {
		//std::cout << "rand" << this->m_weight.size();
		for (int i = 0; i < this->m_out_size; i++) {
			for (int j = 0; j < this->m_in_size; j++) {
				this->m_weight(i, j) = normalDist();
			}
		}
	}

	Matrix output(Matrix& prev_layer_data) {
		Matrix res = m_weight * prev_layer_data;
		res = res + m_bias;
		return res;
	}

	Matrix optimize(Scalar stepSize, Matrix& prev_layer_data, Matrix& next_layer_derivative) {
		Matrix newDerrivative(this->in_size(), next_layer_derivative.Col());
		for (int i = 0; i < this->out_size(); i++) {
			Scalar derrivativeSum = 0;
			for (int j = 0; j < next_layer_derivative.Col(); j++) {
				derrivativeSum += next_layer_derivative(i, j);
			}
			m_bias(i, 0) -= stepSize * derrivativeSum;
		}
		for (int j = 0; j < this->in_size(); j++) {
			for (int i = 0; i < this->out_size(); i++) {
				Scalar derrivativeSum = 0;
				for (int k = 0; k < next_layer_derivative.Col(); k++) {
					derrivativeSum += next_layer_derivative(i, k) * prev_layer_data(j, k);
					newDerrivative(j, k) += next_layer_derivative(i, k) * prev_layer_data(j, k);
				}
				m_weight(i, j) -= stepSize * derrivativeSum;
				for (int k = 0; k < next_layer_derivative.Col(); k++) {
					newDerrivative(j, k) += next_layer_derivative(i, k) * m_weight(i, j);
				}
			}

		}
		return newDerrivative;
	}
};