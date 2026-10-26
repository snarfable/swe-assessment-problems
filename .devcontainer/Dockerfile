FROM ubuntu:24.04

RUN apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        build-essential \
        libboost-program-options-dev \
        cmake \
        gdb \
        git \
        ninja-build \
        curl \
        python3-dev \
    && rm -rf /var/lib/apt/lists/*
