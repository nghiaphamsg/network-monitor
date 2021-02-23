from conans import ConanFile, CMake

class ConnaPackage(ConanFile):
   name = 'network-monitor'
   version = "0.1.0"

   generators = 'cmake_find_package'

   requires = [
      ('boost/1.75.0'),
      ('libcurl/7.73.0'),
      ('openssl/1.1.1i'),
   ]

   default_options = (
      'boost:shared=False',
   )