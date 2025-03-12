/*
** EPITECH PROJECT, 2024
** YML_PARSER_H_
** File description:
** Header for YML parser
*/

#ifndef YML_PARSER_H_
    #define YML_PARSER_H_

    /* ------------------------- Error messages ---------------------------- */

    #define FILE_NOT_FOUND "File not found."
    #define YML_CREATION_FAIL "YML creation failed."
    #define YML_PARSING_FAIL "YML parsing failed."
    #define YML_LINE_PARSING_FAIL "YML line parsing failed."
    #define YML_WRONG_SYNTAX "YML line wrong syntax."
    #define YML_NODE_NOT_FOUND "Node not found."
    #define YML_EMPTY_VALUE "Empty value"
    #define YML_INVALID_TYPE "Node type isn't valid"

    /* --------------------------------------------------------------------- */

    #define MAX_STRING_LEN 1024
    #define NESTING_SPACES 2

    #include <stddef.h>
    #include <stdbool.h>
    #include <sys/queue.h>

typedef struct yml_node_s {
    char *name;
    char *value;
    bool is_list;
    TAILQ_HEAD(yml_node_list_s, yml_node_s) children;
    TAILQ_ENTRY(yml_node_s) entries;
} yml_node_t;

typedef struct {
    char *raw_content;
    TAILQ_HEAD(yml_list_s, yml_node_s) nodes;
} yml_t;

typedef struct {
    yml_t *main;
    char *path;
    char *needle;
} yml_parsing_t;

/* YML */
yml_t *yml_create_from_file(const char *filepath);
yml_t *yml_create_from_string(const char *string);
yml_node_t *yml_find_node_from_path(yml_t *yml, const char *search);
void yml_dump(yml_t *yml);
int yml_save(yml_t *yml, const char *filepath);
void yml_destroy(yml_t *yml);

/* Parsing */
int yml_parse(yml_t *yml);
void yml_parsing_update_path(yml_parsing_t *parsing, size_t n);
void yml_parsing_create(yml_parsing_t *parsing, yml_t *yml);
void yml_parsing_destroy(yml_parsing_t *parsing);

/* Node */
yml_node_t *yml_node_create(const char *name, const char *value);
void yml_node_dump(yml_node_t *node, int depth);
void yml_node_destroy(yml_node_t *node);

/* Getters */
int yml_get_int(yml_t *yml, const char *path);
float yml_get_float(yml_t *yml, const char *path);
char *yml_get_str(yml_t *yml, const char *path);
bool yml_get_bool(yml_t *yml, const char *path);
int yml_get_children_n(yml_t *yml, const char *path);
char **yml_get_list(yml_t *yml, const char *path);

/* Setters */
int yml_set_int(yml_t *yml, const char *path, int value);
int yml_set_float(yml_t *yml, const char *path, float value);
int yml_set_str(yml_t *yml, const char *path, const char *value);
int yml_set_bool(yml_t *yml, const char *path, bool value);

#endif /* YML_PARSER_H_ */
