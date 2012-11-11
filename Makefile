
WAF=waf -j2
OUT=./build

all: build

configure: clean
	$(WAF) configure

build: configure
	$(WAF) build

clean:
	$(WAF) distclean
