#include <stdio.h>
#include <yaml.h>

int main()
{
    FILE* file;
    yaml_parser_t parser;
    yaml_token_t token;

    file = fopen("./res/example.yaml", "rb");

    yaml_parser_initialize(&parser);
    yaml_parser_set_input_file(&parser, file);

    int done = 0;
    while (!done) {
        if (!yaml_parser_scan(&parser, &token)) {
            printf("Parser error\n");
            return 1;
        }

        switch (token.type) {
        case YAML_STREAM_START_TOKEN:
            printf("STREAM START\n");
            break;

        case YAML_STREAM_END_TOKEN:
            printf("STREAM END\n");
            done = 1;
            break;

        case YAML_DOCUMENT_START_TOKEN:
            printf("DOCUMENT START\n");
            break;

        case YAML_DOCUMENT_END_TOKEN:
            printf("DOCUMENT END\n");
            break;

        case YAML_SCALAR_TOKEN:
            printf("SCALAR (%s)\n", token.data.scalar.value);
            break;

        default:
            printf("Unknown token\n");
            break;
        }

        if (token.type != YAML_STREAM_END_TOKEN) {
            yaml_token_delete(&token);
        }
    }

    yaml_parser_delete(&parser);
    fclose(file);

    return 0;
}
