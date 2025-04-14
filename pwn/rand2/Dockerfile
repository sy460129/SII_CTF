FROM ubuntu@sha256:27cb6e6ccef575a4698b66f5de06c7ecd61589132d5a91d098f7f3f9285415a9

RUN apt update
RUN apt-get install -y socat

COPY ./flag /flag
COPY ./chall /chall

RUN chmod 755 /flag /chall

EXPOSE 5864
CMD socat TCP-LISTEM:5864, reuseaddr, fork EXEC:/chall
