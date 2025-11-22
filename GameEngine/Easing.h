#pragma once

namespace easing
{
	float EaseOutBounce(float x)
	{
		const float n1 = 7.5625f;
		const float d1 = 2.75f;

		if (x < 1.0f / d1)
		{
			return n1 * x * x;
		}
		else if (x < 2.0f / d1)
		{
			x -= 1.5f / d1;
			return n1 * x * x + 0.75f;
		}
		else if (x < 2.5f / d1)
		{
			x -= 2.25f / d1;
			return n1 * x * x + 0.9375f;
		}
		else
		{
			x -= 2.625f / d1;
			return n1 * x * x + 0.984375f;
		}
	}

	float EaseInBounce(float x)
	{
		if (x < 0.5f)
		{
			return (1.0f - EaseOutBounce(1.0f - 2.0f * x)) * 0.5f;
		}
		else
		{
			return (1.0f + EaseOutBounce(2.0f * x - 1.0f)) * 0.5f;
		}
	}

	float EaseInOutBounce(float x)
	{
		if (x < 0.5f)
		{
			return (1.0f - EaseOutBounce(1.0f - 2.0f * x)) * 0.5f;
		}
		else
		{
			return (1.0f + EaseOutBounce(2.0f * x - 1.0f)) * 0.5f;
		}
	}
}

