/* viewer.h - this file is part of the GNU HaliFAX Viewer
 *
 * Copyright (C) 2000-2001 Wolfgang Sourdeau
 *
 * Author: Wolfgang Sourdeau <wolfgang@contre.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef VIEWER_H
#define VIEWER_H

#include "i18n.h"

/* these are barely the measures for my own screen a 17" in 1024x768,
   but is likely to not be correct for other people. */
#define X_DPI 84.7
#define Y_DPI 84.7

#define MAX_ZOOM_INDEX 8

typedef struct _ViewerData ViewerData;
typedef struct _MotionData MotionData;

typedef enum
{
  FILE_CLOSE,
  FILE_PRINT,
  FILE_PROPERTIES,
  VIEW_NEXT_PAGE,
  VIEW_PREV_PAGE,
  VIEW_ZOOM_IN,
  VIEW_ZOOM_OUT,
  VIEW_ROTATE_RIGHT90,
  VIEW_ROTATE_REVERSE,
  VIEW_ROTATE_LEFT90,
  NBR_ACTIONS
} ActionIndex;

#define FIRST_BUTTON  1
#define FIRST_MENU    0

struct _ViewerData
{
  FaxFile *fax_file;
  FaxPage *current_page;
  guint zoom_index;
  
  GdkPixmap *page_pixmap;
  GtkWidget *viewer_window;
  GtkWidget *page_area;
  int rotation;

  /* File selection dialog */
  GtkWidget *file_dlg;
  
  /* action (command) widgets */
  GtkWidget *cmd_buttons[NBR_ACTIONS];
  GtkWidget *cmd_menus[NBR_ACTIONS]; 

  /* thumbnails */
  GtkWidget *thumbs_layout;
  GtkWidget **th_buttons;
  
  /* Cursor motion data */
  MotionData *motion_data;

  /* printing */
  void *print_job;
};

struct _MotionData
{
  gboolean dragging;
  guint orig_x, orig_y;
  gfloat orig_adj_x, orig_adj_y;
};

GdkPixmap *pixmap_for_page (GtkWidget *ref_widget,
			    gint ref_width, gint ref_height,
			    FaxRotationType rotation,
			    int with_frame);

ViewerData *fax_viewer_new ();
void fax_viewer_open_file (ViewerData *viewer_data, gchar *file_name);

void increase_win_count ();
void decrease_win_count ();

/* functions from C files of which it would be a waste of time to
 * create an interface H file. */

void draw_page (ViewerData *viewer_data);
GtkWidget *thumbs_fixed_new ();
void add_thumbs (ViewerData *viewer_data);
void destroy_thumb (gpointer fixed_child, gpointer container);

void about_cb (GtkWidget *irrelevant_1, gpointer irrelevant_2);
void close_file_cb (GtkWidget *irrelevant, ViewerData *viewer_data);
void file_dialog_cb (GtkWidget* irrelevant, ViewerData *viewer_data);
void info_cb (GtkWidget *irrelevant, ViewerData *viewer_data);

#ifdef __WIN32__
gchar *win32_pixmap_file (gchar *pixmap);
#endif

void closeviewer_cb (GtkWidget *widget, ViewerData *viewer_data);

#endif
