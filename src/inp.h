/******************************************************************
 * Copyright (C) 2003 - 2005 by SG Software.
 *
 * SG MPFC. Interface for input plugin management functions.
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

#ifndef __SG_MPFC_INP_H__
#define __SG_MPFC_INP_H__

#include <sys/stat.h>
#include "types.h"
#include "file.h"
#include "genre_list.h"
#include "mystring.h"
#include "plugin.h"
#include "song_info.h"

/* Input plugin flags */
#define INP_OWN_OUT			0x00000001
#define INP_OWN_SOUND		0x00000002
#define INP_VFS				0x00000004
#define INP_VFS_NOT_FIXED	0x00000008

/* Special function flags */
#define INP_SPEC_SAVE_INFO 0x00000001

/* Forward declarations */
struct tag_pmng_t;
struct tag_song_t;

/* Special input plugin function type */
typedef struct
{
	/* Function title */
	char *m_title;

	/* Flags */
	dword m_flags;

	/* Function */
	void (*m_func)( char *filename );
} inp_spec_func_t;

/* Redirection parameters */
typedef struct
{
	int m_start_time, m_end_time;

	byte m_reserved[120];
} inp_redirect_params_t;

/* Data for exchange with plugin */
typedef struct
{
	/* Common plugin data */
	plugin_data_t m_common_data;

	/*
	 * Functions
	 */

	/* Start playing function */
	bool_t (*m_start)( char *filename );

	/* Start playing with an opened file descriptor */
	bool_t (*m_start_with_fd)( char *filename, file_t *fd );

	/* End playing function */
	void (*m_end)( void );

	/* Get stream function */
	int (*m_get_stream)( void *buf, int size );

	/* Seek song */
	void (*m_seek)( int seconds );

	/* Pause playing */
	void (*m_pause)( void );

	/* Resume playing */
	void (*m_resume)( void );

	/* Get current time */
	int (*m_get_cur_time)( void );

	/* Get song information function */
	song_info_t *(*m_get_info)( char *file_name, int *len );
	
	/* Save song information function */
	bool_t (*m_save_info)( char *file_name, song_info_t *info );
	
	/* Get supported file formats */
	void (*m_get_formats)( char *extensions, char *content_type );
	
	/* Get song audio parameters */
	void (*m_get_audio_params)( int *channels, int *frequency, dword *fmt,
									int *bitrate );

	/* Update equalizer parameters */
	void (*m_set_eq)( void );

	/* Set a title for song with empty song info */
	str_t *(*m_set_song_title)( char *filename );

	/* Set next song name */
	void (*m_set_next_song)( char *name );

	/***
	 * Virtual file system access functions
	 ***/

	/* Open a directory */
	void *(*m_vfs_opendir)( char *name );

	/* Close directory */
	void (*m_vfs_closedir)( void *dir );

	/* Read directory entry */
	char *(*m_vfs_readdir)( void *dir );

	/* Get file parameters */
	int (*m_vfs_stat)( char *name, struct stat *sb );

	/* Get type of mixer used by this plugin */
	plugin_mixer_type_t (*m_get_mixer_type)( void );

	/* Check file type */
	bool_t (*m_is_our_file)( char *filename );

	/* Redirect virtual file to a normal one */
	char *(*m_redirect)( char *filename, inp_redirect_params_t *rp );

	/* Update plugin flags (called on start of every play) */
	dword (*m_get_plugin_flags)( void );

	/* Reserved */
	byte m_reserved[36];

	/*
	 * Data
	 */

	/* Special functions list */
	int m_num_spec_funcs;
	inp_spec_func_t *m_spec_funcs;

	/* Plugin flags */
	dword m_flags;

	/* Reserved data */
	byte m_reserved1[52];
} inp_data_t;

/* Input plugin type */
typedef struct tag_in_plugin_t
{
	/* Plugin object */
	plugin_t m_plugin;

	/* Data for exchange */
	inp_data_t m_pd;
} in_plugin_t;

/* Helper macros */
#define INPUT_PLUGIN(p) ((in_plugin_t *)p)
#define INP_DATA(pd) ((inp_data_t *)pd)

/* Initialize input plugin */
plugin_t *inp_init( char *name, struct tag_pmng_t *pmng );

/* Free input plugin object */
void inp_free( plugin_t *plugin );

/* Start playing function */
bool_t inp_start( in_plugin_t *p, char *filename, file_t *fd );

/* End playing function */
void inp_end( in_plugin_t *p );

/* Get stream function */
int inp_get_stream( in_plugin_t *p, void *buf, int size );

/* Seek song */
void inp_seek( in_plugin_t *p, int seconds );

/* Pause playing */
void inp_pause( in_plugin_t *p );

/* Resume playing */
void inp_resume( in_plugin_t *p );

/* Get current time */
int inp_get_cur_time( in_plugin_t *p );

/* Get song information function */
song_info_t *inp_get_info( in_plugin_t *p, char *file_name, int *len );
	
/* Save song information function */
bool_t inp_save_info( in_plugin_t *p, char *file_name, song_info_t *info );
	
/* Get supported file formats */
void inp_get_formats( in_plugin_t *p, char *extensions, char *content_type );
	
/* Get song audio parameters */
void inp_get_audio_params( in_plugin_t *p, int *channels, 
							int *frequency, dword *fmt, int *bitrate );

/* Set equalizer parameters */
void inp_set_eq( in_plugin_t *p );

/* Initialize songs array that respects to the object */
struct tag_song_t **inp_init_obj_songs( in_plugin_t *p, char *name, 
		int *num_songs );

/* Set song title */
str_t *inp_set_song_title( in_plugin_t *p, char *filename );

/* Set next song name */
void inp_set_next_song( in_plugin_t *p, char *name );

/* Get number of special functions */
int inp_get_num_specs( in_plugin_t *p );

/* Get special function title */
char *inp_get_spec_title( in_plugin_t *p, int index );

/* Get special function flags */
dword inp_get_spec_flags( in_plugin_t *p, int index );

/* Call special function */
void inp_spec_func( in_plugin_t *p, int index, char *filename );

/* Open directory */
void *inp_vfs_opendir( in_plugin_t *p, char *name );

/* Close directory */
void inp_vfs_closedir( in_plugin_t *p, void *dir );

/* Read directory entry */
char *inp_vfs_readdir( in_plugin_t *p, void *dir );

/* Get file parameters */
int inp_vfs_stat( in_plugin_t *p, char *name, struct stat *sb );

/* Get mixer type */
plugin_mixer_type_t inp_get_mixer_type( in_plugin_t *p );

/* Check file type */
bool_t inp_is_our_file( in_plugin_t *p, char *filename );

/* Redirect file */
char *inp_redirect( in_plugin_t *p, char *filename, inp_redirect_params_t *rp );

/* Update plugin flags */
dword inp_get_plugin_flags( in_plugin_t *p );

/* Get plugin flags */
dword inp_get_flags( in_plugin_t *p );

#endif

/* End of 'inp.h' file */

