from conans import ConanFile, CMake

class ConnaPackage(ConanFile):
   name = 'network-monitor'
   version = "0.1.0"

   generators = 'cmake_find_package'

   requires = [
      ('boost/1.75.0'),
   ]

   default_options = (
      'boost:shared=False',
   )