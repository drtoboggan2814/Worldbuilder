//	C++ libraries
#include <vector>

int findClosest(int x, int y, int target)
{
	if ((target - x) >= (y - target))	{return y;}
	else								{return x;}
}


//	Take a sorted array of values and return the index of the value closest to target
int findClosestElementDouble (const std::vector<double>& inputArray, int inputArraySize, double target)
{
//	If target is smaller than the 0 index
	if (target <= inputArray.at(0))	{return 0;}
//	If target is greater than the last index
	if (target >= inputArray[inputArraySize - 1])	{return (inputArraySize - 1);}
//	Otherwise, perform binary search
	int left = 0, right = inputArraySize, mid = 0;
	while (left < right)
	{
		mid = (left + right) / 2;
		if (inputArray[mid] == target)	{return inputArray[mid];}
//			If the target is less than the array element
		if (target < inputArray[mid])
		{
//				If target is greater than the previous to mid, return the closest of the two
			if ((mid > 0) && (target > inputArray[mid - 1]))	{return findClosest(inputArray[mid], inputArray[mid + 1], target);}
//				Repeat for left half
			right = mid;
		}

//			If target is greater than mid
		else
		{
			if ((mid < (inputArraySize - 1)) && (target < inputArray[mid + 1]))	{return findClosest(inputArray[mid], inputArray[mid + 1], target);}
//				Update mid
			left = mid + 1;
		}
	}


	return mid;
}
