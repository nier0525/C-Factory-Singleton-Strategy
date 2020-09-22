#ifndef _CMAINFRAME_H
#define _CMAINFRAME_H
#include "Global.h"
#include "WindowFrame.h"
#include "Mouse.h"


class CMainFrame
{
	static CMainFrame* mPthis;

	CMainFrame(){}
	~CMainFrame(){}

public:
	static CMainFrame* Create(HINSTANCE _hinstance);
	static CMainFrame* GetInstance();
	static void Destroy();

	void Initialize();
	int Run();


};

#endif
