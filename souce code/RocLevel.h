#pragma once

#include "RocStudio.h"

class RocLevel
{
/// <summary>
/// ROC 引擎的关卡接口，纯虚类，具体的关卡需要继承 RocLevel 并实现相关功能
/// 由 RocController 对关卡进行管理
/// </summary>
public:
	virtual VOID Load() = 0;
	virtual VOID Unload() = 0;
	virtual VOID Render() = 0;
	virtual VOID Update() = 0;
	virtual VOID HandleKey(WPARAM wParam) = 0;
};
