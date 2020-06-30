#include <thread>
#include <vector>
#include <pybind11/stl.h>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/eigen.h>
namespace py = pybind11;

#include <Eigen/Dense>
using namespace Eigen;
using Eigen::Ref;
using Array = Eigen::Array<double, Eigen::Dynamic, 1>;

std::vector<double> dot_product(const std::vector<double>& a, const std::vector<double>& b)
{
  assert(a.size() == b.size() && "Opps! Must pass in vectors of the same length.");
  std::vector<double> v(a.size());
  for(int i = 0; i < a.size(); i++)
    v[i] = a[i] * b[i];

  return v;
}

MatrixXd mat_mul(const MatrixXd& a, const MatrixXd& b) { return a * b; }

VectorXd add_vec_sync(const VectorXd& a, const VectorXd& b)
{
  const auto size = a.size();
  VectorXd c(size);
  for(int i = 0; i < size; i++)
  {
    c[i] = a[i] + b[i];
  }
  return c;
}

py::array_t<double> add_vec_thread(py::array_t<double> _a, py::array_t<double> _b)
{
  const auto size = _a.size();

  /*
   * Get information about the numpy arrays
   */
  py::buffer_info a_info = _a.request(), b_info = _b.request();

  if(a_info.ndim != 1 || b_info.ndim != 1)
    throw std::runtime_error("Number of dimensions must be one");

  if(a_info.size != b_info.size)
    throw std::runtime_error("Input shapes must match");

  /*
   * Allocate a new numpy array to return to the caller
   */
  auto _c                = py::array_t<double>(a_info.size);
  py::buffer_info c_info = _c.request();

  double *a = static_cast<double*>(a_info.ptr), *b = static_cast<double*>(b_info.ptr),
         *c = static_cast<double*>(c_info.ptr);

#pragma omp parallel for
  for(int i = 0; i < size; i++)
  {
    c[i] = a[i] + b[i];
  }
  return _c;
}

void add_vec_kernel(double*, double*, double*, int);
py::array_t<double> add_vec_cuda(py::array_t<double> _a, py::array_t<double> _b)
{
  const auto size = _a.size();
  py::buffer_info a_info = _a.request(), b_info = _b.request();

  if(a_info.ndim != 1 || b_info.ndim != 1)
    throw std::runtime_error("Number of dimensions must be one");

  if(a_info.size != b_info.size)
    throw std::runtime_error("Input shapes must match");

  /*
   * Allocate a new numpy array to return to the caller
   */
  auto _c                = py::array_t<double>(a_info.size);
  py::buffer_info c_info = _c.request();
  double *a = static_cast<double*>(a_info.ptr), *b = static_cast<double*>(b_info.ptr),
         *c = static_cast<double*>(c_info.ptr);
  add_vec_kernel(a, b, c, a_info.size);
  return _c;
}

PYBIND11_MODULE(linear_algebra, m)
{
  m.def("dot_product", &dot_product);
  m.def("mat_mul", &mat_mul);
  m.def("mat_add", [](const MatrixXd& a, const MatrixXd& b) { return a + b; });
  m.def("add_vec_sync", &add_vec_sync);
  m.def("add_vec_thread", &add_vec_thread);
  m.def("add_vec_cuda", &add_vec_cuda);
}
