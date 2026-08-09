# include < stdio .h >
# include < stdlib .h >
# include < string .h >
# include < unistd .h >
# include < arpa / inet .h >
# define PORT 8081
# define BUFFER_SIZE 1024
int main () {
int sock ;
struct sockaddr_in serv_addr ;
char buffer [ BUFFER_SIZE ];
char input [ BUFFER_SIZE ];
// Create Socket ----
serv_addr . sin_family = AF_INET ;
serv_addr . sin_port = htons ( PORT ) ;
inet_pton ( AF_INET , " 127.0.0.1 " , & serv_addr . sin_addr )
;
connect ( sock , ( struct sockaddr *) & serv_addr , sizeof (
serv_addr ) );
-----
-----
-----
close ( sock ) ;
return 0;
}