#include <cstdlib>
#include <iostream>

#include <netdb.h>
#include <unistd.h>

using namespace std;

int do_client(char *serverName);

int main(int argc, char *argv[])
{
  if (argc!=2)
    {
      cerr << "USAGE: " << argv[0] << " <tod-server>" << endl;
      return 1;
    }

  return do_client(argv[1]);
}

int do_client(char *server)
{
  //cout << "Connecting to " << server << endl;

  // variable to hold return values from various network calls
  int rval =0;

  // holds IP information about our server.
  struct hostent *serverEntry;

  // holds socket information for our connection with server
  // technically a "socket", which holds IP (IP layer) and port (TCP
  // info) for both server (foreign end) and client (local end)
  struct sockaddr_in serverInfo;

  // convert server "name" to "numeric" IP address
  serverEntry = gethostbyname(server);

  if (!serverEntry)
    {
      cerr << "gethostbyname failed for: " << server << endl;
      return 1;
    }

  // create an actual network socket
  //   AF_INET --> IPv4
  //   SOCK_STREAM --> TCP
  //   0 --> use default "flags"
  int mySock = socket(AF_INET, SOCK_STREAM, 0);

  serverInfo.sin_family = AF_INET;
  serverInfo.sin_addr = * ( (struct in_addr *)serverEntry -> h_addr_list[0] );
  serverInfo.sin_port = htons(13);

  rval = connect(mySock, (struct sockaddr *) &serverInfo, sizeof(serverInfo) );

  if (rval<0)
    {
      cerr << "connect() failed." << endl;
      return 1;
    }

  // if we get here we are connected to the server !!!!

  int n=0; // how many bytes did we just read?
  char recvln[81];  // actual bytes (caharacters) read

  while (  (n=read(mySock, recvln, 80)) > 0 )
    {
      recvln[n] = '\0'; // null terminate returned "string"
      cout << recvln; 
    }

  cout << endl;

  // end network connection 
  close (mySock);
  
  return 0;
}
