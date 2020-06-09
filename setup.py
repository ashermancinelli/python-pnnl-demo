from setuptools_cmake import *

setup(
    name='linear_algebra',
    version='0.1',
    author='Asher Mancinelli',
    author_email='asher.mancinelli@pnnl.gov',
    description='Some cool linear algebra operations',
    long_description='',
    ext_modules=[CMakeExtension('linear_algebra')],
    cmdclass=dict(build_ext=CMakeBuild),
    zip_safe=False,
)
