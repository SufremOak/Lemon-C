from setuptools import setup
from Cython.Build import cythonize

setup(
    name='lemonpy',
    ext_modules=cythonize("./lib/lemonpy.pyx", build_dir="./dist"),
    zip_safe=False,
)
