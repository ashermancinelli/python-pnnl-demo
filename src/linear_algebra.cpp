
#include <vector>
using std::vector;

#include <thread>

#include <pybind11/stl.h>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
namespace py = pybind11;

#include <Eigen/Dense>
using namespace Eigen;

static constexpr int N_THREADS = 16;

vector<double> dot_product(const vector<double>& a, const vector<double>& b)
{
  assert(a.size() == b.size() && "Opps! Must pass in vectors of the same length.");
  vector<double> v(a.size());
  for(int i=0; i<a.size(); i++)
    v[i] = a[i] * b[i];

  return v;
}

MatrixXd mat_mul(MatrixXd& a, MatrixXd b)
{
  return a * b;
}

PYBIND11_MODULE(linear_algebra, m)
{
  m.doc() = "Performs some cool linear algebra operations!";
  m.def("dot_product", &dot_product, "Compute the dot product of two vectors");
  m.def("mat_mul", &mat_mul, "Matrix multiply");
}
