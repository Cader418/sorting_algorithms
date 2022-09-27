#include <iostream>
#include <vector>
#include<chrono>
using namespace std;
using namespace std::chrono;

//_____________________________________________________________________________________________ Merge Sort Functions
void merge(int arr[], int leftBeg, int middle, int rightEnd) {
	int arrSize = (sizeof(arr) / sizeof(arr[0])) - 1;
	vector<int> vec1;
	vector<int> vec2;
	for (int i = leftBeg; i <= (middle); i++)
		vec1.push_back(arr[i]);
	for (int i = middle+1; i <= rightEnd; i++)
		vec2.push_back(arr[i]);
	
	int leftInd = 0;
	int rightInd = 0;
	int mergedInd = leftBeg;

	while (leftInd < vec1.size() && rightInd < vec2.size()) {
		if (vec1[leftInd] < vec2[rightInd]) {
			arr[mergedInd] = vec1[leftInd];
			leftInd++;
		}
		else {
			arr[mergedInd] = vec2[rightInd];
			rightInd++;                                                           
		}
		mergedInd++;
	}
	while (leftInd < vec1.size()) {
		arr[mergedInd] = vec1[leftInd];
		leftInd++;
		mergedInd++;
	}
	while (rightInd < vec2.size()) {
		arr[mergedInd] = vec2[rightInd];
		rightInd++;
		mergedInd++;
	}
}

void mergeSort(int arr[], int leftBeg, int rightEnd) {
	if (leftBeg >= rightEnd)
		return;
	int middle = (leftBeg + rightEnd) / 2;
	mergeSort(arr, leftBeg, middle);
	mergeSort(arr, middle+1, rightEnd);
	merge(arr, leftBeg, middle, rightEnd);
}
//________________________________________________________________________________________________

//________________________________________________________________________________________________ Quick Sort Functions
void swapp(int arr[], int pos1, int pos2) {
	int temp = arr[pos1];
	arr[pos1] = arr[pos2];
	arr[pos2] = temp;
}
int partition(int arr[], int beg, int end) {
	int count = 0;
	int begPoint = beg;
	int endPoint = end;
	int p = (beg + end) / 2;
	for (int i = beg; i <= end; i++) {
		if (arr[i] < arr[p] && i != p)
			count++;
	}
	swapp(arr, count+beg, p);
	p = count + beg;
	while (begPoint < p && endPoint > p) {
		if ((arr[begPoint] >= arr[p]) && (arr[endPoint] < arr[p])) {
			swapp(arr, begPoint, endPoint);
			begPoint++;
			endPoint--;
		} 
		else if ((arr[begPoint] < arr[p]) && (arr[endPoint] < arr[p]))               
			begPoint++;
		else if ((arr[begPoint] >= arr[p]) && (arr[endPoint] >= arr[p]))
			endPoint--;
		else {
			begPoint++;
			endPoint--;
		}
	}
	return p;
}
void quickSort(int arr[], int beg, int end) {
	if (beg >= end)
		return;
	int pivot = partition(arr, beg, end);
	quickSort(arr, beg, pivot);
	quickSort(arr, pivot + 1, end);
}
//___________________________________________________________________________________________________

void selection(int arr[], int size) {
	int min = 0;

	for (int i = 0; i < size-1; i++) {
		min = i;
		for (int j = i + 1; j < size; j++) {
			if (arr[j] < arr[min]) {
				min = j;
			}
		}
		int temp = arr[i];
		arr[i] = arr[min];
		arr[min] = temp;
	}
}

void insertion(int arr[], int size) {
	for (int i = 1; i < size; i++) {
		int key = arr[i];
		int j = i - 1;
		while (j >= 0 && key < arr[j]) {
			arr[j + 1] = arr[j];
			j--;                                                        
		}
		arr[j+1] = key;
	}
}

void bubble(int arr[], int size) {
	bool swap = false;
	while(1){
		swap = false;
		for (int i = 0; i < size-1; i++) {
			if (arr[i] > arr[i + 1]) {
				int temp = arr[i + 1];
				arr[i + 1] = arr[i];
				arr[i] = temp;
				swap = true;
			}
		}
		if (swap == 0)
			break;
	}
}

void displayArray(int arr[], int size) {
	for (int i = 0; i < size; i++) 
		cout << arr[i] << " ";
}

void randomizeArray(int arr[], int size) {
	for (int i = 0; i < size; i++) 
		arr[i] = rand() % 101;
}
//________________________________________________________________________________________________
int main()
{
	int size = 100000;
	int array[100000] = {};
	bool showArrays = false;
	char input = ' ';
	while (1) {
		cout << "Do you want to see unsorted and sorted arrays? Enter '1' for yes, and '0' for no: ";
		cin >> input;
		if (input == '1') {
			showArrays = 1;
			break;
		}
		else if (input == '0') {
			showArrays = 0;
			break;
		}
		else
			cout << "Invalid Input";
	}

	//Selection Sort:
	randomizeArray(array, size);
	if (showArrays) {
		cout << "\n\tUnsorted: ";
		displayArray(array, size);
	}
	auto selStart = high_resolution_clock::now();
	selection(array, size);
	auto selStop = high_resolution_clock::now();
	if (showArrays) {
		cout << "\n\tSorted: ";
		displayArray(array, size);
	}
	auto selectionDuration = duration_cast<microseconds>(selStop - selStart);
	cout << "Selection Sort Complete" << endl;

	//Insertion Sort:
	randomizeArray(array, size);
	if (showArrays) {
		cout << "\n\tUnsorted: ";
		displayArray(array, size);
	}
	auto insStart = high_resolution_clock::now();
	insertion(array, size);
	auto insStop = high_resolution_clock::now();
	if (showArrays) {
		cout << "\n\tSorted: ";
		displayArray(array, size);
	}
	auto insertionDuration = duration_cast<microseconds>(insStop - insStart);
	cout << "Insertion Sort Complete" << endl;

	//Bubble Sort:
	randomizeArray(array, size);
	if (showArrays) {
		cout << "\n\tUnsorted: ";
		displayArray(array, size);
	}
	auto bubStart = high_resolution_clock::now();
	bubble(array, size);
	auto bubStop = high_resolution_clock::now();
	if (showArrays) {
		cout << "\n\tSorted: ";
		displayArray(array, size);
	}
	auto bubbleDuration = duration_cast<microseconds>(bubStop - bubStart);
	cout << "Bubble Sort Complete" << endl;

	//Merge Sort:
	randomizeArray(array, size);
	if (showArrays) {
		cout << "\n\tUnsorted: ";
		displayArray(array, size);
	}
	auto merStart = high_resolution_clock::now();
	mergeSort(array, 0, size-1);
	auto merStop = high_resolution_clock::now();
	if (showArrays) {
		cout << "\n\tSorted: ";
		displayArray(array, size);
	}
	auto mergeDuration = duration_cast<microseconds>(merStop - merStart);
	cout << "Merge Sort Complete" << endl;

	//Quick Sort:
	randomizeArray(array, size);
	if (showArrays) {
		cout << "\n\tUnsorted: ";
		displayArray(array, size);
	}
	auto quiStart = high_resolution_clock::now();
	quickSort(array, 0, size - 1);
	auto quiStop = high_resolution_clock::now();
	if (showArrays) {
		cout << "\n\tSorted: ";
		displayArray(array, size);
	}
	auto quickDuration = duration_cast<microseconds>(quiStop - quiStart);
	cout << "Quick Sort Complete" << endl;

	
	cout << "\nTime Taken for Selection Sort: " << selectionDuration.count() << " microseconds" << endl;
	cout << "\nTime Taken fot Insertion Sort: " << insertionDuration.count() << " microseconds" << endl;
	cout << "\nTime Taken fot Bubble Sort: " << bubbleDuration.count() << " microseconds" << endl;
	cout << "\nTime Taken fot Merge Sort: " << mergeDuration.count() << " microseconds" << endl;
	cout << "\nTime Taken fot Quick Sort: " << quickDuration.count() << " microseconds" << endl;

	/*int arr[] = { 10, 4, 7, 2, 40, 3, 4, 3, 1, 2};
	mergeSort(arr, 0, (sizeof(arr) / sizeof(arr[0]))-1);                          Merge Driver
	for (int i = 0; i < ((sizeof(arr) / sizeof(arr[0]))); i++)
		cout << arr[i];*/
	//_________________________________________________________________________________________
	/*int arr[] = { 10, 4, 7, 2, 40, 3, 4, 3, 1, 2 };
	quicksort(arr, 0, (sizeof(arr) / sizeof(arr[0])) - 1);
	for (int i = 0; i < ((sizeof(arr) / sizeof(arr[0]))); i++)                    Quick Driver
		cout << arr[i] << " ";*/
	return 0;
}