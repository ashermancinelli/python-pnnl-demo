
#include <vector>
using std::vector;

#include <pybind11/stl.h>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
namespace py = pybind11;

void some_function() {}

PYBIND11_MODULE(linear_algebra, m)
{
  m.def("some_function", &some_function);
}
