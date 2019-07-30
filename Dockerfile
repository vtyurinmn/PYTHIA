FROM centos:7 as build

WORKDIR /app

RUN yum update -y && yum install -y wget gcc make gcc-c++

ARG PYTHIA=pythia8235

RUN wget http://home.thep.lu.se/~torbjorn/pythia8/${PYTHIA}.tgz

RUN tar xvfz ${PYTHIA}.tgz \
    && cd ${PYTHIA} \
    && ./configure \
    && make

WORKDIR /app/${PYTHIA}/examples/

COPY config/build/* ./

RUN make main201 && mv main201 /app/

FROM centos:7

COPY --from=build /app /app

WORKDIR /app
COPY config/runtime ./

ENTRYPOINT [ "./start.sh" ]