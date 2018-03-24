FROM 5n5mrpesus/c_dev_environment_1:version2

WORKDIR /usr/src
RUN git clone https://github.com/byronka/webserver.git
WORKDIR /usr/src/webserver
RUN git checkout testing_git_bisect_ideas_minimal
CMD ["./set_environment_variables.sh"]
