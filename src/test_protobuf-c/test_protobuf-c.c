#include "student.pb-c.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    Student pack_stu    = { 0 };
    uint8_t buffer[512] = { 0 };
    Student* unpack_stu = NULL;
    size_t len          = 0;

    student__init(&pack_stu);

    /* 组包 */
    pack_stu.name    = "zhangsan";
    pack_stu.num     = 88;
    pack_stu.c_score = 90;
    len              = student__pack(&pack_stu, buffer);
    printf("len = %ld\n", len);

    /* 解包 */
    unpack_stu = student__unpack(NULL, len, buffer);
    printf("unpack_stu.name = %s\n", unpack_stu->name);
    printf("unpack_stu.num = %d\n", unpack_stu->num);
    printf("unpack_stu.c_score = %d\n", unpack_stu->c_score);

    student__free_unpacked(unpack_stu, NULL);
    return 0;
}
