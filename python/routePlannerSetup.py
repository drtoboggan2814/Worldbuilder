from setuptools import setup
from Cython.Build import cythonize

setup(
#	ext_modules = cythonize("Z:\Projects\Worldbuilder\python\\routePlanner.pyx")
	ext_modules = cythonize("/media/MAGI_II/Projects/Worldbuilder/python/routePlanner.pyx")

)
