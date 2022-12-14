//	Source: A C++ Dynamic Array
//	https://www.cs.nmsu.edu/~rth/cs/cs471/C++DynamicArray.pdf

class Dynarray
{
	private:
//		Points to the array
		int *pa;
//		Number of elements
		int length;
//		Next highest index value
		int nextIndex;

	public:
//		Constructor
		Dynarray()
		{
			pa = new int[10];
			for (int i = 0; i < 10; i++) {pa[i] = 0;}
			length = 10;
			nextIndex = 0;
		}
//		Destructor
		~Dynarray() {delete [] pa;}
//		Indexing operation
		int& operator[] (int index)
		{
//			Pointer for new array
			int *pnewa;
			if (index >= length)
			{
//				If an element is in the array, allocate a bigger array
				pnewa = new int[index + 10];
//				Copy old values
				for (int i = 0; i < nextIndex; i++) {pnewa[i] = pa[i];}
//				Initialize remainder
				for (int j = nextIndex; j < index + 10; j++) {pnewa[j] = 0;}
//				Set length to bigger size
				length = index + 10;
//				Delete old array
				delete [] pa;
//				Reassign new array
				pa = pnewa;
			}
//			Set nextIndex past index
			if (index > nextIndex) {nextIndex = index + 1;}
//			A reference to the element
			return *(pa + index);
		}
//		Add a new value to the end
		int size();
}
