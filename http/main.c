#include <stdio.h>
#include <string.h>

void send_http(char* host, char* msg, char* resp, size_t len);

int main(int argc, char* argv[]) {
  if (argc != 4) {
    fprintf(stderr, "Invalid arguments - %s <host> <GET|POST> <path>\n", argv[0]);
    return -1;
  }
  char* host = argv[1];
  char* verb = argv[2];
  char* path = argv[3];

  char request[4096];
  char response[4096];
  
  if (strcmp(verb, "GET") == 0) {
    snprintf(request, sizeof(request), "%s %s HTTP/1.1\r\nHost: %s\r\n\r\n", verb, path, host);
  } else if (strcmp(verb, "POST") == 0) {
    //snprintf(request, sizeof(request), "POST %s HTTP/1.1\r\nHost: %s\r\nContent-Length: 0\r\n\r\n", path, host);
    snprintf(request, sizeof(request), "POST %s HTTP/1.1\r\nHost: %s\r\n\r\n\r\n", path, host);
  } else {
    fprintf(stderr, "Invalid verb\n");
    return -1;
  }

  send_http(host, request, response, sizeof(response));

  printf("%s\n", response);

  return 0;
}
