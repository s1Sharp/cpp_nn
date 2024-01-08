# ubuntu:22.04
# mcr.microsoft.com/vscode/devcontainers/cpp:0-ubuntu-22.04
FROM ubuntu:23.10

LABEL description="Development environment workspace"

ENV TZ=Etc
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN echo "root:docker" | chpasswd

RUN apt-get update && \
    apt-get install -y --force-yes \
    build-essential \
    cmake \
    clang \
    clang-format \
    lldb \
    llvm \
    devscripts \
    equivs \
    valgrind \
    git \
    g++ \
    gdb \
    libssl-dev \
    ninja-build \
    openssh-server \
    rsync \
    python3-pip \
    virtualenv \
    pkg-config \
    make \
    ninja-build \
    doxygen \
    libsqlite3-dev \
    qt6-base-dev \
&& \
    apt-get clean
# && \
#     rm -rf /var/lib/apt/lists/*

COPY requirements.txt .
COPY conanfile.txt .

RUN pip install -r requirements.txt \
# only for ubuntu>=23-**
    --break-system-packages \
    && rm requirements.txt

ENV PKG_CONFIG_PATH=/usr/share/pkgconfig

RUN conan profile detect && \
    conan install conanfile.txt \
        -of $PKG_CONFIG_PATH \
        -g PkgConfigDeps \
        -c tools.system.package_manager:mode=install \
        --build=missing

EXPOSE 22

CMD ["/usr/sbin/sshd", "-D"]
