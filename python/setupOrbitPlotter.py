from setuptools import setup
from Cython.Build import cythonize

setup(
    ext_modules=cythonize("/media/MAGI_II/Projects/Worldbuilder/python/orbitPlotter.pyx"),
)
