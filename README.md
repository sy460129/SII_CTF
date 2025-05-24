# CTF

EC2 인스턴스는 ta3.small이나 ta3.medium / ubuntu로 생성하기

# 접속

termius로 로컬 파일 서버에 올리기: https://sjparkk-dev1og.tistory.com/240

아니면 

```bash
$ ssh -i my.pem ubuntu@ip주소 
```

위처럼 접속도 가능하다.

# 도커 설치

```bash
$ sudo apt-get update
$ sudo apt-get install apt-transport-https ca-certificates curl gnupg-agent software-properties-common
$ curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -
$ sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable"
$ sudo apt-get update
$ sudo apt-get install docker-ce docker-ce-cli containerd.io
```

![image](https://github.com/user-attachments/assets/49022de6-1dfa-422b-9f2d-a728b9df0f0f)

도커 설치 완료

docker compose 설치

```bash
$ sudo curl -L "https://github.com/docker/compose/releases/download/1.27.4/docker-compose-$(uname -s)-$(uname -m)" -o /usr/local/bin/docker-compose
$ sudo chmod +x /usr/local/bin/docker-compose
$ docker-compose --version 
```

![image](https://github.com/user-attachments/assets/39b4d8a1-e943-43bf-99cb-7ea0c17c3fe3)

docker compose 설치 완료

```bash
$ sudo usermod -aG docker $USER
```

위를 통해 docker 명령어를 sudo 없이 사용가능하도록 변경

```bash
$ docker pull ctfd/ctfd
```

위를 통해 최신 ctfd 구축

![image](https://github.com/user-attachments/assets/e295409f-6d61-46c9-930d-8d282496cd2c)

이제 EC2 인스턴스에서 할 일은 없음.

각 문제별로 도커파일 내부에서 실행 → 권한은 root로 해야함..

# 예시, 문제 이름은 rtw

도커파일 예시

```Dockerfile
FROM ubuntu:20.04@sha256:e5a6aeef391a8a9bdaee3de6b28f393837c479d8217324a2340b64e45a81e0ef

RUN apt-get update && apt-get install -y socat

RUN adduser --disabled-password --gecos '' inha

WORKDIR /home/rtw

COPY ./chall ./chall
COPY ./flag ./flag

# RUN chown inha:inha ./chall ./flag
RUN chmod 755 ./chall
RUN chmod 444 ./flag

USER inha

EXPOSE 9050
CMD socat TCP-LISTEN:9050,reuseaddr,fork EXEC:/home/rtw/chall,stderr
```

도커 빌드 명령어

```bash
$ docker build -t rtw .
$ docker run -dp 9050:9050 <image_id>
```

![image](https://github.com/user-attachments/assets/94c6b998-abf0-43c4-a187-534c308d4d0b)

그럼 위처럼 생김

지금 위는 9050포트 실행 캡쳐가 없어서 5050포트 입력의 예시

```bash
$ docker exec --user root -it <container_id> /bin/bash
```

위의 명령어로 도커를 root로 들어감

→ xinetd 설정을 위해서

```bash
$ apt-get update
$ apt-get install -y vim xinetd 
```

이후 root 권한이므로 위를 설치해주면 된다.

![image](https://github.com/user-attachments/assets/ba2792fb-4041-4485-8985-44d0ebf55f3e)

아래는 설치 완료 시 화면

![image](https://github.com/user-attachments/assets/561c4ad7-20c6-41f0-9d88-87a7f2ed7484)

여기서 

```sh
$ vim /etc/xinetd.d/rtw

service rtw
{
	socket_type = stream
	flags = REUSE
	wait = no
	protocol = tcp
	user = userid
	disable = no
	server = /home/rtw/chall
}

# python 파일이라면
server = /usr/bin/python     # which python을 통해 찾은 경로를 넣어줘야함.
server_args = /home/rtw/main.py    # 문제파일의 경로

```

![image](https://github.com/user-attachments/assets/dbe733c5-cfc0-4987-9244-954b2ca0e6a6)

이후 위의 값 입력

server에는 실행 파일이 들어가야 함

이러면 nc로 접근했을 때 userid인 inha로 접속이 된다.

```sh
$ vim /etc/services
```

위로 들어가서 맨 아래로 내림

맨 아래 Local services 아래에

![image](https://github.com/user-attachments/assets/e30dfded-872c-4e6e-9755-8aee98193f48)

서비스명 포트/tcp 입력

여기서 서비스명은 /etc/xinetd.d/rtw이므로 rtw가 됨

```bash
$ service xinetd restart
```

![image](https://github.com/user-attachments/assets/fcebd889-5c6d-4b1b-a97b-dd6861fab0e5)

새로고침 한 번 해주기

이후 로컬에서

![image](https://github.com/user-attachments/assets/175b108a-1f88-4df5-bcb8-bff38fe249d8)

위처럼 접속하면 바이너리가 실행되게 됨

참고로 바이너리에 setvbuf 함수가 필수

여기까지하면 위처럼 접속은 가능하나, EC2는 변동 IP주소를 가지므로 고정된 IP를 할당받아야 한다.

# 고정 IP 설정

![image](https://github.com/user-attachments/assets/befd60de-205d-48b3-99de-d72d19f9ae4a)

![image](https://github.com/user-attachments/assets/092c3831-fc95-4e62-9dc9-eb347e933e47)

이를 위해 우선 좌측에 네트워크 및 보안 → 탄력적 IP로 들어간 후 탄력적 IP 주소 할당을 들어간다.

![image](https://github.com/user-attachments/assets/9187d33f-ce5d-4e46-bc7c-3c9444eae425)

그럼 위처럼 IP주소를 할당받는다.

![image](https://github.com/user-attachments/assets/6982d806-01d4-47f9-b306-a66424434409)

해당 주소를 누른 후 우측 상단에 있는 탄력적 IP 주소 연결을 누른다.

![image](https://github.com/user-attachments/assets/c451e0d2-564d-46c0-9414-261b9ef86610)

위처럼 인스턴스와 연결하면 된다.

# CPU 처리 부족

![image](https://github.com/user-attachments/assets/07fc9309-09f2-41d0-ba3d-323415305de8)

만약 용량이 너무 작아서 CPU 100%가 된 상황

→ 접속 자체가 불가능하다.

![image](https://github.com/user-attachments/assets/4a0bba43-dc04-470c-be7e-453c9922d8e1)

위의 인스턴스 유형 변경을 들어간다.

![image](https://github.com/user-attachments/assets/39cfb7d3-8b8e-4032-9707-3e246b0c6b90)

지피티 피셜로 위가 적당하다고 한다.

# EBS 용량 부족

![image](https://github.com/user-attachments/assets/0e32dc95-4bd6-4f04-85f3-10a991681944)

위와 같은 오류는 EBS 용량을 늘려야한다.

![image](https://github.com/user-attachments/assets/5ee222f3-74ab-454e-8297-072e674e1bcd)

위의 루트 볼륨을 들어간 후에

![image](https://github.com/user-attachments/assets/e20bae40-5642-4a6c-8e6d-20b82db2d29a)

우측 상단의 수정을 통해 늘리면 된다.

![image](https://github.com/user-attachments/assets/8c2cd638-d69b-49e8-86a3-eeb17a03725e)

이후 재접속해서 파티션 병합을 하면 된다.

# 참고자료

docker 내부 설정: https://m.blog.naver.com/cosmos243/221812378958

ubuntu에 docker 설치: https://haengsin.tistory.com/128

docker-compse 설치: https://doongdangdoongdangdong.tistory.com/137

탄력적 IP 설정: https://any-ting.tistory.com/71
