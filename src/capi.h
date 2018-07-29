#ifndef _ANIMX_CAPI_H_
#define _ANIMX_CAPI_H_

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include <string>

#include "animx.h"
#include <unordered_map>
#include <memory>
#include <stddef.h>

using namespace adsk;

class AnimXCurve : ICurve
{
public:
	AnimXCurve::AnimXCurve() :numKeys(0), keys(NULL){};
	virtual __stdcall ~AnimXCurve(){};

	virtual void __stdcall setNumKeys(unsigned n) { numKeys = n; };
	virtual int __stdcall getNumKeys() { return numKeys; };
	virtual void __stdcall setKeys(Keyframe* k){ keys = k; };
	virtual Keyframe* __stdcall getKeys(){ return keys; };

	bool keyframeAtIndex(int index, Keyframe &key) const override;

	bool keyframe(double time, Keyframe &key) const override;

	bool first(Keyframe &key) const override;

	bool last(Keyframe &key) const override;

	InfinityType preInfinityType() const override;

	InfinityType postInfinityType() const override;

	bool isWeighted()const override;

	unsigned int keyframeCount() const override;

	bool isStatic() const override;
	
public:
	unsigned numKeys;
	Keyframe* keys;
};

extern "C" __declspec(dllexport) AnimXCurve * __stdcall newCurve();
extern "C" __declspec(dllexport) void __stdcall deleteCurve(AnimXCurve * crv);

#endif

