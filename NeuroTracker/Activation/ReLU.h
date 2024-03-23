#pragma once

#include "../Config.h"

class ReLU {
public:
	static Scalar activate(Scalar in) {
		return max(0.0, in);
	}
	static Matrix activate(Matrix& in) {
		Matrix out = in;
		for (int i = 0; i < in.Row(); i++) {
			out(i, 0) = activate(in(i, 0));
		}
		return out;
	}
	static Scalar derrivative(Scalar in) {
		return in > 0 ? 1 : 0;
	}
	static Matrix derrivative(Matrix& in) {
		Matrix out = in;
		for (int i = 0; i < in.Row(); i++) {
			for (int j = 0; j < in.Col(); j++) {
				out(i, j) = derrivative(in(i, j));
				//std::cout << in(i, j) << " to " << out(i, j) << "; ";
			}
		}
		return out;
	}
};