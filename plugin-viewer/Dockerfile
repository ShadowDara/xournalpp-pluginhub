FROM fedora:42

# System updaten und benötigte Pakete installieren
RUN dnf -y update && \
    dnf -y install \
        gcc-c++ \
        make \
        cmake \
        gtk3 \
        gtk3-devel \
        pkgconf \
        pkgconf-pkg-config \
        glibc-devel \
        libstdc++-devel \
        libcurl-devel \
        git \
        nlohmann-json-devel \
        which && \
    dnf clean all

# Arbeitsverzeichnis festlegen
WORKDIR /app

# Projektcode kopieren
COPY . /app

# Build-Verzeichnis erstellen, bauen und App ausführen
CMD mkdir -p build && cd build && cmake .. && make && ./app
