FROM centos:7

WORKDIR /app

RUN yum update -y && yum install -y wget gcc make gcc-c++

ARG PYTHIA=pythia8235

RUN wget http://home.thep.lu.se/~torbjorn/pythia8/${PYTHIA}.tgz

RUN tar xvfz ${PYTHIA}.tgz \
    && cd ${PYTHIA} \
    && ./configure \
    && make

WORKDIR /app/${PYTHIA}/examples/

COPY config/* ./

RUN make main201

ENTRYPOINT [ "./start.sh" ]