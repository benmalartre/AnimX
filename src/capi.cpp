//---------------------------------------------------------------------------------
// AnimX Interface for PureBasic
//---------------------------------------------------------------------------------
#include <string>
#include <capi.h>

static size_t KEYFRAME_SIZE = sizeof(adsk::Keyframe);


bool AnimXCurve::keyframeAtIndex(int index, adsk::Keyframe &key) const
{
	if (numKeys && index >= 0 && index < (int)numKeys)
	{
		memcpy(&key.time, (void*)&keys[index], KEYFRAME_SIZE);
		return true;
	}
	return false;
}

bool AnimXCurve::keyframe(double time, adsk::Keyframe &key) const
{
	if (!numKeys)return false;
	adsk::Keyframe firstKey, lastKey;
	int firstIndex, lastIndex, index;
	index = 0;
	if (this->first(firstKey))
	{
		if (time < firstKey.time)return keyframeAtIndex(0, key);
		else firstIndex = 0;
	}
	if (this->last(lastKey))
	{
		if (time > lastKey.time)return keyframeAtIndex(numKeys - 1, key);
		else lastIndex = numKeys - 1;
	}

	while (firstIndex <= lastIndex)
	{
		index = (firstIndex + lastIndex) / 2;		// compute mid point
		if (time >= keys[index].time)
			firstIndex = index + 1;					// repeat search in top half
		else if (time < keys[index].time)
			lastIndex = index - 1;					// repeat search in bottom half
		else
			break;
	}
	// if found key lies before the requested time, choose next key instead
	if (keys[index].time < time)
	{
		if (index != numKeys - 1)
			index++;
		else
			return last(key);
	}
	return keyframeAtIndex(index, key);
}

bool AnimXCurve::first(Keyframe &key) const
{
	return keyframeAtIndex(0, key);
}

bool AnimXCurve::last(Keyframe &key) const
{
	return keyframeAtIndex(numKeys - 1, key);
}

InfinityType AnimXCurve::preInfinityType() const
{
	return adsk::InfinityType::Linear;
}

InfinityType AnimXCurve::postInfinityType() const
{
	return adsk::InfinityType::Linear;
}

bool AnimXCurve::isWeighted()const
{
	return true;
}

unsigned int AnimXCurve::keyframeCount() const
{
	return numKeys;
}

bool AnimXCurve::isStatic() const
{
	return false;
}

extern "C" __declspec(dllexport) AnimXCurve * __stdcall newCurve()
{
	AnimXCurve* crv = new AnimXCurve;
	return crv;
}

extern "C" __declspec(dllexport) void __stdcall deleteCurve(AnimXCurve* curve)
{
	delete curve;
}
