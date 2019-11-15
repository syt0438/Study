FROM ubuntu:18.04
MAINTAINER linshu <745698872@qq.com>
COPY ["/entrypoint.sh", "/data/entrypoint.sh"]

RUN chmod u+x /data/entrypoint.sh

CMD ["cmd param 1", "cmd param 2"]

ENTRYPOINT ["/data/entrypoint.sh", "entrypoint param 1", "entrypoint param 2"]
