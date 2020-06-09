Python@PNNL
---
Short demo for interfacing Python data types and C/C++, specifically array- and matrix-like objects.

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

2. Custom Data types
