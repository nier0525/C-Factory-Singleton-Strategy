#ifndef  _GLOBAL_H
#define  _GLOBAL_H
#include <windows.h>
#include "resource.h"

#include <iostream>
using namespace std;

#define NODATA 0
#define NULL 0
#define CHAR 128

#define GAMEMONEY 10000
#define MAXCOUNT 6
#define MAXITEM 100

enum { LOGINMENU = 1, CHARACTERMENU, STOREMENU };
enum { WENPON = 1, ARMOR , ACCESSORIES };
enum { OAK = 1, ELF };

#define MAKE_NO_COPY(CLASSNAME)                                             \
        private:                                                            \
               CLASSNAME(const CLASSNAME&){}                                \
               CLASSNAME& operator=(const CLASSNAME&);

// ΩÃ≈¨≈Ê ∆–≈œ ª˝º∫ ∏≈≈©∑Œ
#define DECLARE_SINGLETONE(CLASSNAME)                                       \
        MAKE_NO_COPY(CLASSNAME)                                             \
        private:                                                            \
			   static CLASSNAME* mPthis;									\
        public:                                                             \
			   static CLASSNAME* GetInstance();								\
               static void Destroy();										 

// ΩÃ±€≈Ê ∆–≈œ ±∏«ˆ ∏≈≈©∑Œ

#define IMPLEMENT_SINGLETON(CLASSNAME)                              \
               CLASSNAME* CLASSNAME::mPthis = nullptr;				\
                                                                    \
               CLASSNAME* CLASSNAME::GetInstance()					\
               {                                                    \
                       if(mPthis == nullptr)						\
						{											\
                              mPthis=new CLASSNAME();				\
						}											\
                        return mPthis;								\
               }													\
																	\
			   void CLASSNAME::Destroy()							\
               {													\
					if(mPthis) delete mPthis;						\
				}																												

#endif