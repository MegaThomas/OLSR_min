#include <malloc.h>
#include <sys/epoll.h>
#include <unistd.h>

#define MAX_EVENTS 2

struct epoll_event *events;
int nr_events, i, epfd;

int main(int argv, char **argc) {
    epfd = epoll_create1(0);
    if (epfd<0)
        perror("epoll_create1()");

    events = malloc(sizeof(struct epoll_event) * MAX_EVENTS);
    if (!events) {
        perror("malloc");
        return 1;
    }

    events[0].events = EPOLLIN;
    events[0].data.fd = STDIN_FILENO;
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &events[0])) {
        perror("epoll_ctl");
    }
    events[1].events = EPOLLOUT;
    events[1].data.fd = STDOUT_FILENO;
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, STDOUT_FILENO, &events[1])) {
        perror("epoll_ctl");
    }
    nr_events = epoll_wait(epfd, events, MAX_EVENTS, -1);
    if (nr_events < 0) {
        perror("epoll_wait");
        free(events);
        return 1;
    }

    for (i = 0; i < nr_events; ++i) {
        printf("event=%ld on fd=%d\n",
            events[i].events,
            events[i].data.fd);
    }
    free(events);
    if (close(epfd)) {
        perror("close");
        return 1;
    }
    return 0;
}