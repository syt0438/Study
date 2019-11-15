FROM python:3.7.4

RUN groupadd -r uwsgi && useradd -r -g uwsgi uwsgi

RUN sed -i "s:deb.debian.org:mirrors.aliyun.com:g" /etc/apt/sources.list && rm -rf /var/lib/apt/lists/* && apt-get update
RUN apt-get install -y build-essential python-dev
RUN pip install -i https://pypi.tuna.tsinghua.edu.cn/simple flask uwsgi
RUN pip install -i https://pypi.tuna.tsinghua.edu.cn/simple requests 

WORKDIR /app
COPY app /app
COPY cmd.sh /cmd.sh

RUN chown uwsgi:uwsgi /cmd.sh 

EXPOSE 9090 9191 5000
USER uwsgi

CMD ["/cmd.sh"]
