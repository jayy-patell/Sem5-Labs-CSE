#include <stdio.h>
#define n 5
struct segTableEntry{
	int base,limit;
};
struct segTableEntry segTable[n]={
	{1400,100},
	{6300,400},
	{4300,400},
	{3200,1100},
	{4700,1000}
};
int logToPhy(int segment, int offset)
{
	if(segment<0 || segment>=n)
	{
		printf("Segment %d doesn't exist\n",segment); return -1;
	}
	if(offset<0 || offset >= segTable[segment].limit)
	{
		printf("Offset %d out of bounds\n",offset); return -1;
	}
	return segTable[segment].base + segTable[segment].limit;
}
int main()
{
	int seg[] = {2,3,0};
	int off[] = {53,852,1222};
	for(int i=0; i<3; i++)
	{	
		int ans = logToPhy(seg[i],off[i]);
		if(ans!=-1)
			printf("Logical Address: Segment %d, Offset %d --> Physical Address: %d\n", seg[i], off[i], ans);
	}
	return 0;
}