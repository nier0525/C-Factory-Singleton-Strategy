#ifndef _CMOUSE_H
#define _CMOUSE_H
#include "Global.h"

class CMouse
{
	static  CMouse* mPthis;
	int		mX;
	int		mY;
	int		mOldx;
	int		mOldy;
	HWND    mHwnd;
	bool	mBclick;

	CMouse(){};
	~CMouse(){};

public:

	static CMouse* Create();
	static CMouse* GetInstance();
	static void Destroy();
	
	void Initialize(HWND _hwnd);
	bool SetX(int _x);
	bool Sety(int _y);
	bool SetXY(LPARAM _lParam);

	bool SetOldx(int _x);
	bool SetOldy(int _y);
	bool SetOldXY(LPARAM _lParam);

	void SetclickDown(){mBclick=true;}
	void SetclickUp(){mBclick=false;}

	int GetX() const {return mX;}
	int Gety() const {return mY;}
	LPARAM GetXY() const;
	

	int GetOldX() const {return mOldx;}
	int GetOldy() const {return mOldy;}
	LPARAM GetOldXY() const;
	HWND  GetHWnd() const{return mHwnd;}
	bool GetClick()const{return mBclick;}


};
#endif