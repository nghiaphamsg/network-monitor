<h1> Network Monitor </h1>

## 1. Tooling
### A compiler/linker (it depends on your operating system: GCC, MSVC, or Apple Clang)
```shell
sudo apt-get update
sudo apt-get install -y build-essential gcc-10 g++-10
```

### A build system (ninja) and build generator (CMake)
```shell
sudo apt-get update
sudo apt-get install -y ninja-build cmake
ninja --version
cmake --version
```

### A dependency manager (conan) (requires Python 3)
```shell
sudo apt-get update
sudo apt-get install -y python3 python3-pip
python3 --version
pip3 --version

sudo pip3 install conan
conan --version

#Generate a default conan profile
conan profile new default --detect

#Configure conan to use the latest C++ ABI by patching your default profile
conan profile update settings.compiler.libcxx=libstdc++11 default
```

### Version control software (git)
```shell
sudo apt-get update
sudo apt-get install -y git
git --version
```

## 2. Development environment
### Create the top-level folder where the Project code
```shell
mkdir Network_Monitor && cd Network_Monitor
```

### Project structure
```
Network_Monitor
  ├── .gitignore
  ├── build
  │   └── .gitignore
  ├── CMakeLists.txt
  └── src
      └── main.cpp
```

### Build
```shell
cd build
cmake .. -GNinja -DCMAKE_BUILD_TYPE=Release
ninja

#Run app
./network-monitor
```
