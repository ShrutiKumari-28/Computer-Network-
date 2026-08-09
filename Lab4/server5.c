# include < stdio .h >
# include < stdlib .h >
# include < string .h >
# include < unistd .h >
# include < arpa / inet .h >
# define PORT 8081
# define BUFFER_SIZE 1024
int count_words ( char * str ) {
int count = 0 in_word = 0;
while (*str)
{
    if (!isspace((unsigned char)*str))
    {
        if(!in_word)
        {
            count++;
            in_word=1;
        }
    }
    else
    {
        in_word =0;
    }
    str++;
}
return count ;
}
int count_vowels ( char * str ) {
int count = 0;
while(*str)
{
    char ch = tolower((unsigned char)*str);
    if (ch=='a' || ch=='e'|| ch=='i'|| ch=='o'|| ch=='u')
    {
        count++;
    }
    str++;
}

return count ;
}
int main () {
int server_fd , new_socket ;
struct sockaddr_in address ;
char buffer [ BUFFER_SIZE ];
// Create Socket 
server_fd=socket(AF_INET,SOCK_STREAM, 0);
if (server_fd < 0)
{
    perror("Socket failed");
    exit(EXIT_FAILURE);
}
// Initialize the value 
memset 
// Write bind syntax here -----
// Write Listen Syntax here ----
// Write Accept function call --
while (1) {0
memset ( buffer , 0 , BUFFER_SIZE ) ;
int valread = read ( new_socket , buffer ,
BUFFER_SIZE ) ;
if ( valread <= 0) break ;
buffer [ strcspn ( buffer , " \ n " ) ] = 0;
if ( strcmp ( buffer , " bye " ) == 0) break ;
char command [20] , text [ BUFFER_SIZE ];
sscanf ( buffer , " %[^|]|%[^\ n ] " , command , text ) ;
if ( strcmp ( command , " ANALYZE " ) == 0) {
int chars = strlen ( text ) ;
int words = count_words ( text ) ;
int vowels = count_vowels ( text ) ;
char response [ BUFFER_SIZE ];
sprintf ( response , " Chars =% d , ␣ Words =% d , ␣
Vowels =% d " , chars , words , vowels ) ;
send ( new_socket , response , strlen ( response ) ,
0) ;
} else {
char * msg = " Invalid ␣ Command " ;
send ( new_socket , msg , strlen ( msg ) , 0) ;
}
}

close ( new_socket ) ;
close ( server_fd ) ;
return 0;
}