/******************************************************************
 * Copyright (C) 2003 by SG Software.
 ******************************************************************/

/* FILE NAME   : eqwnd.h
 * PURPOSE     : SG MPFC. Interface for equalizer window functions.
 * PROGRAMMER  : Sergey Galanov
 * LAST UPDATE : 5.08.2004
 * NOTE        : Module prefix 'eqwnd'.
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

#ifndef __SG_MPFC_EQUALIZER_H__
#define __SG_MPFC_EQUALIZER_H__

#include "types.h"
#include "wnd.h"

/* Equalizer window type */
typedef struct 
{
	/* Window part */
	wnd_t m_wnd;

	/* Cursor position */
	int m_pos, m_scroll;

	/* Currently selected band value */
	float m_cur_value;
} eq_wnd_t;

/* Convert window object to equalizer window type */
#define EQWND_OBJ(wnd) ((eq_wnd_t *)wnd)

/* Create a new equalizer window */
eq_wnd_t *eqwnd_new( wnd_t *parent );

/* Initialize equalizer window */
bool_t eqwnd_construct( eq_wnd_t *eq, wnd_t *parent );

/* Handle display message */
wnd_msg_retcode_t eqwnd_on_display( wnd_t *wnd );

/* Handle 'action' message */
wnd_msg_retcode_t eqwnd_on_action( wnd_t *wnd, char *action );

/* Handle mouse left button click */
wnd_msg_retcode_t eqwnd_on_mouse_ldown( wnd_t *wnd, int x, int y,
		wnd_mouse_button_t btn, wnd_mouse_event_t type );

/* Display slider */
int eqwnd_display_slider( eq_wnd_t *eq, int x, bool_t hl, float val, 
		char *str );

/* Get equalizer band slider position */
void eqwnd_get_slider_pos( eq_wnd_t *eq, int band, int *x, int *y, int *w, 
		int *h );

/* Convert band value to position */
int eqwnd_val2pos( float value, int height );

/* Convert position to band value */
float eqwnd_pos2val( int pos, int height );

/* Show help screen */
void eqwnd_help( eq_wnd_t *eq );

/* Initialize equalizer window class */
wnd_class_t *eqwnd_class_init( wnd_global_data_t *global );

/* Set equalizer window class default styles */
void eqwnd_class_set_default_styles( cfg_node_t *list );

/* Get equlizer band value */
float eqwnd_get_band( int band );

/* Set equalizer band value */
void eqwnd_set_band( int band, float val );

/* Launch load preset from EQF file dialog */
void eqwnd_load_eqf_dlg( void );

/* Handle 'ok_clicked' for EQF loading dialog */
wnd_msg_retcode_t eqwnd_on_load( wnd_t *wnd );

/* Load a Winamp EQF file */
void eqwnd_load_eqf( char *filename );

/* Scroll window if current band is not visible */
void eqwnd_scroll( eq_wnd_t *eq );

#endif

/* End of 'eqwnd.h' file */

