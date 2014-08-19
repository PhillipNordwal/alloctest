#include<stdio.h>
#include<stdlib.h>

/* malloc_test returns 0 if size was not able to be malloc'ed
 * @param size [in] number of byte's to malloc
 * @return 0 if size wasn't able to be malloc'ed, something else otherwise
 */
unsigned short malloc_test(size_t size) {
	unsigned short retVal = 0;
	char * pChar = 0;
	pChar = malloc(size);
	retVal = pChar != 0;
	free(pChar);
	return retVal;
}

/* malloc_loop loops a malloc call, doubling the requested size each time
 * it returns the first unsuccessful size.
 * @param starting_size [in] number of byte's to start the malloc doublinng at
 * @return last size unsuccessfully malloc'ed
 */
size_t malloc_loop(const size_t starting_size) {
	size_t i = starting_size;
	while(malloc_test(i*=2)){}
	return (i);
}

/* binary_search will search through the inclusive range of min and max and
 * return the highest value for which the function fp is true.
 * @param min [in] minimum value to test
 * @param max [in] maximum value to test
 * @param fp [in] a pointer to a function that returns 0 on failure, and takes 
 * 	a size_t as a parameter.
 * @return the highest value that when used as an argument to fp, doesn't
 * 	return 0
 */
size_t binary_search(size_t min, size_t max, unsigned short (*fp)(size_t size)){
	size_t tmp;
	/* make sure min <= max
	 * return min if min == max
	 */
	if ( min > max) {
		tmp=min;
		min=max;
		max=tmp;
	}

	while ( min != max - 1) {
		tmp = (min + max)/2;
		if ( (*fp)(tmp) ) {
			min = tmp;
		} else {
			max = tmp;
		}
	}
	return min;
}

int main(int argc, char **argv) {
	/* start at 1GB */
	size_t unsuccessful = malloc_loop(1<<30);
	size_t successful = unsuccessful/2;
	size_t highest = binary_search(successful, unsuccessful, &malloc_test);
	printf("%lu\n", highest);
	return 0;
}

/* vim: set ts=4 sw=4 ai magic smarttab noet : */
