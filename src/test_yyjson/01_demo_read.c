#include "yyjson.h"
#include <stdio.h>

void read_json_string()
{
    const char *json = "{\"name\":\"Mash\",\"star\":4,\"hits\":[2,2,1,3]}";

    // Read JSON and get root
    yyjson_doc *doc  = yyjson_read(json, strlen(json), 0);
    yyjson_val *root = yyjson_doc_get_root(doc);

    // Get root["name"]
    yyjson_val *name = yyjson_obj_get(root, "name");
    printf("name: %s\n", yyjson_get_str(name));
    printf("name length:%d\n", (int)yyjson_get_len(name));

    // Get root["star"]
    yyjson_val *star = yyjson_obj_get(root, "star");
    printf("star: %d\n", (int)yyjson_get_int(star));

    // Get root["hits"], iterate over the array
    yyjson_val *hits = yyjson_obj_get(root, "hits");
    size_t idx, max;
    yyjson_val *hit;
    yyjson_arr_foreach(hits, idx, max, hit)
    {
        printf("hit%d: %d\n", (int)idx, (int)yyjson_get_int(hit));
    }

    // Free the doc
    yyjson_doc_free(doc);
}

void read_json_file()
{
    // Read JSON file, allowing comments and trailing commas
    yyjson_read_flag flg = YYJSON_READ_ALLOW_COMMENTS | YYJSON_READ_ALLOW_TRAILING_COMMAS;
    yyjson_read_err err;
    yyjson_doc *doc = yyjson_read_file("../../res/yyjson.json", flg, NULL, &err);

    // Iterate over the root object
    if (doc) {
        yyjson_val *obj = yyjson_doc_get_root(doc);
        yyjson_obj_iter iter;
        yyjson_obj_iter_init(obj, &iter);
        yyjson_val *key, *val;
        while ((key = yyjson_obj_iter_next(&iter))) {
            val = yyjson_obj_iter_get_val(key);
            printf("%s: %s\n", yyjson_get_str(key), yyjson_get_type_desc(val));
        }
    }
    else {
        printf("read error (%u): %s at position: %ld\n", err.code, err.msg, err.pos);
    }

    // Free the doc
    yyjson_doc_free(doc);
}

int main(void)
{
    read_json_string();
    read_json_file();

    return 0;
}