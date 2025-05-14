#include <stdio.h>

int myNumber = 42;
int myArray[] = {0, 2, 3, 4,5};

int main(void) {
  printf("Welcome to data types!");
  printf("Third value of myArray is %d. \n", myArray[2]);
  printf("The array is %ld bytes long. \n", sizeof(myArray));
  
  printf("The location of the first element is %p\n", &myArray[0]);
  printf("The location of the second element is at %p\n", &myArray[1]);
    
}
