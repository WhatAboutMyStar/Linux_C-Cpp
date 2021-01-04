#include<stdio.h>
#include<arpa/inet.h>

int main()
{
    char ip_str[] = "127.0.0.1";
    unsigned int ip_uint = 0;
    unsigned char* ip_p = NULL;

    inet_pton(AF_INET, ip_str, &ip_uint);

    printf("ip_uint = %d\n", ip_uint);

    ip_p = (unsigned char*)&ip_uint;
    printf("ip_uint = %d.%d.%d.%d\n",*ip_p, *(ip_p + 1), *(ip_p + 2), *(ip_p + 3));
    return 0;
}
//output:
// ip_uint = 16777343
// ip_uint = 127.0.0.1
