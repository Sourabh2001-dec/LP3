/*
 * Problem Statement :- Write a program for analysis of quick sort by using deterministic
 * 						and randomized variant.
 */

// Case	Time 		Complexity
// Best Case		O(n*logn)
// Average Case		O(n*logn)
// Worst Case		O(n2)

// Space Complexity	O(n*logn)
// Stable			NO

#include <bits/stdc++.h>
using namespace std;

// Deterministic Quick-sort
//  Pivot => last element in the array

int partition(vector<int> &a, int l, int h)
{
	int index = l;
	int pivot = h;
	for (int i = l; i < h; i++)
	{
		if (a[i] < a[pivot])
		{
			swap(a[i], a[index]);
			index++;
		}
	}
	swap(a[pivot], a[index]);
	return index;
}

int r_partition(vector<int> &a, int l, int h)
{
	// 1 2 3 4 l->5 6 10 8 9 h->7
	int num = rand();
	int ri = l + num % (h - l + 1);
	swap(a[h], a[ri]);
	return partition(a, l, h);
}

void quickSort(vector<int> &a, int low, int high)
{
	if (low >= high)
		return;

	int pi = partition(a, low, high);
	quickSort(a, low, pi - 1);
	quickSort(a, pi + 1, high);
}

void r_quickSort(vector<int> &a, int low, int high)
{
	if (low >= high)
		return;

	int pi = r_partition(a, low, high);
	r_quickSort(a, low, pi - 1);
	r_quickSort(a, pi + 1, high);
}

int main()
{
	int choice, n;
	while (true)
	{
		cout << "\n\n Main-Menu \n\t 1. Deterministic Quick-Sort \n\t 2. Randomized Quick-Sort \n\t 3. Exit " << endl;
		cout << "\n\t Enter choice: ";
		cin >> choice;

		if (choice == 1)
		{
			cout << "\n\t Enter the number of data element to be sorted: ";
			cin >> n;
			vector<int> a(n);

			cout << "\n\t Enter the array: ";
			for (int i = 0; i < n; i++)
				cin >> a[i];

			quickSort(a, 0, n - 1);

			cout << "\n\t Sorted Data: ";
			for (int i = 0; i < n; i++)
				cout << a[i] << " ";
		}
		else if (choice == 2)
		{
			cout << "\n\t Enter the number of data element to be sorted: ";
			cin >> n;
			vector<int> a(n);

			cout << "\n\t Enter the array: ";
			for (int i = 0; i < n; i++)
				cin >> a[i];

			quickSort(a, 0, n - 1);

			cout << "\n\t Sorted Data: ";
			for (int i = 0; i < n; i++)
				cout << a[i] << " ";
		}
		else if (choice == 3)
		{
			cout << "\n\t Thank you!!!";
			exit(0);
		}
		else
		{
			cout << "\n\t Enter valid choice" << endl;
		}
	}
}
