#include <cstdlib>
#include <iostream>
#include <string>


#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

#define MAX_WAITING 25

int do_server(unsigned int port);

void do_work(unsigned int with_sock, struct sockaddr_in *fromcli);


int main(int argc, char *argv[])
{
  if (argc!=2)
    {
      cerr << "USAGE: " << argv[0] << " <port number>" << endl;
      return 1;
    }

  return do_server( stoi(argv[1]) ) ; 
}

int do_server(unsigned int port)
{
  int listen_sock;

  // local address in the socket
  struct sockaddr_in local_addr;

  listen_sock = socket(AF_INET, SOCK_STREAM, 0);

  if (listen_sock<0)
    {
      cerr << "could not create socket" << endl;
      return 1;
    }

  local_addr.sin_family = AF_INET;  // use IPv4
  local_addr.sin_addr.s_addr = INADDR_ANY; // use "wildcard" IP address
  local_addr.sin_port = htons(port);

  int rval = bind(listen_sock,  (struct sockaddr *) &local_addr, sizeof(local_addr) );
  if (rval != 0)
    {
      cerr << "Binding failed - possible causes include:" << endl
	   << "   * invalid port number (access denied or already in use?)" << endl
	   << "   * invalid local address (did you use the wildcard?)" << endl;
      return 1;
    }

  return 0;
}
