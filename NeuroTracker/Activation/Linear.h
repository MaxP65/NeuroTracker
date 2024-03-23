#pragma once
#include "../Config.h"

static class Linear {
public:
	static Scalar activate(Scalar in) {
		return in;
	}
	static Matrix activate(Matrix in) {
		return in;
	}
	static Scalar derrivative(Scalar in) {
		return in;
	}
	static Matrix derrivative(Matrix in) {
		return in;
	}
};
