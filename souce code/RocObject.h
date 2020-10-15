#pragma once

#include <Windows.h>

class RocObject
{
/// <summary>
/// ��Ϸ�����ģ�壬���岢��ʵ����һЩ���õ���Ϸ����Ĳ����ͷ����������꣬�ٶȣ����١�
/// �������Ϸ����������� RocLevel �����Ƽ�ʹ�� std::vector ����Ҫ�������ɺ����ٵĶ�������ڴ����
/// </summary>
public:
	VOID  Update();
	virtual VOID Render() = 0;
	virtual BOOL ShouldDestroy() = 0;

	VOID Destroy();

	FLOAT GetX();
	FLOAT GetY();
	FLOAT GetVX();
	FLOAT GetVY();
	VOID  ChangeCoord(FLOAT x, FLOAT y);
	VOID  ChangeCoordX(FLOAT x);
	VOID  ChangeCoordY(FLOAT y);
	VOID  ChangeSpeed(FLOAT vx, FLOAT vy);
	VOID  ChangeSpeedX(FLOAT vx);
	VOID  ChangeSpeedY(FLOAT vy);

protected:
	FLOAT x;
	FLOAT y;
	BOOL  isStatic;
	FLOAT xSpd;
	FLOAT ySpd;
	BOOL mustDestroy;
};

inline VOID RocObject::Update()
{
	if (!isStatic)
	{
		x += xSpd;
		y += ySpd;
	}
}

inline VOID RocObject::Destroy()
{
	mustDestroy = TRUE;
}

inline FLOAT RocObject::GetX()
{
	return x;
}

inline FLOAT RocObject::GetY()
{
	return y;
}

inline FLOAT RocObject::GetVX()
{
	return xSpd;
}

inline FLOAT RocObject::GetVY()
{
	return ySpd;
}

inline VOID RocObject::ChangeCoord(FLOAT cx, FLOAT cy)
{
	x = cx;
	y = cy;
}

inline VOID RocObject::ChangeCoordX(FLOAT cx)
{
	x = cx;
}

inline VOID RocObject::ChangeCoordY(FLOAT cy)
{
	y = cy;
}

inline VOID RocObject::ChangeSpeed(FLOAT vx, FLOAT vy)
{
	xSpd = vx;
	ySpd = vy;
}

inline VOID RocObject::ChangeSpeedX(FLOAT vx)
{
	xSpd = vx;
}

inline VOID RocObject::ChangeSpeedY(FLOAT vy)
{
	ySpd = vy;
}
