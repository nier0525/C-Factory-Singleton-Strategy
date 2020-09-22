#include "BackBit.h"

CBackBit::CBackBit(HWND  _hwnd, int _width , int _height )
{
	HDC hdc=GetDC(_hwnd);
	mHbit = CreateCompatibleBitmap(hdc, _width, _height);
	HDC hMemDC=CreateCompatibleDC(hdc);
	HBITMAP hOldBit=(HBITMAP)SelectObject(hMemDC, mHbit);
	PatBlt(hMemDC,0,0,_width,_height,WHITENESS);
	SelectObject(hMemDC,hOldBit);
	DeleteDC(hMemDC);
	ReleaseDC(_hwnd, hdc);

	mWidth=_width;
	mHeight=_height;
}
CBackBit::~CBackBit()
{
	DeleteObject(mHbit);
}
bool CBackBit::SetHeight(int _height)
{
	BITMAP bit;
	GetObject(mHbit,sizeof(BITMAP),&bit);
	
	int y=bit.bmHeight;

	if( _height< 0 || _height> y)
	{
		return false;
	}

	mHeight=_height;
	return true;
}

bool CBackBit::SetWidth(int _width)
{

	BITMAP bit;
	GetObject(mHbit,sizeof(BITMAP),&bit);
	int x=bit.bmWidth;	

	if( _width< 0 || _width> x)
	{
		return false;
	}

	mWidth=_width;
	return true;
}

void CBackBit::SCreanDraw(HDC _hdc, int _x, int _y)
{
	HDC MemDC;
	HBITMAP OldBitmap;
	int bx,by;
	BITMAP bit;

	MemDC=CreateCompatibleDC(_hdc);
	OldBitmap=(HBITMAP)SelectObject(MemDC, mHbit);

	GetObject(mHbit,sizeof(BITMAP),&bit);
	bx=bit.bmWidth;
	by=bit.bmHeight;

	BitBlt(_hdc,_x,_y,bx,by,MemDC,0,0,SRCCOPY);

	SelectObject(MemDC,OldBitmap);
	DeleteDC(MemDC);
}

void CBackBit::BitmapDraw(int _x, int _y, HBITMAP _hbit)
{
	HDC MemDC1, MemDC2, hdc;
	HBITMAP OldBitmap1, OldBitmap2;
	int bx,by;
	BITMAP bit;

	hdc=GetDC(mHWnd);
	MemDC1=CreateCompatibleDC(hdc);
	MemDC2=CreateCompatibleDC(hdc);

	OldBitmap1=(HBITMAP)SelectObject(MemDC1, mHbit);

	GetObject(_hbit,sizeof(BITMAP),&bit);
	bx=bit.bmWidth;
	by=bit.bmHeight;

	OldBitmap2=(HBITMAP)SelectObject(MemDC2, _hbit);
	BitBlt(MemDC2,_x,_y,bx,by,MemDC2,0,0,SRCCOPY);

	SelectObject(MemDC1,OldBitmap1);
	SelectObject(MemDC2,OldBitmap2);
	DeleteDC(MemDC1);
	DeleteDC(MemDC2);
}

void CBackBit::ClearBitMap()
{
	HDC hdc=GetDC(mHWnd);	
	HDC hMemDC=CreateCompatibleDC(hdc);
	HBITMAP hOldBit=(HBITMAP)SelectObject(hMemDC, mHbit);
	PatBlt(hMemDC,0,0,mWidth,mHeight,WHITENESS);
	SelectObject(hMemDC,hOldBit);
	DeleteDC(hMemDC);
	ReleaseDC(mHWnd, hdc);	
}

HDC	CBackBit::GetBitmapDC() const
{
	HDC hdc=GetDC(mHWnd);
	HDC hMemDC=CreateCompatibleDC(hdc);
	HBITMAP hOldBit=(HBITMAP)SelectObject(hMemDC, mHbit);
	ReleaseDC(mHWnd, hdc);	
	return hMemDC;
}

void CBackBit::DeleteBitmapDC(HDC _dc)
{
	DeleteDC(_dc);
}


void CBackBit::GdiBitMapDraw(HDC hdc, int x, int y, int bx, int by, HBITMAP hBitmap) {
	HDC MemDC;
	HBITMAP OldBitMap;
	int x1, y1;
	BITMAP bitmap;

	MemDC = CreateCompatibleDC(hdc);
	OldBitMap = (HBITMAP)SelectObject(MemDC, hBitmap);

	GetObject(hBitmap, sizeof(BITMAP), &bitmap);
	x1 = bitmap.bmWidth;
	y1 = bitmap.bmHeight;

	GdiTransparentBlt(hdc, x, y, bx, by, MemDC, 0, 0, x1, y1, RGB(255, 255, 255));

	SelectObject(MemDC, OldBitMap);
	DeleteDC(MemDC);
}