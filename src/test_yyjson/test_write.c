#include "yyjson.h"

#include <stdio.h>

void write_json_string()
{
    // Create a mutable doc
    yyjson_mut_doc* doc  = yyjson_mut_doc_new(NULL);
    yyjson_mut_val* root = yyjson_mut_obj(doc);
    yyjson_mut_doc_set_root(doc, root);

    // Set root["name"] and root["star"]
    yyjson_mut_obj_add_str(doc, root, "name", "Mash");
    yyjson_mut_obj_add_int(doc, root, "star", 4);

    // Set root["hits"] with an array
    int hits_arr[]       = { 2, 2, 1, 3 };
    yyjson_mut_val* hits = yyjson_mut_arr_with_sint32(doc, hits_arr, 4);
    yyjson_mut_obj_add_val(doc, root, "hits", hits);

    // To string, minified
    const char* json = yyjson_mut_write(doc, 0, NULL);
    if (json) {
        printf("json: %s\n", json); // {"name":"Mash","star":4,"hits":[2,2,1,3]}
        free((void*)json);
    }

    // Free the doc
    yyjson_mut_doc_free(doc);
}

void write_json_file()
{
    // Read the JSON file as a mutable doc
    yyjson_doc* idoc    = yyjson_read_file("../../res/yyjson.json", 0, NULL, NULL);
    yyjson_mut_doc* doc = yyjson_doc_mut_copy(idoc, NULL);
    yyjson_mut_val* obj = yyjson_mut_doc_get_root(doc);

    // Remove null values in root object
    yyjson_mut_obj_iter iter;
    yyjson_mut_obj_iter_init(obj, &iter);
    yyjson_mut_val *key, *val;
    while ((key = yyjson_mut_obj_iter_next(&iter))) {
        val = yyjson_mut_obj_iter_get_val(key);
        if (yyjson_mut_is_null(val)) {
            yyjson_mut_obj_iter_remove(&iter);
        }
    }

    // Write the json pretty, escape unicode
    yyjson_write_flag flg = YYJSON_WRITE_PRETTY ;
    yyjson_write_err err;
    yyjson_mut_write_file("../../res/yyjson.json", doc, flg, NULL, &err);
    if (err.code) {
        printf("write error (%u): %s\n", err.code, err.msg);
    }

    // Free the doc
    yyjson_doc_free(idoc);
    yyjson_mut_doc_free(doc);
}

int main(void)
{
    write_json_string();
    write_json_file();

    return 0;
}