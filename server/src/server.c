#include <kore/kore.h>
#include <kore/http.h>

int page(struct http_request *);

int page(struct http_request *req)
{
	struct kore_buf buf;
	struct kore_json json;
	struct kore_json_item *item;

	kore_buf_init(&buf, 128);
	kore_json_init(&json, req->http_body->data, req->http_body->length);

	if (!kore_json_parse(&json))
	{
		kore_buf_appendf(&buf, "%s\n", kore_json_strerror(&json));
	}
	else
	{
		item = kore_json_find_string(json.root, "foo/bar");
		if (item != NULL)
		{
			kore_buf_appendf(&buf,
							 "foo.bar = '%s'\n", item->data.string);
		}
		else
		{
			kore_buf_appendf(&buf, "string foo.bar not found\n");
		}
	}

	http_response(req, 200, buf.data, buf.offset);

	kore_buf_cleanup(&buf);
	kore_json_cleanup(&json);

	return (KORE_RESULT_OK);
}