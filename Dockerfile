FROM gcc:4.9

COPY . /usr/src/myapp
WORKDIR /usr/src/myapp

RUN apt-get -y update
RUN apt-get install -y vim
RUN mkdir -p ~/.vim/backup ~/.vim/swap ~/.vim/undodir
RUN curl https://renomad.com/vimrc_unescaped > ~/.vimrc
