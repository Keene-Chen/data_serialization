#include "libxml/parser.h"
#include "libxml/tree.h"
#include <stdio.h>

void print_element_names(xmlNode* node)
{
    xmlNode* cur_node = NULL;

    for (cur_node = node; cur_node; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
            printf("Element name: %s\n", cur_node->name);
            
        }

        print_element_names(cur_node->children);
    }
}

int main()
{
    xmlDoc* doc           = NULL;
    xmlNode* root_element = NULL;

    doc = xmlReadFile("./res/example.xml", NULL, 0);

    if (doc == NULL) {
        printf("Failed to parse document\n");
        return 1;
    }

    root_element = xmlDocGetRootElement(doc);
    print_element_names(root_element);

    xmlFreeDoc(doc);
    xmlCleanupParser();
    return 0;
}
