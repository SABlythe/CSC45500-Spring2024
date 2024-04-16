#include <cstdlib>
#include <iostream>
#include <string>


#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>

using namespace std;

#define MAX_WAITING 25

int do_server(unsigned int port);

//void do_work(unsigned int with_sock, struct sockaddr_in *fromcli);
void* do_work(void *);

struct do_work_struct
{
  unsigned int with_sock;
  struct sockaddr_in *fromcli;
};

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

  rval = listen (listen_sock, MAX_WAITING);

  if (rval!=0)
    {
      cerr << "listen() failed" << endl;
      return 1;
    }

  while(true)
    {
      //accept icoming client
      int accepted_socket;     // socket for actual connexted client
      struct sockaddr_in from; // holds client address data
      unsigned int from_len;   // bytes in from

      from_len = sizeof(from);

      accepted_socket = accept(listen_sock,
			       (struct sockaddr*) &from,
			       &from_len);
      
      // process incoming client

      struct do_work_struct *params = new struct do_work_struct;
      params -> with_sock = accepted_socket;
      params -> fromcli = &from;
      
      pthread_create(new pthread_t, NULL, do_work, params );
    }
  
  return 0;
}


void* do_work(void *generic_ptr)
{
  struct do_work_struct *actual_ptr = (struct do_work_struct *) generic_ptr;

  unsigned int with_sock;
  struct sockaddr_in *fromcli;
  with_sock = actual_ptr -> with_sock;
  fromcli = actual_ptr -> fromcli; 

  string buffer; // the result we are trying to send back to client
  buffer = "Your IP is ";
  buffer += inet_ntoa(fromcli->sin_addr);
  buffer += "\n";

  char *cbuff = (char *) buffer.c_str(); // network code needs array of bytes (chars)

  int needed = buffer.length();

  while(needed > 0)
    {
      int n = write(with_sock, cbuff, needed);
      needed -= n;
      cbuff += n;
    }

  cout << "Processed a connection from " << inet_ntoa(fromcli->sin_addr) << endl;

  // close the connected (accepted) socket from server side
  close(with_sock);

  return nullptr;
}
