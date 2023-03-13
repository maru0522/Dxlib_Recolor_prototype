#pragma once

namespace YMath
{
	// ����������
	void Srand();
	// �����擾
	int GetRand(const int start, const int end);
	float GetRand(const float start, const float end, const float place);

	// ����
	template<typename T>
	T Sign(const T num);

	// �͈͐���
	template<typename T>
	T Clamp(const T num, const T lower, const T upper);
}

