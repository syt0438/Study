FROM ubuntu:18.04

MAINTAINER linshu <745698872@qq.com>

COPY sources.list /etc/apt/sources.list

RUN apt-get clean && apt-get update && apt-get install -y cowsay fortune

COPY entrypoint.sh /opt/entrypoint.sh

ENTRYPOINT ["/opt/entrypoint.sh"]
