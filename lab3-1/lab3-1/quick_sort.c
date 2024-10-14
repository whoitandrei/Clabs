static void sort(int* arr, int min, int max) {
    while (min < max) {
        int left = min, right = max;
        int pivot = arr[(left + right) / 2];

        while (left <= right) {
            while (arr[left] < pivot) {
                left++;
            }
            while (arr[right] > pivot) {
                right--;
            }
            if (left <= right) {
                int t = *(arr + left);
                *(arr + left) = *(arr + right);
                *(arr + right) = t;
                left++;
                right--;
            }
        }
        
        if ((right - min) > (max - left)) {
            sort(arr, left, max);
            min = min;
            max = right;
        }
        else {
            sort(arr, min, right);
            min = left;
            max = max;
        }
    }

}

void quick_sort(int* arr, int lenght) {
    sort(arr, 0, lenght - 1);
}
