<h1> Network Monitor </h1>

## 1. Clone source
```
git clone https://github.com/nghiaphamsg/Network_Monitor.git
```

## 2. Run on docker

```
# Clone repo from dockerhub (requires docker version 20.10.3 or higher)
sudo docker pull nghiaphamsg/network-monitor

# Run docker container
cd Network_Monitor/docker
./run_docker_local

# [Option] You can build your dockerfile on local
cd Network_Monitor/docker
./build_dockerfile
```

## 3. Run on host (Linux 20.04)
### 3.1. Tooling
- A compiler/linker (it depends on your operating system: GCC, MSVC, or Apple Clang)
```shell
sudo apt-get update
sudo apt-get install -y build-essential gcc-10 g++-10
```

- A build system (ninja) and build generator (CMake)
```shell
sudo apt-get update
sudo apt-get install -y ninja-build cmake
ninja --version
cmake --version
```

- A dependency manager (conan) (requires Python 3)
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

- Version control software (git)
```shell
sudo apt-get update
sudo apt-get install -y git
git --version
```

### 3.2 Build
```
cd Network_Monitor
./run-build
```

## 4. Project structure
```
Network_Monitor
  ├── .gitignore
  ├── build
  │   └── .gitignore
  ├── example               (basic code implementation example)
  ├── src                   (main source)
  │   ├── ...
  │   └── main.cpp
  ├── CMakeLists.txt        (build configuration)
  ├── conanfile.py          (dependency manager)custom profile
  └── conanprofile.toml     (custom profile)

```
