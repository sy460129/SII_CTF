FROM ubuntu:22.04@sha256:67211c14fa74f070d27cc59d69a7fa9aeff8e28ea118ef3babc295a0428a6d21

RUN apt-get update && apt-get install -y socat

RUN adduser --disabled-password --gecos '' -- "inha"

WORKDIR /home/baseball

COPY ./chall ./chall
COPY ./flag ./flag

RUN chown inha:inha ./chall ./flag
RUN chmod 755 ./chall
RUN chmod 444 ./flag

USER inha

EXPOSE 7736
CMD socat TCP-LISTEN:7736,reuseaddr,fork EXEC:/home/baseball/chall,stderr
