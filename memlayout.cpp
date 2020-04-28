/*
  This small program is run to reveal the memory layout of a c/c++ memory layout, which consists of the following secitions:
  1. Code or text segment, which holds the executable instructions 
  2. Data area, could be read-only or read-write sections, including global, static 
    a. Initialized data, b. Uninitialized 
  3  BSS, legacy of "block started symbol" from an older compiler. Similar to the above but are not initliazed
  
  3. Stack, typically starts from the higher address and grows downward, used for automatic(local) variables
     functional call frames 
  4. Heap, starts from the end of bss and grows upward, responsible for dynamically requested memory, loaded binary 
     library. 
  5. Command line arguments memory 
  Note:
  1. In linux (unistd.h), we can use int brk(void *addr) to set (success 0) and void * sbrk( intptr_t increment ) to increase ( when increment == 0, it returns the current program break) the
     data segment. 
  2. To check the memory layout of the problem, use "size memolayout"

  __TEXT  __DATA  __OBJC    others          dec             hex
    4096    4096    0       4294971392      4294979584      100003000
*/

#if 1
#include <stdio.h> 

volatile int x[10240];

int main()
{
    int global[4097];
    int i[1024] = {0};
    return 0;
}
#endif 

#if 0
// The following code test the endiness of the machine 

#include <stdio.h> 
int y = 10;
int main()
{
    unsigned int x = 1;
    char *c = (char *) &x;
    if ( (int)*c )
        printf("Little Endiness!!\n");
    else 
        printf("Big Endiness!!\n");
}
#endif 

#if 0
#include <stdio.h> 


void show_mem_rep( char *start, int n )
{
    int i;
    for ( i = 0; i < n; i++ )
    {
        printf(" %.2x addres %p\n", start[i], (int*)&start[i] );
    }
    printf("\n");
}

int main()
{
    int i = 0x76543210;
    // little endian shows: 10, 32, 54, 76
    // Big endian shows   : 76,54,32,10
    show_mem_rep( (char *)&i, sizeof(i));
    return 0;
}
#endif 
