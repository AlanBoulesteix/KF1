CONTAINER_NAME=kfs-container
IMAGE_NAME=kfs

all: build run

build:
	docker build -f build-env/kernel.Dockerfile -t $(IMAGE_NAME) .

run:
	docker run -it --name $(CONTAINER_NAME) $(IMAGE_NAME):latest bash

start:
	docker start $(CONTAINER_NAME)

stop:
	@docker stop $(CONTAINER_NAME) 2>/dev/null || true

re: rm all

rm: 
	docker rm -f $(CONTAINER_NAME) 2>/dev/null || true
	docker rmi -f $(IMAGE_NAME) 2>/dev/null || true

nuke: stop
	docker container prune -f
	docker image prune -a -f
	docker system prune -a -f

install_hooks:
	@bash scripts/setup-git-hooks.sh

.PHONY: all build run start stop re nuke install_hooks