void build_max_heap(int* arr, int max, int i) { 
	// i - индекс родительского элемента узла (предпологаем что его значение наибольшее)
		while (i * 2 + 1 < max)
		{
			int large = i;
			int left = 2 * i + 1;
			int right = 2 * i + 2;
			if (left < max && arr[left] > arr[large]) {
				large = left;
			}
			if (right < max && arr[right] > arr[large]) {
				large = right;
			}

			

			if (large != i) {
				int tmp = arr[i];
				arr[i] = arr[large];
				arr[large] = tmp;
				i = large;
			}
			else
			{
				break;
			}
		}
	
}

int heapSort(int* arr, int size) {
	int i = (size / 2) - 1;
	while(i>=0)
	{
		build_max_heap(arr, size, i);
		--i;
	}
	


	i = size - 1;
	while (i >= 0) {
		int tmp = arr[i];
		arr[i] = arr[0];
		arr[0] = tmp;
		build_max_heap(arr, i, 0);
		--i;
	}
	return 0;
}