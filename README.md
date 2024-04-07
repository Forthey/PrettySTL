# PrettySTL

Small library that gives pretty output of all STL containers

## Examples
### With custom types
```c++
#include <list>
#include "pretty_stl.hpp"


class Point {
public:
    double x, y;
};

std::string pointToStr(void const *point) {
    return "(" + std::to_string(((Point *) point)->x) + "; " +
           std::to_string(((Point *) point)->y) + ")";
}

int main() {
    Pretty::Stl prettyStl;
    std::list<Point> points = {
            {1, 1},
            {2, 2},
    };

    prettyStl.setElementConvertFunction(pointToStr);
    prettyStl << points;
    return 0;
}
```
### With built-in types
With built-in types the '<<' operator and 'print' is not working (program will exit with segmentation fault if you try)  
You need to use the 'printBuiltIn' function instead of 'print', or treat built-in type as custom type
```c++
#include <list>
#include "pretty_stl.hpp"

int main() {
    Pretty::Stl prettyStl;
    std::list<int> points = {1, 2, 3};

    prettyStl.printBuiltIn(points, {{Pretty::separator, " ---> "}});
    return 0;
}
```