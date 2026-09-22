FROM ubuntu:24.04 AS builder

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update \
    && apt-get install -y --no-install-recommends build-essential cmake \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /src
COPY . .
RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=OFF \
    && cmake --build build --parallel \
    && cmake --install build --prefix /opt/doo

FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update \
    && apt-get install -y --no-install-recommends network-manager \
    && rm -rf /var/lib/apt/lists/* \
    && useradd --system --no-create-home --shell /usr/sbin/nologin doo

COPY --from=builder /opt/doo/bin/doo /usr/local/bin/doo
COPY configs/doo.json /etc/doo/doo.json

ENTRYPOINT ["/usr/local/bin/doo"]
CMD ["--config", "/etc/doo/doo.json"]