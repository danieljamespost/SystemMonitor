#!/usr/bin/env sh
docker-compose run -v "$(pwd)":/usr/src/htop:consistent htop bash
