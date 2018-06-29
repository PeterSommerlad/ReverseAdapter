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