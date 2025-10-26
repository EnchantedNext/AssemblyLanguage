// stdlib
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// sockets
#include <arpa/inet.h>  // For inet_pton(), inet_ntop()
#include <netinet/in.h> // For sockaddr_in and constants like INADDR_ANY
#include <string.h>     // For memset() or memcpy()
#include <sys/socket.h> // For socket(), bind(), connect(), accept(), etc.
#include <sys/types.h> // For data types like pid_t, size_t (sometimes optional)
#include <unistd.h>    // For close()

// threads
#include <threads.h>

#define PORT 5665
#define HOST "0.0.0.0"
#define EXIT_FAIL -127
#define EXIT_SUCCESS 0

// create sock -> bind sock -> listen -> accept -> serve in thread

typedef struct {
  int port;
  char *host;
} sock_thrd_args_t;

int handle_client(void *arg) {
  sock_thrd_args_t *args = (sock_thrd_args_t *)arg;
  printf("Handling client %s:%i...\n", args->host, args->port);
  sleep(5);
  fflush(stdout);
  free(args->host);
  printf("Succeeded handling client!\n");
  return 0;
}

int main(void) {

  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  unsigned int addr_size = sizeof(addr);
  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  addr.sin_addr.s_addr = INADDR_ANY;
  int sock_desc;
  sock_desc = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_desc <= 0) {
    printf("Error creating socket!\n");
    exit(EXIT_FAIL);
  }

  if (bind(sock_desc, (struct sockaddr *)&addr, addr_size) < 0) {
    printf("Failed to bind socket!\n");
    close(sock_desc);
    exit(EXIT_FAIL);
  }
  printf("Socket successfully binded to %s:%i\n", HOST, PORT);
  listen(sock_desc, 5);
  while (true) {
    int client_fd = accept(sock_desc, (struct sockaddr *)&addr, &addr_size);
    if (client_fd < 0) {
      printf("Failed to accept connection!");
      continue;
    }
    char host[INET_ADDRSTRLEN];
    int port = ntohs(addr.sin_port);
    inet_ntop(AF_INET, &addr.sin_addr, host, INET_ADDRSTRLEN);
    thrd_t thread;
    sock_thrd_args_t args;
    args.host = strdup(host);
    args.port = port;
    if (thrd_create(&thread, handle_client, &args)) {
      printf("Failed to create thread!");
      exit(EXIT_FAIL);
    }
    thrd_detach(thread);
  }
  printf("Closing socket...");
  close(sock_desc);
  return EXIT_SUCCESS;
};
