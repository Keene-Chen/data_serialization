/**
 * @file    : 03_test_read.c
 * @author  : KeeneChen
 * @date    : 2023.10.07-12:23:51
 * @details : 03_test_read
 */

#include "yyjson.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/* 从字符串中读取json */
static int read_json_str(void)
{
    const char *json_str = "{\"dht11\":{\"temperature\":35.6,\"humidity\":78.2,\"status\":true}}";
    yyjson_doc *doc      = yyjson_read(json_str, strlen(json_str), 0);
    if (doc == NULL) {
        yyjson_doc_free(doc);
        return -1;
    }

    yyjson_val *root   = yyjson_doc_get_root(doc);
    yyjson_val *device = yyjson_obj_getn(root, "dht11", strlen("dht11"));
    printf("%ld\n", yyjson_obj_size(device));
    yyjson_val *temp = yyjson_obj_get(device, "temperature");
    printf("%.2f\n", yyjson_get_real(temp));

    /**
     * 如果对象键的顺序在编译时已知，
     * 您可以使用此方法来避免搜索整个对象。
     * 例如 { "x":1, "y":2, "z":3 }
     */
    yyjson_obj_iter iter = yyjson_obj_iter_with(device);
    yyjson_val *humi     = yyjson_obj_iter_get(&iter, "humidity");
    printf("%.2f\n", yyjson_get_real(humi));

    /* 使用迭代器遍历对象 */
    yyjson_val *key, *val;
    yyjson_obj_iter iter1 = yyjson_obj_iter_with(device);
    while ((key = yyjson_obj_iter_next(&iter1))) {
        val = yyjson_obj_iter_get_val(key);
        if (yyjson_is_real(val))
            printf("%s:%.2f\n", yyjson_get_str(key), yyjson_get_real(val));
        else if (yyjson_is_bool(val))
            printf("%s:%d\n", yyjson_get_str(key), yyjson_get_bool(val));
    }

    /* 使用foreach宏遍历对象 */
    size_t idx, max;
    yyjson_val *key1, *val1;
    yyjson_obj_foreach(device, idx, max, key1, val1)
    {
        if (yyjson_is_real(val1))
            printf("%s:%.2f\n", yyjson_get_str(key1), yyjson_get_real(val1));
        else if (yyjson_is_bool(val1))
            printf("%s:%d\n", yyjson_get_str(key1), yyjson_get_bool(val1));
    }

    yyjson_doc_free(doc);
    return 0;
}

static int read_json_file(void)
{
    const char *file_path = "/home/keenechen/Code_Test/data_serialization/res/yyjson.json";
    yyjson_read_err err;
    yyjson_doc *doc = NULL;

    doc = yyjson_read_file(file_path, YYJSON_READ_ALLOW_COMMENTS | YYJSON_READ_ALLOW_INF_AND_NAN,
                           NULL, &err);
    if (doc) {
        printf("{\n");
        yyjson_val *root     = yyjson_doc_get_root(doc);
        yyjson_obj_iter iter = yyjson_obj_iter_with(root);
        yyjson_val *key, *val;
        while ((key = yyjson_obj_iter_next(&iter))) { // 第一层为根

            val = yyjson_obj_iter_get_val(key);
            printf("  \"%s\": [\n", yyjson_get_str(key));
            printf("    {\n");
            yyjson_arr_iter iter1 = yyjson_arr_iter_with(val);
            yyjson_val *arr_val;
            while ((arr_val = yyjson_arr_iter_next(&iter1))) { // 第二层为数组

                yyjson_obj_iter iter2 = yyjson_obj_iter_with(arr_val);
                yyjson_val *key1, *val1;
                while ((key1 = yyjson_obj_iter_next(&iter2))) { // 第三层为对象

                    val1 = yyjson_obj_iter_get_val(key1);
                    printf("      \"%s\": ", yyjson_get_str(key1));
                    if (yyjson_is_str(val1))
                        printf("%s\n", yyjson_get_str(val1));
                    else if (yyjson_is_real(val1))
                        printf("%.2f\n", yyjson_get_real(val1));
                    else if (yyjson_is_num(val1))
                        printf("%d\n", yyjson_get_int(val1));
                    else if (yyjson_is_bool(val1))
                        printf("%s\n", yyjson_get_type_desc(val1));
                    else if (yyjson_is_obj(val1)) {
                        printf("{\n");
                        yyjson_obj_iter iter3 = yyjson_obj_iter_with(val1);
                        yyjson_val *key2, *val2;
                        while ((key2 = yyjson_obj_iter_next(&iter3))) {
                            val2 = yyjson_obj_iter_get_val(key2);
                            printf("        \"%s\": ", yyjson_get_str(key2));
                            if (yyjson_is_str(val2))
                                printf("%s\n", yyjson_get_str(val2));
                            else if (yyjson_is_real(val2))
                                printf("%.2f\n", yyjson_get_real(val2));
                        }
                        printf("      }\n");
                    }
                    else if (yyjson_is_arr(val1)) {
                        printf("[\n");
                        yyjson_arr_iter iter4 = yyjson_arr_iter_with(val1);
                        yyjson_val *arr_val1;
                        while ((arr_val1 = yyjson_arr_iter_next(&iter4))) {
                            if (yyjson_is_str(arr_val1))
                                printf("        \"%s\"\n", yyjson_get_str(arr_val1));
                            else if (yyjson_is_num(arr_val1))
                                printf("        %d\n", yyjson_get_int(arr_val1));
                        }
                        printf("      ]\n");
                    }
                }
                printf("    }\n");
            }
            printf("  ]\n");
        }
        printf("}\n");
    }
    else {
        printf("read error (%u): %s at position: %ld\n", err.code, err.msg, err.pos);
    }

    yyjson_doc_free(doc);
    return 0;
}

int main(void)
{
    read_json_str();
    read_json_file();

    return 0;
}