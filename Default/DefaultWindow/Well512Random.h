#pragma once
class CWell512Random
{
protected:
  
	UINT state[16];
  
  	UINT index;
  
public:
  
  CWell512Random(UINT nSeed)
  
  {
  	index = 0;
  
	UINT s = nSeed;
  
  	for (int i = 0; i < 16; i++)
  
  	{
  		state[i] = s;
  
  		s += s + 73;
  	}
  }

  UINT Next(int minValue, int maxValue)
  
  {
  
  	return (UINT)((Next() % (maxValue - minValue)) + minValue);
  
  }
  
  
  
  UINT Next(UINT maxValue)
  {
  	return Next() % maxValue;
  }
  
  
  
  UINT Next()
  {
	  UINT a, b, c, d;
  
  	a = state[index];
  
  	c = state[(index + 13) & 15];
  
  	b = a ^ c ^ (a << 16) ^ (c << 15);
  
  	c = state[(index + 9) & 15];
  
  	c ^= (c >> 11);
  
  	a = state[index] = b ^ c;
  
  	d = a ^ ((a << 5) & 0xda442d24U);
  
  	index = (index + 15) & 15;
  
  	a = state[index];
  
  	state[index] = a ^ b ^ d ^ (a << 2) ^ (b << 18) ^ (c << 28);
  
  
  
  	return state[index];
  
  }
};

