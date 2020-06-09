
#include <vector>
using std::vector;

#include <pybind11/stl.h>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/eigen.h>
namespace py = pybind11;

#include <Eigen/Dense>
using namespace Eigen;

vector<double> dot_product(const vector<double>& a, const vector<double>& b)
{
  assert(a.size() == b.size() && "Opps! Must pass in vectors of the same length.");
  vector<double> v(a.size());
  for(int i=0; i<a.size(); i++)
    v[i] = a[i] * b[i];

  return v;
}

MatrixXd mat_mul(const MatrixXd& a, const MatrixXd& b)
{
  return a * b;
}

PYBIND11_MODULE(linear_algebra, m)
{
  m.def("dot_product", &dot_product);
  m.def("mat_mul", &mat_mul);
  m.def("mat_add", [](const MatrixXd& a, const MatrixXd& b) { return a + b; });
}
