FROM python:3.7.4

RUN groupadd -r uwsgi && useradd -r -g uwsgi uwsgi

RUN sed -i "s:deb.debian.org:mirrors.aliyun.com:g" /etc/apt/sources.list && rm -rf /var/lib/apt/lists/* && apt-get update
RUN apt-get install -y build-essential python-dev
RUN pip install -i https://pypi.tuna.tsinghua.edu.cn/simple flask uwsgi

WORKDIR /app
COPY app /app

EXPOSE 9090 9191
USER uwsgi

CMD ["uwsgi", "--http", "0.0.0.0:9090", "--wsgi-file", "/app/identidock.py", "--callable", "app", "--stats", "0.0.0.0:9191"]
