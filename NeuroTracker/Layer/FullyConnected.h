#pragma once

#include "../Config.h"
#include "../Layer.h"
#include "../Utils/Random.h"

template<typename Activation>
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
		for (int i = 0; i < this->m_out_size; i++) {
			for (int j = 0; j < this->m_in_size; j++) {
				this->m_weight(i, j) = fpRand(); // normalDist();
				//std::cout << this->m_weight(i, j) << " ";
			}
		}
	}

	Matrix output(Matrix& prev_layer_data) {
		Matrix res = m_weight * prev_layer_data;
		res = res + m_bias;
		//std::cout << "weight " << "\n";
		//m_weight.print();
		//m_bias.print();
		//std::cout << "unactivated " << "\n";
		//res.print();
		res = Activation::activate(res);
		return res;
	}

	Matrix optimize(Scalar stepSize, Matrix& prev_layer_data, Matrix& next_layer_derivative) {
		Matrix newDerrivative(this->in_size(), next_layer_derivative.Col());
		Matrix out(m_out_size, prev_layer_data.Col());
		for (int i = 0; i < prev_layer_data.Col(); i++) {
			out.setCol(i, m_weight * prev_layer_data.Col(i) + m_bias);
		}
		Matrix activatedDerivative = Activation::derrivative(out);
		for (int i = 0; i < this->out_size(); i++) {
			Scalar derrivativeSum = 0;
			for (int j = 0; j < next_layer_derivative.Col(); j++) {
				derrivativeSum += activatedDerivative(i, j) * next_layer_derivative(i, j);
			}
			m_bias(i, 0) -= stepSize * derrivativeSum;
		}
		for (int j = 0; j < this->in_size(); j++) {
			for (int i = 0; i < this->out_size(); i++) {
				Scalar derrivativeSum = 0;
				for (int k = 0; k < next_layer_derivative.Col(); k++) {
					derrivativeSum += activatedDerivative(i, k) * next_layer_derivative(i, k) * prev_layer_data(j, k);
				}
				m_weight(i, j) -= stepSize * derrivativeSum;
				for (int k = 0; k < next_layer_derivative.Col(); k++) {
					newDerrivative(j, k) += activatedDerivative(i, k) * next_layer_derivative(i, k) * m_weight(i, j);
				}
			}
		}
		return newDerrivative;
	}

	Matrix derrivative(Matrix& prev_layer_data, Matrix& next_layer_derivative) {
		Matrix derivative(this->in_size(), next_layer_derivative.Col());
		Matrix bias(m_out_size, prev_layer_data.Col());
		for (int i = 0; i < prev_layer_data.Col(); i++) bias.setCol(i, m_bias);
		Matrix out = m_weight * prev_layer_data + bias;
		Matrix activatedDerivative = Activation::derrivative(out);
		for (int j = 0; j < this->in_size(); j++) {
			for (int i = 0; i < this->out_size(); i++) {
				for (int k = 0; k < next_layer_derivative.Col(); k++) {
					derivative(j, k) += activatedDerivative(i, k) * next_layer_derivative(i, k) * m_weight(i, j);
				}
			}
		}
		return derivative;
	}
};