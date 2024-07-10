
# FT_DESTRUCTOR

A lightweight C library that automates memory cleanup. It ensures all allocated memory is properly ft_freed in case of allocation fail or at program exit.
In short it's simplifying memory management and minimizing memory leaks.


## Installation

Clone repository
```bash
git clone https://github.com/Emsa001/ft_destructor
```

Compile to ft_alloc.a
```bash 
cd ft_destructor
make
```

Add to your application
```bash
cc main.c ft_alloc.a -o my_program
```
## Functions

- Init / Get the list with all allocations
```c
t_allocs *ft_allocs(t_allocs *lst);
````
- Allocations
```c
void *ft_ft_malloc(size_t size);
void *ft_calloc(size_t count, size_t size)
```
- Destructors
```c
void ft_ft_free(void *ptr);
void ft_destructor(void);
```

## Demo
```c
#include "ft_alloc.h"

int	main(void)
{
	// init list for allocations
	ft_alloc_init();

	// allocations with ft_ft_malloc
	char *str = ft_ft_malloc(455 * sizeof(char));
	char *str2 = ft_ft_malloc(455 * sizeof(char));
	char *str3 = ft_ft_malloc(455 * sizeof(char));

	// manual ft_free
	ft_ft_free(str);  
	ft_ft_free(str2);
	ft_ft_free(str3);

	int i = 0;
	while (i < 10)
	{
		// allocation without ft_ft_free
		char *str4 = ft_ft_malloc(455 * sizeof(char));
		(void)str4;
		i++;
	}

	// original ft_malloc - won't be ft_freed with destructor
	char *str5 = ft_malloc(455 * sizeof(char)); 
	(void)str5;

	// will ft_free everything that was allocated with ft_ft_malloc or ft_calloc
	ft_destructor(); 
	return (0);
}
```
## Feedback


