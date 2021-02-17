FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

# Update && install toolchain && cleanup after install
RUN apt-get update \
    && apt-get install -y \
    locales \
    ninja-build \
    cmake \
    python3 \
    python3-pip \
    git \
    && rm -rf /var/lib/apt/lists/* \
    && localedef -i en_US -c -f UTF-8 -A /usr/share/locale/locale.alias en_US.UTF-8

# Generate a default conan profile
# Configure conan to use the latest C++ ABI by patching your default profile
RUN pip3 install conan; \
    conan profile new default --detect; \
    conan profile update settings.compiler.libcxx=libstdc++11 default

EXPOSE 80

# Create workspace
RUN mkdir home/network_monitor

WORKDIR /home/network_monitor