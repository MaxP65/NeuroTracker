#pragma once
#include "../Config.h"

static class Softmax {
public:
	static Scalar activate(Scalar in) {
		return in;
	}
	static Matrix activate(Matrix in) {
		Matrix out = in;
		Scalar sum = 0;
		for (int i = 0; i < in.Row(); i++) {
			sum += exp(in(i, 0));
		}
		for (int i = 0; i < in.Row(); i++) {
			out(i, 0) = exp(in(i, 0)) / sum;
		}
		return out;
	}
	static Scalar derrivative(Scalar in) {
		return in;
	}
	static Matrix derrivative(Matrix in) {
		Matrix out(in.Row(), in.Col());
		for (int j = 0; j < in.Col(); j++) {
			Scalar sum = 0;
			for (int i = 0; i < in.Row(); i++) {
				sum += exp(in(i, 0));
			}
			for (int i = 0; i < in.Row(); i++) {
				out(i, j) = exp(in(i, j)) * sum - exp(2 * in(i, j)) / pow(sum, 2);
			}
		}
		return in;
	}
};
