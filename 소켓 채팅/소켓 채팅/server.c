//Example code: A simple server side code,which echos back the received message.
//Handle multiple socket connections with select and fd_set on Linux
#include <stdio.h>
#include <string.h> //strlen
#include <stdlib.h>
#include <errno.h>
#include <unistd.h> //close
#include <arpa/inet.h> //close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> //FD_SET,FD_ISSET,FD_ZERO macros
// #include <strings.h>
// #include <fcntl.h>
// #include <sys/file.h>
#include <time.h>
#define TRUE 1
#define FALSE 0
#define PORT 8888
#define BUFLEN 1024
// #define MAX_SOCK 1024
typedef struct sockaddr sa_t;
struct Emoji
{
    char word[20];
    char expression[BUFLEN + 1];
};
char* START_STRING = "Connected to chat_server \n";
int max_sd;                 // 최대 소켓번호 +1
int num_user = 0;         // 채팅 참가자 수
int num_chat = 0;         // 지금까지 오간 대화의 수
int client_socket[30];      // 채팅에 참가자 소켓번호 목록
int master_socket;         // 서버의 리슨 소켓
void addClient(int s, struct sockaddr_in* newcliaddr);// 새로운 채팅 참가자 처리
void removeClient(int s);   // 채팅 탈퇴 처리 함수
void errquit(char* mesg) { perror(mesg); exit(1); }
char emoticon(char* buffer);
time_t ct;
struct tm tm;
int main(int argc, char* argv[])
{
    int optval = TRUE;
    int master_socket, addrlen, new_socket, client_socket[30],
        max_clients = 30, activity, i, j, valread, sd, nbyte;
    int max_sd;
    struct sockaddr_in address;

    char buffer[BUFLEN + 1]; //data buffer of 1K

    struct Emoji emojies[20];
    strcpy(emojies[1].word, "sad");
    strcpy(emojies[1].expression, "TT");


    //set of socket descriptors
    fd_set readfds;

    //a message
    char* message = "ECHO Daemon v1.0 \r\n";
    if (argc != 2) {
        printf("Usage: %s [PORT]\n", argv[0]);
        exit(0);
    }
    //initialise all client_socket[] to 0 so not checked
    for (i = 0; i < max_clients; i++) {
        client_socket[i] = 0;
    }
    //create a master socket
   // if ((master_socket=socket(AF_INET,SOCK_STREAM,0))==0) {
    if ((master_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    //type of socket created
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(atoi(argv[1]));
    //bind the socket to localhost port 8888
    if (bind(master_socket, (sa_t*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("Listener on port %d \n", atoi(argv[1]));
    //try to specify maximum of 3 pending connections for the master socket
    if (listen(master_socket, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    //accept the incoming connection
    addrlen = sizeof(address);
    puts("Waiting for connections ...");


    while (TRUE) {
        //clear the socket set
        FD_ZERO(&readfds);

        //add master socket to set
        FD_SET(master_socket, &readfds);
        max_sd = master_socket;
        //add child sockets to set
        for (i = 0; i < max_clients; i++)
        {
            //socket descriptor
            sd = client_socket[i];
            //if valid socket descriptor then add to read list
            if (sd > 0)
                FD_SET(sd, &readfds);
            //highest file descriptor number,need it for the select function
            if (sd > max_sd)
                max_sd = sd;
        }


        //wait for an activity on one of the sockets,timeout is NULL,
        //so wait indefinitely
        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);
        if ((activity < 0) && (errno != EINTR)) {
            printf("select error");
        }


        if (FD_ISSET(master_socket, &readfds))
        {
            // if ((new_socket=accept(master_socket,(sa_t *)&address,
            // (socklen_t *)&addrlen))<0)
            // {
            // perror("accept");
            // exit(0);
            // }
            new_socket = accept(master_socket,
                (sa_t*)&address, &addrlen);
            if (new_socket == -1) errquit("accept fail");

            printf("New connection: socket fd %d, ip %s, port %d\n",
                new_socket, inet_ntoa(address.sin_addr), ntohs(address.sin_port));

            // 클라이언트에게 첫 번째 인사 보내기
            if (write(new_socket, message, strlen(message)) != strlen(message))
            {
                perror("send");
            }
            num_user++;
            puts("Welcome message sent successfully");

            // 새로운 소켓을 비어 있는 클라이언트 관리 배열에 넣기
            for (int i = 0; i < max_clients; i++)
            {
                if (client_socket[i] == 0)
                {
                    client_socket[i] = new_socket;
                    printf("Adding to list of sockets as %d\n", i);
                    ct = time(NULL);         //현재 시간을 받아옴
                    tm = *localtime(&ct);
                    write(1, "\033[0G", 4);      //커서의 X좌표를 0으로 이동
                    printf("[%02d:%02d:%02d]", tm.tm_hour, tm.tm_min, tm.tm_sec);
                    fprintf(stderr, "\033[33m");//글자색을 노란색으로 변경
                    printf("사용자 1명 추가. 현재 참가자 수 = %d\n", num_user);
                    fprintf(stderr, "\033[32m");//글자색을 녹색으로 변경
                    fprintf(stderr, "server>"); //커서 출력
                    break;
                }
            }
        }

        // 클라이언트가 보낸 메시지를 모든 클라이언트에게 방송
        for (i = 0; i < num_user; i++)
        {
            sd = client_socket[i];
            if (FD_ISSET(sd, &readfds))
            {
                num_chat++;            //총 대화 수 증가
                if ((valread = read(client_socket[i], buffer, BUFLEN)) == 0)
                {
                    // 보내온 게 아무 것도 없다면 연결 종료 신호가 온 셈이므로
                    getpeername(sd, (sa_t*)&address, (socklen_t*)&addrlen); //상대주고 얻고
                    printf("Host disconnected, ip %s, port %d \n",
                        inet_ntoa(address.sin_addr), ntohs(address.sin_port));   //보여준다
                        // 소켓 닫고 해당 클라이언트 관리 배열 값 초기화
                    close(sd);
                    client_socket[i] = 0;
                }
                else
                {
                    emoticon(buffer);
                    for (j = 0; j < num_user; j++) {
                        send(client_socket[j], buffer, strlen(buffer), 0);
                    }
                    printf("\033[0G");      //커서의 X좌표를 0으로 이동
                    fprintf(stderr, "\033[97m");//글자색을 흰색으로 변경
                    printf("%s", buffer);         //메시지 출력
                    fprintf(stderr, "\033[32m");//글자색을 녹색으로 변경
                    fprintf(stderr, "server>"); //커서 출력
                }
            }
        }
    }  // end of while
    return 0;
}
// 채팅 탈퇴 처리
void removeClient(int s)
{
    close(client_socket[s]);
    if (s != num_user - 1) { //저장된 리스트 재배열
        client_socket[s] = client_socket[num_user - 1];
    }
    num_user--; //유저 수 감소
    ct = time(NULL);         //현재 시간을 받아옴
    tm = *localtime(&ct);
    write(1, "\033[0G", 4);      //커서의 X좌표를 0으로 이동
    fprintf(stderr, "\033[33m");//글자색을 노란색으로 변경
    printf("[%02d:%02d:%02d]", tm.tm_hour, tm.tm_min, tm.tm_sec);
    printf("채팅 참가자 1명 탈퇴. 현재 참가자 수 = %d\n", num_user);
    fprintf(stderr, "\033[32m");//글자색을 녹색으로 변경
    fprintf(stderr, "server>"); //커서 출력
}
//이모티콘 변환
char emoticon(char* buffer)
{
    struct Emoji emojies[20];
    strcpy(emojies[0].word, "sad");
    strcpy(emojies[0].expression, "TT");
    strcpy(emojies[1].word, "happy");
    strcpy(emojies[1].expression, "^^");
    strcpy(emojies[2].word, "smile");
    strcpy(emojies[2].expression, "^m^");
    strcpy(emojies[3].word, "good");
    strcpy(emojies[3].expression, "----------------------------\n|                          |\n|        GOOD JOB !!       |\n|                          |\n----------------------------");

    for (int i = 0; i < 20; i++)
    {

        if (strcmp(buffer, emojies[i].word) == 0)
        {
            char tmp;
            char* p1, * p2;

            p1 = buffer;
            p2 = emojies[i].word;

            tmp = *p1;
            *p1 = *p2;
            *p2 = tmp;

            //strcpy(buffer,emojies[i].expression);
        }
    }
    return *buffer;
}
