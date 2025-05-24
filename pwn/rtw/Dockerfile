FROM ubuntu:20.04@sha256:e5a6aeef391a8a9bdaee3de6b28f393837c479d8217324a2340b64e45a81e0ef

RUN apt-get update && apt-get install -y socat

RUN adduser --disabled-password --gecos '' -- "inha"

WORKDIR /home/rtw
USER inha

COPY ./chall ./chall
COPY ./flag ./flag

USER root
RUN chmod 755 ./chall
RUN chmod 644 ./flag

USER inha

EXPOSE 9050
CMD socat TCP-LISTEN:9050,reuseaddr,fork EXEC:/home/rtw/chall,stderr
