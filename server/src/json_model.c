#include <kore/kore.h>
#include <kore/http.h>
#include <string.h>
#include <stdio.h>

extern struct kore_json_item *build_simple_text(char *msg)
{
    struct kore_json_item *json;
    struct kore_json_item *template;
    struct kore_json_item *outputs;
    struct kore_json_item *simpleTextOuter;
    struct kore_json_item *simpleText;
    struct kore_json_item *text;

    json = kore_json_create_object(NULL, NULL);

    template = kore_json_create_object(json, "template");
    outputs = kore_json_create_array(template, "outputs");
    simpleTextOuter = kore_json_create_object(outputs, NULL);
    simpleText = kore_json_create_object(simpleTextOuter, "simpleText");
    text = kore_json_create_object(simpleText, NULL);
    kore_json_create_string(text, "text", msg); // 마지막으로 text 만들기

    kore_json_create_string(json, "version", "2.0");

    return json;
}

extern char *get_json_data(struct kore_json *json, char *keyword)
{
    struct kore_json_item *find = kore_json_find_string(json->root, keyword);
    if (find != NULL)
    {
        return find->data.string;
    }
    else
    {
        fprintf(stderr, "Could not find %s\n", keyword);
        return NULL;
    }
}
