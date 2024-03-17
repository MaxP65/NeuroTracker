#pragma once

#include "Config.h"
#include "Activation.h"

class Layer {
protected:
	const int m_in_size;
	const int m_out_size;
public:
	Layer(const int in_size, const int out_size) :
		m_in_size(in_size),
		m_out_size(out_size) {}

	int in_size() const { return m_in_size; }
	int out_size() const { return m_out_size; }

	virtual void init() = 0;
	virtual void randomize() = 0;
	virtual Matrix output(Matrix& prev_layer_data) = 0;
	virtual Matrix optimize(Scalar stepSize, Matrix& prev_layer_data, Matrix& layer_data, Matrix& next_layer_derivative) = 0;
};