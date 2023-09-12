FROM debian:latest

WORKDIR /app

RUN apt-get update -y && \
    apt-get install -y gcc make && \
    rm -rf /var/lib/apt/lists/*

COPY . /app

RUN make re

RUN chmod +x /app/fvm
RUN chmod +x /app/docker/entrypoint.sh
RUN chmod +x /app/bin/*

ENTRYPOINT ["/app/docker/entrypoint.sh"]

CMD ["/app/fvm"]
