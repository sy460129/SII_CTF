FROM ubuntu:22.04@sha256:b6b83d3c331794420340093eb706a6f152d9c1fa51b262d9bf34594887c2c7ac

RUN apt-get update && apt-get install -y socat

RUN adduser --disabled-login --gecos '' -- "inha"

WORKDIR /home/dp

COPY ./chall ./chall
COPY ./flag ./flag

RUN chown inha:inha ./chall ./flag
RUN chmod 755 ./chall
RUN chmod 444 ./flag

USER inha

EXPOSE 10001
CMD socat TCP-LISTEN:10001,reuseaddr,fork EXEC:/home/dp/chall,stderr
