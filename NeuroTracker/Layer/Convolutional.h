#pragma once

#include "../Config.h"
#include "../Layer.h"
#include "../Utils/Random.h"

class ConvolutionalLayer : public Layer {
private:
	Matrix m_filter;
	int m_in_size_x;
	int m_in_size_y;
	int m_out_size_x;
	int m_out_size_y;
public:
	ConvolutionalLayer(const int in_size_x, const int in_size_y, const int filter_size_x, const int filter_size_y, const int channels) :
		Layer(in_size_x * in_size_y, (in_size_x - 2) * (in_size_y - 2)), m_filter(filter_size_x, filter_size_y)
	{
	}
	void init() {
		m_filter = Matrix(3, 3, std::vector<Scalar> {
			0, 0, 1,
			0, 1, 0,
			1, 0, 0
		});
	}
	void randomize() {
		
	}

	Matrix output(Matrix& prev_layer_data) {
		Matrix data(this->m_in_size_x, this->m_in_size_y, prev_layer_data.data());
		for(int i = 0; i < this->m_in_size_x)
		return res;
	}

	Matrix optimize(Scalar stepSize, Matrix& prev_layer_data, Matrix& next_layer_derivative) {
		Matrix newDerrivative(this->in_size(), next_layer_derivative.Col());
		return newDerrivative;
	}

	Matrix derrivative(Matrix& prev_layer_data, Matrix& next_layer_derivative) {
		Matrix derivative(this->in_size(), next_layer_derivative.Col());
		return derivative;
	}
};