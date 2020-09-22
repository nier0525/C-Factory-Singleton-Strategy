#include "Mouse.h"

CMouse* CMouse::mPthis=NULL;

CMouse* CMouse::Create()
{
	if(!mPthis)
	{
		mPthis=new CMouse();
	}		

	return mPthis;
}

CMouse* CMouse::GetInstance()
{
	return mPthis;
}

void CMouse::Destroy()
{
	if(mPthis)
	{
		delete mPthis;
		mPthis=NULL;
	}
}

void CMouse::Initialize(HWND _hwnd)
{
	CMouse::GetInstance()->mX=0;
	CMouse::GetInstance()->mY=0;
	CMouse::GetInstance()->mOldx=0;
	CMouse::GetInstance()->mOldy=0; 
	CMouse::GetInstance()->mHwnd=_hwnd;

	CMouse::GetInstance()->mBclick=false;

}


bool CMouse::SetX(int _x)
{
	
	RECT crt;
	
	GetClientRect(mHwnd, &crt);
	int x= crt.right;
	if( _x< 0 || _x> x)
	{
		return false;
	}
	mOldx=mX;
	mX=_x;
	return true;
}

bool CMouse::Sety(int _y)
{

	RECT crt;
	
	GetClientRect(mHwnd, &crt);
	int y=crt.bottom;
	if( _y< 0 || _y> y)
	{
		return false;
	}
	mOldy=mY;
	mY=_y;
	return true;
}

bool CMouse::SetXY(LPARAM _lParam)
{
	RECT crt;
	
	GetClientRect(mHwnd, &crt);
	int x= crt.right;
	int y= crt.bottom;
	if( HIWORD(_lParam)< 0 || HIWORD(_lParam)> y || LOWORD(_lParam)<0 ||LOWORD(_lParam)>x)
	{
		return false;
	}

	mOldx=mX;
	mOldy=mY;

	mX=LOWORD(_lParam);
	mY=HIWORD(_lParam);

	return true;
}

bool CMouse::SetOldx(int _x)
{
	RECT crt;
	
	GetClientRect(mHwnd, &crt);
	int x= crt.right;
	if( _x< 0 || _x> x)
	{
		return false;
	}
	mOldx=_x;

	return true;

}

bool CMouse::SetOldy(int _y)
{
	RECT crt;
	
	GetClientRect(mHwnd, &crt);
	int y=crt.bottom;
	if( _y< 0 || _y> y)
	{
		return false;
	}
	mOldy=_y;
	
	return true;
}

bool CMouse::SetOldXY(LPARAM _lParam)
{
	RECT crt;
	
	GetClientRect(mHwnd, &crt);
	int x= crt.right;
	int y= crt.bottom;
	if( HIWORD(_lParam)< 0 || HIWORD(_lParam)> y || LOWORD(_lParam)<0 ||LOWORD(_lParam)>x)
	{
		return false;
	}

	mOldx=LOWORD(_lParam);
	mOldy=HIWORD(_lParam);

	return true;
}

LPARAM CMouse::GetXY() const
{
	LPARAM lparam=MAKEWORD(mY, mX);
	return lparam;
}

LPARAM CMouse::GetOldXY() const
{
	LPARAM lparam=MAKEWORD(mOldy, mOldx);
	return lparam;
}