# CTF

## docker build
docker build -t <chall_name> . <br>
docker run -dp 4646:4646 <image>

## 도커 내부 설정
/etc/xinetd.d/<chall_name> <br>
/etc/services -> Local 아래 <chall_name> tcp/<port>

