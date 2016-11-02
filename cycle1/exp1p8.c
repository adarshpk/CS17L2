// CS 17L2 NETWORKS AND OPERATING SYSTEMS LABORATORY
// Cycle 1 : Exp 1 - Program No: (viii): Familiarization of socket() system call.
// ADARSH P.K. CSU13203
//
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>

int main(int argc, char* argv[])
{
  struct sockaddr_un name;
  int sock;
  char *filename = argv[1];
  sock = socket (AF_LOCAL, SOCK_DGRAM, 0);
  name.sun_family = AF_LOCAL;
  strcpy (name.sun_path, filename);
  bind (sock, (struct sockaddr *) &name, sizeof(struct sockaddr_un));
  return 0;
}