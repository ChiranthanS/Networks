#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {
  if (argc != 3) {
    printf("Invalid arguments - %s <host> <port>", argv[0]);
    return -1;
  }
  char* host = argv[1];
  long port = atoi(argv[2]);
  char buffer[70]; 

  sprintf(buffer, "%ld", port);

  int res_code;
  struct addrinfo hints, *res, *result;

  
  hints.ai_family = PF_UNSPEC;
  hints.ai_protocol = IPPROTO_TCP;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  char addrstring[INET6_ADDRSTRLEN]; 
  void* raw_address = malloc(sizeof(800));

  res_code = getaddrinfo(host, buffer, &hints, &result); 
  if (res_code == 0) {
    res = result;

    while (res) {
      int ip_version = (res->ai_family == AF_INET) ? 4 : 6;

      if (res->ai_family == AF_INET6) 
      {
        raw_address = &((struct sockaddr_in6*)res->ai_addr)->sin6_addr;
      } else {
        raw_address = &((struct sockaddr_in*)res->ai_addr)->sin_addr;
      }

      
      inet_ntop(res->ai_family, raw_address, addrstring, 200);
      printf("IPv%d %s \n", ip_version, addrstring);
      res = res->ai_next;
    }

    freeaddrinfo(result); 
  }
  return 0;
}
