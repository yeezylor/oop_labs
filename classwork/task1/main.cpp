#include <iostream>
#include "array.h"

void foo(Array arr) {
	for (size_t i = 0; i < arr.size(); i++) {
		std::cout << i << " elem : " << arr.get(i) << "\n";
	}
}

int main() {
	Array arr1;
	arr1.put(2, "100");
	arr1.put(5, "200");
	arr1.put(4, "49482");

	foo(arr1);
}