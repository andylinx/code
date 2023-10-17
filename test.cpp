#include <iostream>
#include <vector>

int findSecondLargest(std::vector<int>& arr)
{
	int n = arr.size();

	if (n < 2)
		return -1; // No second largest element

	int max1 = std::max(arr[0], arr[1]);
	int max2 = std::min(arr[0], arr[1]);

	for (int i = 2; i < n; i++) {
		if (arr[i] > max1) {
			max2 = max1;
			max1 = arr[i];
		} else if (arr[i] > max2) {
			max2 = arr[i];
		}
	}

	return max2;
}

int main()
{
	std::vector<int> arr = { 3, 1, 4, 2, 6, 6 };
	int result = findSecondLargest(arr);

	if (result != -1)
		std::cout << "The second biggest element is: " << result << std::endl;
	else
		std::cout << "There is no second biggest element in the array." << std::endl;

	return 0;
}
