# Stage 1 – build
FROM ubuntu:24.04 AS builder
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
      build-essential cmake git
WORKDIR /app
COPY backend/ .
RUN mkdir build && cd build && cmake .. && make

# Stage 2 – runtime
FROM ubuntu:24.04
RUN apt-get update && apt-get install -y libstdc++6
WORKDIR /app
COPY --from=builder /app/build/plantry /usr/local/bin/plantry
EXPOSE 18080
CMD ["plantry"]
