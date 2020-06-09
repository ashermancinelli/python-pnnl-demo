Python@PNNL
---
Short demo for interfacing Python data types and C/C++, specifically array- and matrix-like objects.

Getting Started
---

You will need:
- Python 3
- Cmake >= 3.12
- A C compiler suite

First clone the repo and pull initialize submodules:
```bash
git clone https://github.com/ashermancinelli/python-pnnl-demo.git
cd python-pnnl-demo
git submodule init
git submodule update
```

Than select the C compiler you'll use (here I use GCC 9):
```bash
export CC=gcc-9 CXX=g++-9

# Or for clang:
export CC=clang CXX=clang++
```

Ensure CMake version is greater than 3.12:
```bash
> cmake --version
cmake version 3.17.2

CMake suite maintained and supported by Kitware (kitware.com/cmake).
```


Basic Case
---
Automatic cast to `std::vector<T>` type.
From there, anything in C++-land is available to you, like threading, message passing, etc.

Advanced Cases
---
1. Eigen
    - Automatic conversion from `numpy` arrays
    
C Array
---

![c-array](./readme_images/c-array.png)


Python List
---

![python-list](./readme_images/python-list.png)


Numpy NDArray
---
![np-array](./readme_images/np-array.png)


Numpy to Eigen Conversion
---

![np-eigen](./readme_images/np-eigen.png)

