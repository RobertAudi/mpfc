/******************************************************************
 * Copyright (C) 2003 - 2005 by SG Software.
 *
 * SG MPFC. Song info management functions implementation.
 * $Id$
 *
 * This program is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU General Public License 
 * as published by the Free Software Foundation; either version 2 
 * of the License, or (at your option) any later version.
 *  
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *  
 * You should have received a copy of the GNU General Public 
 * License along with this program; if not, write to the Free 
 * Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, 
 * MA 02111-1307, USA.
 */

#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "charset.h"
#include "genre_list.h"
#include "pmng.h"
#include "song_info.h"

/* Initialize song info */
song_info_t *si_new( void )
{
	song_info_t *si;

	/* Allocate memory */
	si = (song_info_t *)malloc(sizeof(song_info_t));
	if (si == NULL)
		return NULL;

	/* Set empty fields */
	memset(si, 0, sizeof(*si));
	si->m_name = strdup("");
	si->m_artist = strdup("");
	si->m_album = strdup("");
	si->m_year = strdup("");
	si->m_track = strdup("");
	si->m_comments = strdup("");
	si->m_own_data = strdup("");
	si->m_genre = strdup("");
	si->m_charset = NULL;
	si->m_glist = NULL;
	return si;
} /* End of 'si_new' function */

/* Duplicate song info */
song_info_t *si_dup( song_info_t *info )
{
	song_info_t *si;
	
	if (info == NULL)
		return NULL;

	/* Allocate memory */
	si = (song_info_t *)malloc(sizeof(*si));
	if (si == NULL)
		return NULL;

	/* Copy fields */
	memset(si, 0, sizeof(*si));
	si->m_name = strdup(info->m_name);
	si->m_artist = strdup(info->m_artist);
	si->m_album = strdup(info->m_album);
	si->m_year = strdup(info->m_year);
	si->m_track = strdup(info->m_track);
	si->m_comments = strdup(info->m_comments);
	si->m_genre = strdup(info->m_genre);
	si->m_own_data = strdup(info->m_own_data);
	if (info->m_charset != NULL)
		si->m_charset = strdup(info->m_charset);
	else
		si->m_charset = NULL;
	si->m_flags = info->m_flags;
	si->m_glist = info->m_glist;
	return si;
} /* End of 'si_dup' function */

/* Free song info */
void si_free( song_info_t *si )
{
	if (si == NULL)
		return;

	/* Free memory */
	free(si->m_name);
	free(si->m_artist);
	free(si->m_album);
	free(si->m_year);
	free(si->m_track);
	free(si->m_comments);
	free(si->m_own_data);
	free(si->m_genre);
	if (si->m_charset != NULL)
		free(si->m_charset);
	free(si);
} /* End of 'si_free' function */

/* Set song name */
void si_set_name( song_info_t *si, char *name )
{
	if (si == NULL)
		return;

	free(si->m_name);
	si->m_name = strdup(name == NULL ? "" : name);
	if (name != NULL)
		si->m_flags |= SI_INITIALIZED;
} /* End of 'si_set_name' function */

/* Set artist name */
void si_set_artist( song_info_t *si, char *artist )
{
	if (si == NULL)
		return;

	free(si->m_artist);
	si->m_artist = strdup(artist == NULL ? "" : artist);
	if (artist != NULL)
		si->m_flags |= SI_INITIALIZED;
} /* End of 'si_set_artist' function */

/* Set album name */
void si_set_album( song_info_t *si, char *album )
{
	if (si == NULL)
		return;

	free(si->m_album);
	si->m_album = strdup(album == NULL ? "" : album);
	if (album != NULL)
		si->m_flags |= SI_INITIALIZED;
} /* End of 'si_set_album' function */

/* Set year */
void si_set_year( song_info_t *si, char *year )
{
	if (si == NULL)
		return;

	free(si->m_year);
	si->m_year = strdup(year == NULL ? "" : year);
	if (year != NULL)
		si->m_flags |= SI_INITIALIZED;
} /* End of 'si_set_year' function */

/* Set track */
void si_set_track( song_info_t *si, char *track )
{
	if (si == NULL)
		return;

	free(si->m_track);
	si->m_track = strdup(track == NULL ? "" : track);
	if (track != NULL)
		si->m_flags |= SI_INITIALIZED;
} /* End of 'si_set_track' function */

/* Set comments */
void si_set_comments( song_info_t *si, char *comments )
{
	if (si == NULL)
		return;

	free(si->m_comments);
	si->m_comments = strdup(comments == NULL ? "" : comments);
	if (comments != NULL)
		si->m_flags |= SI_INITIALIZED;
} /* End of 'si_set_comments' function */

/* Set genre */
void si_set_genre( song_info_t *si, char *genre )
{
	int id;
	char *s;

	if (si == NULL)
		return;

	/* Free memory */
	free(si->m_genre);
	if (genre == NULL)
	{
		si->m_genre = strdup("");
		return;
	}
	
	/* Genre string is a number */
	id = glist_str2num(genre);
	if (id >= 0 && si->m_glist != NULL)
	{
		char *name;
		
		/* Get this genre name */
		name = glist_get_name_by_id(si->m_glist, id);
		if (name != NULL)
			si->m_genre = strdup(name);
		else
			si->m_genre = strdup(genre);
		si->m_flags |= SI_INITIALIZED;
		return;
	}

	/* If not - set this string as genre and remove its id (if exists) */
	si->m_genre = strdup(genre);
	s = strrchr(si->m_genre, '(');
	if (s != NULL)
		*s = 0;
	si->m_flags |= SI_INITIALIZED;
} /* End of 'si_set_genre' function */

/* Set own data */
void si_set_own_data( song_info_t *si, char *own_data )
{
	if (si == NULL)
		return;

	free(si->m_own_data);
	si->m_own_data = strdup(own_data == NULL ? "" : own_data);
} /* End of 'si_set_own_data' function */

/* Set charset */
void si_set_charset( song_info_t *si, char *cs )
{
	if (si == NULL)
		return;

	if (si->m_charset != NULL)
		free(si->m_charset);
	if (cs == NULL)
		si->m_charset = NULL;
	else
		si->m_charset = strdup(cs);
} /* End of 'si_set_charset' function */

/* Convert info fields from one charset to another */
void si_convert_cs( song_info_t *si, char *new_cs, pmng_t *pmng )
{
	char *str;
	
	if (si == NULL || new_cs == NULL || pmng == NULL)
		return;

	si_convert_field(si, &si->m_name, new_cs, pmng);
	si_convert_field(si, &si->m_artist, new_cs, pmng);
	si_convert_field(si, &si->m_album, new_cs, pmng);
	si_convert_field(si, &si->m_year, new_cs, pmng);
	si_convert_field(si, &si->m_track, new_cs, pmng);
	si_convert_field(si, &si->m_comments, new_cs, pmng);
	si_set_charset(si, new_cs);
} /* End of 'si_convert_cs' function */

/* Convert one field */
void si_convert_field( song_info_t *si, char **field, char *new_cs, 
							pmng_t *pmng )
{
	char *cs;
	char *str;
	
	cs = si->m_charset;
	if (cs == NULL)
		cs = cfg_get_var(pmng_get_cfg(pmng), "charset-input");
	str = cs_convert(*field, cs, new_cs, pmng);
	if (str != NULL)
	{
		free(*field);
		*field = str;
	}
} /* End of 'si_convert_field' function */

/* End of 'song_info.h' file */

