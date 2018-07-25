.PHONY:all
all:http_server

http_server:httpd.c
	gcc -o $@ $^ -lpthread

.PHONY:clean
clean:
	rm http_server
