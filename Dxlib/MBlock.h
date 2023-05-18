#pragma once
#include "Vector2.h"
enum Kind
{
	Normal, //����
	Move,	//�ؔ�
	Lazar,	//���[�U�[
	Spring, //�΂�
	Goal,	//�S�[��
};

class MBlock
{
public:
	MBlock();
	MBlock(Vector2 pos, Vector2 scale, int mode);
	~MBlock();
	void Initialize();
	void Update();
	void Update(Vector2& pos);
	void Draw();

	void Gravity();

	//private:
	Vector2 pos;
	Vector2 scale;

	Vector2 Lpos;
	Vector2 Lscale;

	void SetLazar(Vector2 pos, Vector2 scale);

	int mode;
};