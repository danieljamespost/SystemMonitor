FROM ubuntu:latest
 
RUN apt-get -y update && apt-get install -y
RUN apt install -y build-essential \
        cmake \
        clang-format \
        libncurses5-dev \
        libncursesw5-dev \
        libncurses5-dev

# Install the Clang compiler
RUN apt-get install clang -y

RUN mkdir /usr/src/htop

CMD ["/bin/bash"]
