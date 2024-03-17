#pragma once

#include "../Config.h"

static class ReLU {
public:
	static Scalar activate(Scalar in) {
		return max(0.0, in);
	}
	static Matrix activate(Matrix in) {
		for (int i = 0; i < in.Row(); i++) {
			in(i, 0) = activate(in(i, 0));
		}
		return in;
	}
	static Scalar derrivative(Scalar in) {
		return in > 0 ? 1 : 0;
	}
	static Matrix derrivative(Matrix in) {
		for (int i = 0; i < in.Row(); i++) {
			for (int j = 0; j < in.Col(); j++) {
				in(i, j) = derrivative(in(i, j));
			}
		}
		return in;
	}
};