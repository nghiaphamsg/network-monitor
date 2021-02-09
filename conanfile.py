from conans import ConanFile

class ConnaPackage(ConanFile):
   name = 'network-monitor'
   version = "0.1.0"

   generators = 'cmake_find_package'

   requires = [

   ]
