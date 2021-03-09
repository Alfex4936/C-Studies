#include <kore/kore.h>
#include <kore/http.h>
#include <string.h>

struct kore_json_item *build_simple_text(char *msg);
char *get_json_data(struct kore_json_item *json, char *keyword);

int page(struct http_request *);

int page(struct http_request *req)
{
	struct kore_buf buf;
	// struct kore_json request;
	struct kore_json_item *json;

	kore_buf_init(&buf, 1024);

	/* Request JSON 받아올 때 */
	// kore_json_init(&request, req->http_body->data, req->http_body->length);
	// if (!kore_json_parse(&request))
	// {
	// 	kore_buf_appendf(&buf, "%s\n", kore_json_strerror(&request)); // 200, Error SimpleText
	// 	http_response(req, 200, NULL, 0);
	// 	return (KORE_RESULT_OK);
	// }
	// utter = get_json_data(&request, "userRequest/utterance"); // 유저 발화문
	// kore_buf_appendf(&buf, "utterance = '%s'\n", utter);
	/* Request JSON 받아올 때 */

	json = build_simple_text("First SimpleText!");

	kore_json_item_tobuf(json, &buf);

	char *answer = kore_buf_stringify(&buf, NULL);

	// 항상 JSON response
	http_response_header(req, "Content-Type", "application/json; charset=utf-8");

	http_response(req, 200, answer, strlen(answer));
	// http_response(req, 200, buf.data, buf.offset);

	kore_buf_cleanup(&buf);
	kore_json_item_free(json);
	// kore_json_cleanup(&request);

	return (KORE_RESULT_OK);
}
