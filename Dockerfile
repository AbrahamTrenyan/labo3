FROM icomputer7/ancient-ubuntu-docker:gutsy

RUN apt-get update -y && \
    apt-get install -y \
    build-essential \
    gdb \
    manpages-dev \
    manpages-posix-dev \
    libssl-dev \
    vim

# Create a simple vim configuration
RUN echo 'syntax on\nset number\nset tabstop=2\nset shiftwidth=2\nset expandtab\nset autoindent\nset hlsearch\nset incsearch\nset showmatch' > /root/.vimrc

WORKDIR /app
