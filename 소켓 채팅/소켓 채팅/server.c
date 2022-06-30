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
int max_sd;                 // �ִ� ���Ϲ�ȣ +1
int num_user = 0;         // ä�� ������ ��
int num_chat = 0;         // ���ݱ��� ���� ��ȭ�� ��
int client_socket[30];      // ä�ÿ� ������ ���Ϲ�ȣ ���
int master_socket;         // ������ ���� ����
void addClient(int s, struct sockaddr_in* newcliaddr);// ���ο� ä�� ������ ó��
void removeClient(int s);   // ä�� Ż�� ó�� �Լ�
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

            // Ŭ���̾�Ʈ���� ù ��° �λ� ������
            if (write(new_socket, message, strlen(message)) != strlen(message))
            {
                perror("send");
            }
            num_user++;
            puts("Welcome message sent successfully");

            // ���ο� ������ ��� �ִ� Ŭ���̾�Ʈ ���� �迭�� �ֱ�
            for (int i = 0; i < max_clients; i++)
            {
                if (client_socket[i] == 0)
                {
                    client_socket[i] = new_socket;
                    printf("Adding to list of sockets as %d\n", i);
                    ct = time(NULL);         //���� �ð��� �޾ƿ�
                    tm = *localtime(&ct);
                    write(1, "\033[0G", 4);      //Ŀ���� X��ǥ�� 0���� �̵�
                    printf("[%02d:%02d:%02d]", tm.tm_hour, tm.tm_min, tm.tm_sec);
                    fprintf(stderr, "\033[33m");//���ڻ��� ��������� ����
                    printf("����� 1�� �߰�. ���� ������ �� = %d\n", num_user);
                    fprintf(stderr, "\033[32m");//���ڻ��� ������� ����
                    fprintf(stderr, "server>"); //Ŀ�� ���
                    break;
                }
            }
        }

        // Ŭ���̾�Ʈ�� ���� �޽����� ��� Ŭ���̾�Ʈ���� ���
        for (i = 0; i < num_user; i++)
        {
            sd = client_socket[i];
            if (FD_ISSET(sd, &readfds))
            {
                num_chat++;            //�� ��ȭ �� ����
                if ((valread = read(client_socket[i], buffer, BUFLEN)) == 0)
                {
                    // ������ �� �ƹ� �͵� ���ٸ� ���� ���� ��ȣ�� �� ���̹Ƿ�
                    getpeername(sd, (sa_t*)&address, (socklen_t*)&addrlen); //����ְ� ���
                    printf("Host disconnected, ip %s, port %d \n",
                        inet_ntoa(address.sin_addr), ntohs(address.sin_port));   //�����ش�
                        // ���� �ݰ� �ش� Ŭ���̾�Ʈ ���� �迭 �� �ʱ�ȭ
                    close(sd);
                    client_socket[i] = 0;
                }
                else
                {
                    emoticon(buffer);
                    for (j = 0; j < num_user; j++) {
                        send(client_socket[j], buffer, strlen(buffer), 0);
                    }
                    printf("\033[0G");      //Ŀ���� X��ǥ�� 0���� �̵�
                    fprintf(stderr, "\033[97m");//���ڻ��� ������� ����
                    printf("%s", buffer);         //�޽��� ���
                    fprintf(stderr, "\033[32m");//���ڻ��� ������� ����
                    fprintf(stderr, "server>"); //Ŀ�� ���
                }
            }
        }
    }  // end of while
    return 0;
}
// ä�� Ż�� ó��
void removeClient(int s)
{
    close(client_socket[s]);
    if (s != num_user - 1) { //����� ����Ʈ ��迭
        client_socket[s] = client_socket[num_user - 1];
    }
    num_user--; //���� �� ����
    ct = time(NULL);         //���� �ð��� �޾ƿ�
    tm = *localtime(&ct);
    write(1, "\033[0G", 4);      //Ŀ���� X��ǥ�� 0���� �̵�
    fprintf(stderr, "\033[33m");//���ڻ��� ��������� ����
    printf("[%02d:%02d:%02d]", tm.tm_hour, tm.tm_min, tm.tm_sec);
    printf("ä�� ������ 1�� Ż��. ���� ������ �� = %d\n", num_user);
    fprintf(stderr, "\033[32m");//���ڻ��� ������� ����
    fprintf(stderr, "server>"); //Ŀ�� ���
}
//�̸�Ƽ�� ��ȯ
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
