#!/bin/bash

docker buildx build -t my-fvm-image -f docker/Dockerfile .
docker run -it my-fvm-image "$@"