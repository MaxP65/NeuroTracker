#pragma once

#include "../Config.h"

static class Softplus {
public:
	static Scalar activate(Scalar in) {
		return log(1 + exp(in));
	}
	static Matrix activate(Matrix in) {
		Matrix out = in;
		for (int i = 0; i < in.Row(); i++) {
			out(i, 0) = activate(in(i, 0));
		}
		return out;
	}
	static Scalar derrivative(Scalar in) {
		return exp(in) / (1 + exp(in));
	}
	static Matrix derrivative(Matrix in) {
		Matrix out = in;
		//std::cout << "Derrivative counter \n";
		for (int i = 0; i < in.Row(); i++) {
			for (int j = 0; j < in.Col(); j++) {
				out(i, j) = derrivative(in(i, j));
				//std::cout << in(i, j) << " to " << out(i, j) << "; ";
			}
		}
		//std::cout << "\n";
		return out;
	}
};