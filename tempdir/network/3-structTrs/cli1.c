#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    struct sockaddr_in s_addr;
    int sfd;
    char rbuf[20] = "";
    //char sbuf[20] = "";
    int s_len= sizeof(s_addr);
    int num_buf = 0x12345;
    typedef struct _ST
    {
	char *c[2];
	//char c2[4];
	int n;
    }ST;


    //set socket
    sfd = socket(AF_INET, SOCK_STREAM, 0);

    //set addr struct
    bzero(&s_addr, s_len);

    s_addr.sin_family = AF_INET;
    s_addr.sin_port=htons(6666);
    inet_pton(AF_INET, "127.0.0.1", &s_addr.sin_addr);

    //connect to server
    connect(sfd, (struct sockaddr *)&s_addr, s_len);

    //communication
    //gets(sbuf);

    //sprintf(sbuf, "%x", num_buf);
    ST st;
    st.c[0] = (char *)malloc(5);
    st.c[1] = (char *)malloc(5);

    strcpy(st.c[0],"c0");
    strcpy(st.c[1],"c1");
    printf("%s\n",st.c[0]);
    printf("%s\n",st.c[1]);
    //strcpy(st.c2,"c2");
    st.n = 1;
    
    send(sfd, &st,sizeof(ST), 0);

    recv(sfd, rbuf, sizeof(rbuf), 0);
    printf("get %s from server\n", rbuf);
    return 0;

}

