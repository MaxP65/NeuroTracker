#pragma once

#include "Config.h"
#include <vector>
#include "Layer.h"
#include "Layer/FullyConnected.h"

enum LayerType {
	Input = 0,
	FullyConnected
};

struct LayerData {
	LayerType type;
	int size;
};

LayerData InputLayer(int size) {
	return { LayerType::Input, size };
}

LayerData ConnectedLayer(int size) {
	return { LayerType::FullyConnected, size };
}

class NeuralNetwork {
private:
	std::vector<Layer*> m_layers;
	int m_len;
public:
	int LayerCount() const { return m_len; }

	NeuralNetwork(int length, LayerData layers[]) {
		m_len = length - 1;
		m_layers = std::vector<Layer*>(m_len);
		for (int i = 1; i < length; i++) {
			if (layers[i].type == LayerType::FullyConnected) {
				m_layers[i - 1] = new FullyConnectedLayer(layers[i - 1].size, layers[i].size);
				m_layers[i - 1]->init();
			}
		}
	}

	void randomize() {
		for (int i = 0; i < m_len; i++) {
			m_layers[i]->randomize();
		}
	}

	Matrix output(Matrix& input) {
		Matrix res = input;
		for (int i = 0; i < m_len; i++) {
			Matrix tmp = this->m_layers[i]->output(res);
			res = tmp;
		}
		return res;
	}

	void optimize(Dataset dataset, Scalar stepSize, int max_steps) {
		for (int i = 0; i < max_steps; i++) {
			std::cout << "step " << i << "\n";
			std::vector<Matrix> outputs((m_len + 1));
			//Passing all dataset through and collecting every layer results;
			for (int j = 0; j < dataset.count; j++) {
				outputs[0] = Matrix(dataset.input[0].Row(), dataset.count);
				outputs[0].setCol(j, dataset.input[j]);
			}
			for (int l = 0; l < m_len; l++) {
				outputs[l + 1] = Matrix(m_layers[l]->out_size(), dataset.count);
				for (int j = 0; j < dataset.count; j++) {
					Matrix outPrev = outputs[l].Col(j);
					outputs[l + 1].setCol(j, m_layers[l]->output(outPrev));
				}
			}
			//Calculating derrivative of error
			Matrix derrivative(m_layers[m_len - 1]->out_size(), dataset.count);
			for (int j = 0; j < m_layers[m_len - 1]->out_size(); j++) {
				for (int k = 0; k < dataset.count; k++) {
					derrivative(j, k) -= 2 * (dataset.output[k](j, 0) - outputs[m_len](j, k));
				}
			}
			//Optimizing weighgs and biases
			for (int l = m_len - 1; l >= 0; l--) {
				derrivative = m_layers[l]->optimize(stepSize, outputs[l], derrivative);
			}
			Scalar error = 0;
			for (int j = 0; j < m_layers[m_len - 1]->out_size(); j++) {
				for (int k = 0; k < dataset.count; k++) {
					error += pow(dataset.output[k](j, 0) - outputs[m_len](j, k), 2);
				}
			}
			std::cout << "error" << error <<  "\n";
		}
	}
};
