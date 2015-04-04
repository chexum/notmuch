#include "notmuch-client.h"
#include "sprinter.h"

notmuch_status_t
sprinter_start_output (sprinter_t *sp,
		       const notmuch_query_t *query,
		       const char *query_type)
{
    long int rev;
    const char *uuid;
    notmuch_database_t *notmuch;

    sp->begin_list (sp);

    if (sp->type != NOTMUCH_SPRINTER_TEXT && notmuch_format_version >= 3) {
	notmuch = notmuch_query_get_database (query);

	rev = notmuch_database_get_revision (notmuch, &uuid);

	sp->begin_map (sp);
	sp->map_key (sp, "query_type");
	sp->string (sp, query_type);

	sp->map_key (sp, "uuid");
	sp->string (sp, uuid);

	sp->map_key (sp, "lastmod");
	sp->integer (sp, rev);

	sp->end (sp);

    }
    return NOTMUCH_STATUS_SUCCESS;
}

notmuch_status_t
sprinter_finish_output (sprinter_t *sp)
{
    sp->end (sp); /* map */
    return NOTMUCH_STATUS_SUCCESS;
}
