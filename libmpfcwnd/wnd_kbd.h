/******************************************************************
 * Copyright (C) 2004 by SG Software.
 ******************************************************************/

/* FILE NAME   : wnd_kbd.h
 * PURPOSE     : MPFC Window Library. Interface for keyboard 
 *               functions.
 * PROGRAMMER  : Sergey Galanov
 * LAST UPDATE : 13.08.2004
 * NOTE        : Module prefix 'wnd_kbd'.
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

#ifndef __SG_MPFC_WND_KBD_H__
#define __SG_MPFC_WND_KBD_H__

#include <curses.h>
#include <pthread.h>
#include "types.h"

/* Control- key combinations */
#define KEY_CTRL_AT		0
#define KEY_CTRL_A		1
#define KEY_CTRL_B		2
#define KEY_CTRL_C		3
#define KEY_CTRL_D		4
#define KEY_CTRL_E		5
#define KEY_CTRL_F		6
#define KEY_CTRL_G		7
#define KEY_CTRL_H		8
#define KEY_CTRL_I		9
#define KEY_TAB			9
#define KEY_CTRL_J		10
#define KEY_CTRL_K		11
#define KEY_CTRL_L		12
#define KEY_CTRL_M		13
#define KEY_CTRL_N		14
#define KEY_CTRL_O		15
#define KEY_CTRL_P		16
#define KEY_CTRL_Q		17
#define KEY_CTRL_R		18
#define KEY_CTRL_S		19
#define KEY_CTRL_T		20
#define KEY_CTRL_U		21
#define KEY_CTRL_V		22
#define KEY_CTRL_W		23
#define KEY_CTRL_X		24
#define KEY_CTRL_Y		25
#define KEY_CTRL_Z		26
#define KEY_CTRL_LSB	27
#define KEY_CTRL_BSLASH	28
#define KEY_CTRL_RSB	29
#define KEY_CTRL_CAT	30
#define KEY_CTRL_USCORE	31
#define WND_KEY_UNDEF 0xFFFF

/* Forward declaration of window */
struct tag_wnd_t;

/* Keyboard thread data type */
typedef struct tag_wnd_kbd_data_t
{
	/* Thread data */
	pthread_t m_tid;
	bool_t m_end_thread;

	/* Pointer to the root window */
	wnd_t *m_wnd_root;

	/* Known escape sequences list */
	struct wnd_kbd_seq_t
	{
		char *m_str;
		int m_code;
		struct wnd_kbd_seq_t *m_next;
	} *m_seq, *m_last_seq;
} wnd_kbd_data_t;

/* Key identification type */
typedef word wnd_key_t;
#define WND_KEY_WITH_ALT(ch)	((ch) | 0x8000)
#define WND_KEY_IS_WITH_ALT(ch)	(((ch) & 0x8000) ? ((ch) & 0x7FFF) : 0)
#define KEY_ESCAPE WND_KEY_WITH_ALT(27)

/* Initialize keyboard management system */
wnd_kbd_data_t *wnd_kbd_init( wnd_t *wnd_root );

/* Initialize the escape sequences list */
void wnd_kbd_init_seq( wnd_kbd_data_t *data );

/* Add a sequence to the list */
void wnd_kbd_add_seq( wnd_kbd_data_t *data, char *seq, int code );

/* Uninitialize keyboard management system */
void wnd_kbd_free( wnd_kbd_data_t *data );

/* Keyboard thread function */
void *wnd_kbd_thread( void *arg );

/* Extract real key code from the keys buffer */
bool_t wnd_kbd_extract_code( wnd_kbd_data_t *data, wnd_key_t *key_info, 
		char *buf, int *len );

/* Test sequence for matches in the list */
int wnd_kbd_test_seq( wnd_kbd_data_t *data, char *seq, int len, 
		wnd_key_t *code );

/* Remove a sequence from the buffer */
void wnd_kbd_rem_from_buf( char *buf, int pos, int *len );

#endif

/* End of 'wnd_kbd.h' file */

