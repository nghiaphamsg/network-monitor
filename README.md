<h1> Network Monitor </h1>

### 1. Introduction
- Implement an itinerary recommendation engine that generates Tube trips based on real-time network load.
![Screenshot from 2021-02-18 22-30-25](https://user-images.githubusercontent.com/32474027/108364683-b0cf2580-7239-11eb-9a88-f54c45b23ab1.png)

### 2. Usage
**2.1. Clone source**
```
git clone https://github.com/nghiaphamsg/Network_Monitor.git
```

**2.2. Run on docker (recommended)**
*Note: Requires docker version 20.10.3 or higher*
```
# Clone dockerfile from dockerhub (recommended)
sudo docker pull nghiaphamsg/network-monitor

# Or build dockerfile on local (optional)
cd Network_Monitor/docker
sudo ./build_dockerfile

# Modify source path in "run_docker_local"
# Note: if you build dockerfile on local you must rename dockerfile name to "network-monitor"
vi run_docker_local

# Run docker container
sudo ./run_docker_local
```

**2.3. Run on linux host (optional)**
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

**2.4. Build**
```
cd Network_Monitor
./run-build
```

### 3. Project structure
```
Network_Monitor
  ├── build
  ├── CMakeLists.txt          (build configuration)
  ├── conanfile.py            (dependency manager)
  ├── conanprofile.toml       (custom profile)
  ├── docker                  (developer environments)
  ├── example                 (basic code implementation example)
  ├── inc                     (contain header file)
  ├── README.md
  ├── run-build               (build script)
  ├── src                     (contain cxx file)
  └── tests
```
