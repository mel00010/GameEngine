FROM debian:experimental
EXPOSE 22
RUN echo 'deb http://deb.debian.org/debian sid main' > /etc/apt/sources.list.d/sid.list

RUN apt-get update
RUN apt-get install -t experimental -y --no-install-recommends \
    clang libc++1 libc++-dev clang-tidy lld \
    llvm python cmake doxygen ninja-build \
    libfreetype-dev libfreetype6 libglm-dev \
    libsdl2-dev libsdl2-gfx-dev libsdl2-image-dev \
    libsdl2-mixer-dev libboost-all-dev freeglut3-dev \
    libglew-dev openssh-client openssh-server git libc++abi-dev \
    ca-certificates gcc lcov libstdc++-10-dev
RUN mv /usr/bin/ld /usr/bin/ld.gold
RUN mv /usr/bin/lld /usr/bin/ld.lld
RUN update-alternatives --install /usr/bin/ld ld /usr/bin/ld.lld 100
RUN update-alternatives --install /usr/bin/ld ld /usr/bin/ld.gold 1

RUN sed -i s/#PermitRootLogin.*/PermitRootLogin\ yes/ /etc/ssh/sshd_config
RUN echo "root:root" | chpasswd


