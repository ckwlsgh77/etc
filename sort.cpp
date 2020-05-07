
#include <stdio.h>
#include <vector>

using namespace std;

void insertion()
{

	int arr[8] = { 7,5,3,4,2,8,1,6 };

	for (int i = 1; i < 8; i++) {
		int j = i - 1;
		int key = arr[i];

		while (j >= 0 && arr[j] > key) {
			arr[j+1] = arr[j];
			j--;
		}
		arr[j+1] = key;

	}

	for (int i = 0; i < 8; i++)
		printf("%d ", arr[i]);

}

void bubble() {

	int arr[8] = { 7,5,3,4,2,8,1,6 };

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 7; j++) {
			int tmp = arr[j];
			if (arr[j + 1] < tmp) {
				arr[j] = arr[j+1];
				arr[j + 1] = tmp;
			}
		}
	}

	for (int i = 0; i < 8; i++)
		printf("%d ", arr[i]);
}

void merge(int *arr, int start, int end, int mid) {
	vector<int> ret;

	int s = start;
	int e = end;
	int m = mid+1;

	while (s <= mid && m <= end) {
		if (arr[s] < arr[m]) {
			ret.push_back(arr[s]); s++;}
		else {
			ret.push_back(arr[m]); m++;}

	}

	while (s <= mid) {
		ret.push_back(arr[s]);
		s++;
	}
	while (m <= end) {
		ret.push_back(arr[m]);
		m++;
	}
	int j = 0;

	for (int i = start; i <= end; i++) {
		
		arr[i] = ret[j];
		j++;
	}

}

void msort(int *arr, int start, int end) {

	if (start < end) {

		int mid = (start + end) / 2;

		msort(arr, start, mid);
		msort(arr, mid + 1, end);

		merge(arr, start, end, mid);
	}
}


void mergesort() {
	int arr[8] = { 7,5,3,4,2,8,1,6 };

	msort(arr, 0, 7);

	for (int i = 0; i < 8; i++)
		printf("%d ", arr[i]);
}

void quick(int *arr, int start, int end) {
	
	int pivot = arr[start];

	int left = start+1;
	int right = end;

	while(right>= left) {

		while (arr[left] < pivot) {
			left++;
		}
		while (arr[right] > pivot) {
			right--;
		}

		if (left <= right) {
			int tmp = arr[left];
			arr[left] = arr[right];
			arr[right] = tmp;
		}
	}

	if (start < end) {
		int tmp = arr[start];
		arr[start] = arr[right];
		arr[right] = tmp;

		quick(arr, start, right - 1);
		quick(arr, right + 1, end);
	}
}

void quicksort() {
	int arr[8] = { 7,5,3,4,2,8,1,6 };

	quick(arr,0,7);
	

	for (int i = 0; i < 8; i++)
		printf("%d ", arr[i]);
}

int main() {

	//insertion();
	//bubble();
	//mergesort();
	quicksort();
	return 0;
}