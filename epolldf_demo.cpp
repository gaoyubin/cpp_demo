#include <sys/epoll.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
void DoWrite(int epollfd)
{
    int fd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if (fd < 0)
    {
        perror("socket ");
        exit(-1);
    }
    struct sockaddr_un peer_addr;
    memset(&peer_addr, 0, sizeof(peer_addr));
    peer_addr.sun_family = AF_LOCAL;
    const char *ipc_path =  "/home/longzhiri/my_code/nettest/localnettest.ipc";
    strncpy(peer_addr.sun_path, ipc_path, sizeof(peer_addr.sun_path)-1);
    if (connect(fd, (struct sockaddr *)&peer_addr,  sizeof(struct sockaddr_un))<0)
    {
        perror("connect ");
        exit(-1);
    }
    struct epoll_event ev, events[10];
    ev.events = EPOLLOUT;
    ev.data.fd = fd;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev) < 0)
    {
        perror("epoll_ctl");
        exit(-1);
    }

    sleep(10);
    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &ev);
    printf("child process exit\n");
 }

 int main(int argc, char *argv[])
 {
     int epollfd = epoll_create(10);
     if (epollfd < 0) {
         perror("epoll_create");
         return -1;
     }

     struct epoll_event events[10];
     int pid = fork();
     if (pid < 0)
     {
         perror("fork");
         return -1;
     }
     else if (pid > 0) 
     {
         for (;;)
         {
             int nfds = epoll_wait(epollfd, events, 10, -1);
             if (nfds < 0)
             {
                 perror("epoll_wait 1");
                 return -1;
             }
             printf("wake up +++\n");
         }
     }
     else 
     {
         DoWrite(epollfd);
     }
     return 0;
 }