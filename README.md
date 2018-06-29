# ReverseAdapter
C++ adapter for traversing a container in a range-for in reverse order (C++17).


```C++
#include "reverse.h"
#include <iostream>
int main(){
	using ::adapter::reverse;
	for(auto const &i : reverse({0,1,2,3,4,5})) {
        std::cout << i << '\n';
    }
}
```

will output

```
5
4
3
2
1
0
```

The C++17 deduction guides ensure that temporaries will be kept around in the reverse object and not dangle. 
Non-temporaries will be kept by reference without overhead.

I know that C++20 ranges will provide a std::reverse range adapter that will provide almost the same, 
except that you must ensure lifetimes yourself. For example, by using the initializer in the range for.

If there is interest, I might implement a similar solution with a factory function for C++11 as well. Please ask.