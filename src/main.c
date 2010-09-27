#include <glib.h>

#include "ani-net.h"
#include "ani-parser.h"

int main (void)
{
    g_type_init ();

    SoupMessage *msg;

    msg = request ("bakemonogatari", ANIME, 0, 0);

    parse (msg->response_body->data, msg->response_body->length);

    return 0;
}
