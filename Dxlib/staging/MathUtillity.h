#pragma once

namespace YMath
{
	// —”‰Šú‰»
	void Srand();
	// —”æ“¾
	int GetRand(const int start, const int end);
	float GetRand(const float start, const float end, const float place);

	// •„†
	template<typename T>
	T Sign(const T num);

	// ”ÍˆÍ§ŒÀ
	template<typename T>
	T Clamp(const T num, const T lower, const T upper);
}

