#include "mt_allocators.h"
#include "mt_dsa.h"

int
main(void) {
	u8 *my_array = array(u8, &allocator);

	printf("Adding elements to the array:\n");
	for (size_t i = 0; i <= 5; ++i) {
		array_append(my_array, i);
	}

	printf("Array contents after appending:\n");
	for (size_t i = 0; i < array_length(my_array); i++) {
		printf("my_array[%zu] = %d\n", i, my_array[i]);
	}

	printf("\nRemoving element at index 2:\n");
	array_remove(my_array, 2);

	printf("Array contents after removal:\n");
	for (size_t i = 0; i < array_length(my_array); i++) {
		printf("my_array[%zu] = %d\n", i, my_array[i]);
	}

	printf("\nPopping the last element:\n");
	array_pop_back(my_array);

	printf("Array contents after popping:\n");
	for (size_t i = 0; i < array_length(my_array); i++) {
		printf("my_array[%zu] = %d\n", i, my_array[i]);
	}
   
	free(array_header(my_array));
}