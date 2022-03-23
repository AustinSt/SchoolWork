#include <stdio.h>
#include <openacc.h>

int main(int argc, char *argv[])
{
    acc_device_t dev = acc_get_device_type();
    int num = acc_get_device_num(dev);
    printf("%d\n", num);
    return 0;
}