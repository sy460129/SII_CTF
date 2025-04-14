FROM ubuntu:22.04@sha256:b6b83d3c331794420340093eb706a6f152d9c1fa51b262d9bf34594887c2c7ac

RUN apt-get update
RUN apt-get install -y socat

# ENV user pwn

# RUN adduser $user

# ADD ./flag /home/$user/flag
# ADD ./chall /home/$user/chall
ADD ./flag /home/rand/flag
ADD ./chall /home/rand/chall

# RUN chown root:$user /home/$user/flag
# RUN chown root:$user /home/$user/chall
# RUN chown /home/rand/flag
# RUN chown /home/rand/chall

# RUN chmod 440 /home/$user/flag
# RUN chmod 755 /home/$user/chall
RUN chmod 440 /home/rand/flag
RUN chmod 755 /home/rand/chall

WORKDIR /home/rand
# USER $user

EXPOSE 1337
CMD socat -T 90 TCP-LISTEN:1337,reuseaddr,fork EXEC:./chall
