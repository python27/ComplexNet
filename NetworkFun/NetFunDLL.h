#ifndef NetworkFun_H_
#define NetworkFun_H_
#ifdef NETWORKLIBDLL 
#define NETWORKLIBDLL extern "C" _declspec(dllimport)
#else
#define NETWORKLIBDLL extern "C" _declspec(dllexport)
#endif
#endif