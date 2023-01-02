# StrongUnits

##### A simple library useful to safely work with user defined units.

## Description

The aims of this project is to provide a simple library useful to safely work with user defined, easy to extend, units.  

`StrongUnit.h` provides a class template which wraps floating-point types defined by the C++ standard. In this way a user developed program can safely implement strong types representing units of different physical quantities.

The defined strong types allow automatic conversion between two units of the same quantity having different multipliers. Furthermore derived quantities can be automatically defined by combining two or more units by product and/or division operands.

This header also provides common mathematical functions and constants such as numeral unit zero (`_0`), one (`_1`), π number (`PI`) and Euler's number (`E`). 

The following headers provide strong types referring to the International System of Units ([SI Units](https://en.wikipedia.org/wiki/International_System_of_Units)) including also SI prefixes and derived units.

* `SIBaseUnits.h` &larr; `SICoherentBaseUnits.h` &larr; `NonSIBaseUnits.h`
* `SIDerivedUnits.h` &larr; `SISpecialDerivedUnits.h`

`StrongCUnit.h` provides a class template which wraps strong types defined by the above headers into complex quantities. It also defines common mathematical complex functions and the complex imaginary unit (`j`).

`StrongTypeDefinition.h` defines wrapped type macro (`STU_UNIT_TYPE`) used by the above headers.  
NOTE: `StrongUnit.h` or  `StrongCUnit.h` can be used without this header, therefore the wrapped type needs to be specified. 
On the other hand, the headers referring to the International System of Units above and the use of the already defined mathematical constants, i.e. `_0`, `_1`, `PI`, `E` and `j`, require this header to be included at first.

## Getting Started

Just include in your code the needed strong type headers, such as:
```
#include "src/lib/StrongTypeDefinition.h"
#include "src/lib/SIBaseUnits.h"
#include "src/lib/StrongCUnit.h"
```

If additional Strong Units are required just define them by means of the `DEF_SCALE`, `DEF_QUANTITY` and `DEF_UNIT` macros, into `stu` namespace, in the same source file or into a new header file.

Next enabel the following features:
```
using namespace stu::literals;  // it allows the use of "1.0_m" for defining one meter 
using namespace stu::symbols;   // it allows the use of "1*_m" for defining one meter as above
using namespace stu::prefixes;  // it allows the use of "1*k_*_m" for defining one kilometer automatically
using namespace stu::constants; // it allows the use of _0, _1, PI, E and j constants
```

Literals and symbols can be used together or separately, according to your needs, for example:
```
auto length1 = 1.0_m;
auto length2 = _m;
```

both specify one meter already defined by `SIBaseUnits.h`.
On the other hand kilometer is not defined as literal by `SIBaseUnits.h`, i.e. `_km` does not exist, but can be automaticaly defined by using symbols, such as:
```
auto length3 = k_*_m;
```

Automatic conversion can be addressed for example by:
```
stu::meter length4 = length3;
```

Complex quantities, such as electric current expressed by amper, can be defined for example as:
```
auto I0 = 1.0_A + j * 1.0_A;
auto I1 = (_1+j)*_A; 
```

Additional code examples and use-cases have been included in this project.

### Operative Systems

* Linux 
* Windows

### Dependencies

* C++ STD library, version: c++14 and above

### Installing

* Include the headers you need in your code.

### Executing program

* To build/run a specific target

```
$ bazel build //src/main:example1 --cxxopt='-std=c++14'

$ bazel run //src/main:example1 --cxxopt='-std=c++14'
```

* To run the tests

```
$ bazel test //test:strong_units_tests --test_output=all --cxxopt='-std=c++14'

$ bazel test //test:strong_complex_units_tests --test_output=all --cxxopt='-std=c++14'
```

* To debug a specific target

```
$ bazel build --compilation_mode=dbg //src/main:example1 --cxxopt='-std=c++14'
```

## Help

* To generate html documentation 
```
$ doxygen Doxyfile
```

## Authors

 
[@mattemax](mattemax@yahoo.com)

## Version History

* Initial Release

## License

* This project is licensed under the MIT License License - see the LICENSE file for details.

## Acknowledgments

* This project has been inspired by a cpponsea-2019 panel session named "Strong types in C++".  

