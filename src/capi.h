#ifndef _ANIMX_CAPI_H_
#define _ANIMX_CAPI_H_

#include <string>

#include "animx.h"
#include <unordered_map>
#include <memory>
#include <stddef.h>

#ifdef _WIN32
#ifdef ANIMX_STATIC_LIB
#define ANIMX_API extern "C"
#else
#define ANIMX_API extern "C" __declspec(dllexport)
#endif
#else
#define ANIMX_API extern "C"
#endif

using namespace adsk;

class AnimXCurve : ICurve
{
public:
	AnimXCurve::AnimXCurve() :numKeys(0), keys(NULL){};
	virtual ~AnimXCurve(){};

	virtual void setNumKeys(unsigned n) { numKeys = n; };
	virtual int getNumKeys() { return numKeys; };
	virtual void setKeys(Keyframe* k){ keys = k; };
	virtual Keyframe* getKeys(){ return keys; };
	virtual void setPreInfinityType(InfinityType t){ prit = t; };
	virtual void setPostInfinityType(InfinityType t){ psit = t; };

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
	InfinityType psit;
	InfinityType prit;
};

ANIMX_API AnimXCurve * newCurve();
ANIMX_API void deleteCurve(AnimXCurve * crv);

#endif

