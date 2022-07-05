#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#define MAXLINE     1000
#define NAME_LEN    20
struct Emoji
{
    char word[20];
    char expression[MAXLINE + 1];
};
char* EXIT_STRING = "exit";
// ���� ���� �� ���� ����, ������ ���ϸ���
int tcp_connect(int af, char* servip, unsigned short port);
void errquit(char* mesg) { perror(mesg); exit(1); }
void changename();
void menu();
void menuoptions();
char emoticon(char* buffer);
char badwords(char* buffer);
char bufname[NAME_LEN];   // �̸�
char nameTemp[100];
char bufmsg[MAXLINE];   // �޽����κ�
char bufall[MAXLINE + NAME_LEN];
struct tm tm;
int main(int argc, char* argv[]) {
    // char bufname[NAME_LEN];   // �̸�
    // char nameTemp[100];
    // char bufmsg[MAXLINE];   // �޽����κ�
    // char bufall[MAXLINE + NAME_LEN];
    int maxfdp1;   // �ִ� ���� ��ũ����
    int s;      // ����
    int namelen;   // �̸��� ����
    //struct tm tm;
    int yellowcnt = 0;
    fd_set read_fds;
    time_t ct;
    struct tm tm;
    if (argc != 4) {
        printf("���� : %s sever_ip  port name \n", argv[0]);
        exit(0);
    }
    s = tcp_connect(AF_INET, argv[1], atoi(argv[2]));
    if (s == -1)
        errquit("tcp_connect fail");
    puts("������ ���ӵǾ����ϴ�.");
    maxfdp1 = s + 1;
    FD_ZERO(&read_fds);
    strcpy(bufname, argv[3]);
    while (1) {
        FD_SET(0, &read_fds);
        FD_SET(s, &read_fds);
        // if(strcmp(bufmsg, "!menu")){
        //          menu();
        //          continue;
        //       }
        if (select(maxfdp1, &read_fds, NULL, NULL, NULL) < 0)
            errquit("select fail");
        if (FD_ISSET(s, &read_fds)) {
            int nbyte;
            if ((nbyte = recv(s, bufmsg, MAXLINE, 0)) > 0) {
                bufmsg[nbyte] = 0;
                //write(1, "\033[0G", 4);      //Ŀ���� X��ǥ�� 0���� �̵�
                //memset(bufmsg,0,sizeof(bufmsg));
                printf("%s\n", bufmsg);      //�޽��� ���
                fprintf(stderr, "\033[1;32m");   //���ڻ��� ������� ����
                //fprintf(stderr, "%s>", bufname);//�� �г��� ���
            }
        }
        if (FD_ISSET(0, &read_fds)) {
            if (fgets(bufmsg, MAXLINE, stdin))
            {
                if (strncmp(bufmsg, "!menu", 5) == 0) {
                    menuoptions();
                    continue;
                }
                fprintf(stderr, "\033[1;33m"); //���ڻ��� ��������� ����
                //fprintf(stderr, "\033[1A"); //Y��ǥ�� ���� ��ġ�κ��� -1��ŭ �̵�
                ct = time(NULL);   //���� �ð��� �޾ƿ�
                tm = *localtime(&ct);
                emoticon(bufmsg);
                memset(bufall, 0, sizeof(bufall));
                if (badwords(bufmsg) == 1)
                {
                    yellowcnt++;
                    //printf("test4 : %s",bufmsg);
                    if (yellowcnt < 4)
                    {
                        strcpy(bufmsg, "�弳������� �����ڿ� ���� �޽����� �����Ǿ����ϴ�.\0");
                    }
                    else
                    {
                        strcpy(bufmsg, "�弳 �ݺ� ������� ����Ǿ����ϴ�.\0");
                        sprintf(bufall, "[%02d:%02d:%02d]%s>%s", tm.tm_hour, tm.tm_min, tm.tm_sec, argv[3], bufmsg);//�޽����� ����ð� �߰�
                        send(s, bufall, strlen(bufall), 0);
                        //printf("server : %s",bufmsg);
                        close(s);
                        exit(0);
                    }
                }
                sprintf(bufall, "[%02d:%02d:%02d]%s>%s", tm.tm_hour, tm.tm_min, tm.tm_sec, argv[3], bufmsg);//�޽����� ����ð� �߰�
                if (send(s, bufall, strlen(bufall), 0) < 0)
                    puts("Error : Write error on socket.");
                strcpy(argv[3], bufname);
                if (strstr(bufmsg, EXIT_STRING) != NULL) {
                    puts("Good bye.");
                    close(s);
                    exit(0);
                }
            }
        }
    } // end of while
}
void menuoptions()
{
    int select;
    printf("\n\t *** menu mode ***\n");
    printf("\t1. change name\n");
    printf("\t2. clear\n\n");
    printf("\tthe other key is cancel");
    printf("\n\t *****************");
    printf("\n\t>> ");
    scanf("%d", &select);
    getchar();

    switch (select)
    {
    case 1:
        changename();
        break;
    case 2:
        menu();
        break;
    default:
        printf("\t cancel.");
        break;
    }
}
void changename() {

    char nameTemp[100];
    printf("\n\tINPUT NEW NAME ____ : ");
    scanf("%s", nameTemp);
    // bufname �� nameTemp ���� �ֱ�
   // strcmp(bufmsg,"q\n");
   // break;
    strcpy(bufname, nameTemp);
    printf("\n\tComplete.\n\n");
}
void menu()
{
    system("clear");
    printf(" **** CLEAR CHATTING ROOM ****\n");
    // printf(" server port : %s \n", serv_port);
    // printf(" client IP   : %s \n", clnt_ip);
    // printf(" chat name   : %s \n", name);
    // printf(" server time : %s \n", serv_time);
    printf(" ************* menu ***************\n");
    printf(" if you want to select menu -> !menu\n");
    printf(" 1. change name\n");
    printf(" 2. clear/update\n");
    printf(" **********************************\n");
    printf(" Exit -> q & Q\n\n");
}
char emoticon(char* buffer)
{
    //    struct Emoji emojies[4];
    //    strcpy(emojies[0].word, "sad");
    //    strcpy(emojies[0].expression, "TT");
    //    strcpy(emojies[1].word, "happy");
    //    strcpy(emojies[1].expression, "^^");
    //    strcpy(emojies[2].word, "smile");
    //    strcpy(emojies[2].expression, "^m^\0");
    //    strcpy(emojies[3].word, "good");
    //    strcpy(emojies[3].expression, "\n----------------------------\n|                          |\n|        GOOD JOB !!       |\n|                          |\n----------------------------");



    struct Emoji emojies[5];
    strcpy(emojies[0].word, "sad");
    strcpy(emojies[0].expression, "TT");
    strcpy(emojies[1].word, "happy");
    strcpy(emojies[1].expression, "\n?????????????? \n?????????????? \n??????????????\n?????????????\n");
    strcpy(emojies[2].word, "smile");
    strcpy(emojies[2].expression, "? �� ���� ? ??? ?���� �� ?\0");
    strcpy(emojies[3].word, "good");
    strcpy(emojies[3].expression, "\n�ڦ���\n ������\n ������\n ������\n ������");
    strcpy(emojies[4].word, "love");
    strcpy(emojies[4].expression, "\n??\n?????????\n?????????\n?????????\n");

    //printf("buffer : %s\n",buffer);
    for (int i = 0; i < 5; i++)
    {
        //printf("%s\n",emojies[i].word);
        if (strncmp(buffer, emojies[i].word, strlen(emojies[i].word)) == 0)
        {
            //   printf(" before : %s\n",buffer);
            strcpy(buffer, emojies[i].expression);
            buffer[strlen(emojies[i].expression)] = 0;
            //puts("Good bye.");
            // printf(" after : %s\n",buffer);
        }
    }
    return *buffer;
}
//�弳ī����
char badwords(char* buffer)
{
    struct Emoji badwords[4];
    int isFwords = 0;
    strcpy(badwords[0].word, "�ٺ�");
    strcpy(badwords[0].expression, "��*");
    strcpy(badwords[1].word, "��û��");
    strcpy(badwords[1].expression, "��*��");
    strcpy(badwords[2].word, "���۳�");
    strcpy(badwords[2].expression, "��*��");
    strcpy(badwords[3].word, "fuck");
    strcpy(badwords[3].expression, "f**k");
    for (int i = 0; i < 4; i++)
    {
        //printf("test1 : %ld, %s",strlen(buffer),buffer);
        if (strlen(buffer) >= strlen(badwords[i].word))
            for (int j = 0; j <= (strlen(buffer) - strlen(badwords[i].word)); j++)
            {
                //printf("test2 : %s",badwords[i].word);
                if (strncmp(buffer + j, badwords[i].word, strlen(badwords[i].word)) == 0)
                {
                    //strncpy(buffer+j,badwords[i].expression,strlen(badwords[i].word));
                    //printf("test3 : %s",badwords[i].word);
                    isFwords = 1;
                }
            }
    }
    return isFwords;
}
//     for (int i=0; i<20; i++)
//    {
//       if (strcmp(buffer,badwords[i].word)==0)
//       {
//           isFwords= 1;
//        }
//     }
int tcp_connect(int af, char* servip, unsigned short port) {
    struct sockaddr_in servaddr;
    int  s;
    // ���� ����
    if ((s = socket(af, SOCK_STREAM, 0)) < 0)
        return -1;
    // ä�� ������ �����ּ� ����ü servaddr �ʱ�ȭ
    bzero((char*)&servaddr, sizeof(servaddr));
    servaddr.sin_family = af;
    inet_pton(AF_INET, servip, &servaddr.sin_addr);
    servaddr.sin_port = htons(port);
    // �����û
    if (connect(s, (struct sockaddr*)&servaddr, sizeof(servaddr))
        < 0)
        return -1;
    return s;
}