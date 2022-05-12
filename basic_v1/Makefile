.PHONY: all

CFLAGS=$(shell pkg-config --libs --cflags gio-2.0 gio-unix-2.0 glib-2.0)

all: dbus service client
service: service.o service-test.o
	gcc -o $@ $^ $(CFLAGS) -g
client: client.o service-test.o
	gcc -o $@ $^ $(CFLAGS) -g
service.o: service.c
	gcc -o $@ $^ -c $(CFLAGS) -g
client.o: client.c
	gcc -o $@ $^ -c $(CFLAGS) -g
service-test.o: service-test.c
	gcc -o $@ $^ -c $(CFLAGS) -g

dbus:
	gdbus-codegen --interface-prefix org.tizen. --generate-c-code service-test service-test-dbus.xml

clean:
	rm service-test.h service-test.c service client *.o -f

