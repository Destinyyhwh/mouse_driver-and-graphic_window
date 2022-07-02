#define MAX_MSG         1024

typedef struct {
    int mid;
    int pid;
    void *adt;
}message;
message msg_list[MAX_MSG];