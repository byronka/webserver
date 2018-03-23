FROM alpine

WORKDIR /home

ADD ./build/exec/ /home

EXPOSE 9999

CMD ["/home/server"]

