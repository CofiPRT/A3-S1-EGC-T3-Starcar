#pragma once

#include <functional>

struct MathUtils {

	typedef std::function<float(float)> FloatMapping;

	static FloatMapping MapLinear(float oldStart, float oldEnd, float newStart, float newEnd) {
		return [oldStart, oldEnd, newStart, newEnd](float t) {
			return newStart + (newEnd - newStart) / (oldEnd - oldStart) * (t - oldStart);
		};
	}

	static FloatMapping MapSmooth(float oldStart, float oldEnd, float newStart, float newEnd, float smoothness) {
		return [oldStart, oldEnd, newStart, newEnd, smoothness](float t) {
			return newStart + (newEnd - newStart) * powf((t - oldStart) / (oldEnd - oldStart), smoothness);
		};
	}

};