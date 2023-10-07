/**
 * @file    : 04_test_write.c
 * @author  : KeeneChen
 * @date    : 2023.10.07-21:51:04
 * @details : 04_test_write
 */

#include "yyjson.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int write_json_str()
{
    // Create a mutable doc
    yyjson_mut_doc *doc = yyjson_mut_doc_new(NULL);
    if (doc == NULL) {
        yyjson_mut_doc_free(doc);
        return -1;
    }
    yyjson_mut_val *root = yyjson_mut_obj(doc);
    yyjson_mut_doc_set_root(doc, root);

    // Set root["name"] and root["star"]
    yyjson_mut_obj_add_str(doc, root, "name", "Mash");
    yyjson_mut_obj_add_int(doc, root, "star", 4);

    // Set root["hits"] with an array
    int hits_arr[]       = { 2, 2, 1, 3 };
    yyjson_mut_val *hits = yyjson_mut_arr_with_sint32(doc, hits_arr, 4);
    yyjson_mut_obj_add_val(doc, root, "hits", hits);

    // To string, minified
    const char *json = yyjson_mut_write(doc, YYJSON_WRITE_PRETTY, NULL);
    if (json) {
        printf("json: %s\n", json);
        free((void *)json);
    }

    // Free the doc
    yyjson_mut_doc_free(doc);
    return 0;
}

static int write_json_file(void)
{
    const char *file_path  = "/home/keenechen/Code_Test/data_serialization/res/yyjson.json";
    const char *file_path1 = "/home/keenechen/Code_Test/data_serialization/res/yyjson_01.json";
    yyjson_read_err read_err;
    yyjson_doc *doc = yyjson_read_file(file_path, 0, NULL, &read_err);
    if (doc == NULL) {
        yyjson_doc_free(doc);
        return read_err.code;
    }

    yyjson_val *arr = yyjson_obj_get(doc->root, "student");
    yyjson_val *stu = yyjson_arr_get_first(arr);
    yyjson_val *id  = yyjson_obj_get(stu, "id");
    printf("%s\n", yyjson_get_str(id));
    yyjson_set_str(id, "456");

    yyjson_write_flag flag = YYJSON_WRITE_PRETTY;
    yyjson_write_err write_err;
    yyjson_write_file(file_path1, doc, flag, NULL, &write_err);
    return 0;
}

// 比较函数，用于排序字符串
static int compare_string_keys(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}

// todo: 根据key排序
static int json_key_sort()
{
    const char *file_path  = "/home/keenechen/Code_Test/data_serialization/res/yyjson.json";
    const char *file_path1 = "/home/keenechen/Code_Test/data_serialization/res/yyjson_01.json";
    yyjson_read_err read_err;
    yyjson_doc *doc = yyjson_read_file(file_path, 0, NULL, &read_err);
    if (doc == NULL) {
        yyjson_doc_free(doc);
        return read_err.code;
    }

    yyjson_val *arr = yyjson_obj_get(doc->root, "student");
    yyjson_val *stu = yyjson_arr_get_first(arr);

    size_t idx, max;
    yyjson_val *key, *val;
    size_t num_keys   = yyjson_obj_size(stu);
    const char **keys = (const char **)malloc(num_keys * sizeof(char *));
    yyjson_obj_foreach(stu, idx, max, key, val)
    {
        keys[idx] = yyjson_get_str(key);
    }

    // 对键进行排序
    // qsort(keys, num_keys, sizeof(const char *), compare_string_keys);

    // yyjson_val *id = yyjson_obj_get(stu, "id");
    // printf("%s\n", yyjson_get_str(id));
    // yyjson_set_str(id, "456");

    yyjson_write_flag flag = YYJSON_WRITE_PRETTY;
    yyjson_write_err write_err;
    yyjson_write_file(file_path1, doc, flag, NULL, &write_err);

    return 0;
}

int main(void)
{
    // write_json_str();
    write_json_file();
    // json_key_sort();

    return 0;
}