/* draw_page.c - this file is part of the GNU HaliFAX Viewer
 *
 * Copyright (C) 2000, 2001, 2002, 2003 Wolfgang Sourdeau
 *
 * Time-stamp: <2003-03-07 10:19:42 wolfgang>
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

/* This file interfaces between the raw image handling functions
   provided by tiffimages.c, zoom.c and the GTK+/GDK framework */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <gtk/gtk.h>

#include <ghfaxwidgets/ghfaxwidgets.h>

#include "tiffimages.h"
#include "cursors.h"
#include "zoom.h"
#include "viewer.h"
#include "draw_page.h"
#include "errors.h"

static gfloat zoom_factor[] = {0.25, 0.37, 0.50, 0.75, 1.0,
			       1.5, 2.0, 3.0, 4.0};

void
draw_page_func (FaxPage *ref_page, gint y, gint height,
		gpointer references)
{
  gint pixm_x, pixm_y, pixm_width, pixm_height;
  gint rowstride;
  guchar *coord;
  DrawData *draw_data;

  draw_data = references;

  if (draw_data->rotation == ROT_NONE
      || draw_data->rotation == ROT_180)
    {
      pixm_x = 0;
      pixm_y = ((draw_data->rotation == ROT_NONE)
		? y
		: (ref_page->height - y - height));
      pixm_width = ref_page->width;
      pixm_height = height;
      rowstride = ref_page->width;
      coord = (ref_page->image + pixm_y * pixm_width);
    }
  else
    {
      pixm_x = ((draw_data->rotation == ROT_RIGHT90)
		? (ref_page->height - y - height)
		: y);
      pixm_y = 0;
      pixm_width = height;
      pixm_height = ref_page->width;
      rowstride = ref_page->height;
      coord = (ref_page->image + pixm_x);
    }

  gdk_draw_gray_image (draw_data->ref_pixmap,
		       draw_data->ref_widget->style->white_gc,
		       pixm_x + 1, pixm_y + 1,
		       pixm_width, pixm_height,
		       GDK_RGB_DITHER_NORMAL,
		       coord,
		       rowstride);
  gdk_draw_gray_image (draw_data->ref_widget->window,
		       draw_data->ref_widget->style->white_gc,
		       pixm_x + 1, pixm_y + 1,
		       pixm_width, pixm_height,
		       GDK_RGB_DITHER_NORMAL,
		       coord,
		       rowstride);
}

static void
refresh_widgets (ViewerData *viewer_data)
{
  int bcounter;

  if (viewer_data->current_page->next)
    {
      gtk_widget_set_sensitive (viewer_data->cmd_menus[VIEW_NEXT_PAGE],
				TRUE);
      gtk_widget_set_sensitive (viewer_data->cmd_buttons[VIEW_NEXT_PAGE],
				TRUE);
    }
  else
    {
      gtk_widget_set_sensitive (viewer_data->cmd_menus[VIEW_NEXT_PAGE],
				FALSE);
      gtk_widget_set_sensitive (viewer_data->cmd_buttons[VIEW_NEXT_PAGE],
				FALSE);
    }
	
  if (viewer_data->current_page->prev)
    {
      gtk_widget_set_sensitive (viewer_data->cmd_menus[VIEW_PREV_PAGE],
				TRUE);
      gtk_widget_set_sensitive (viewer_data->cmd_buttons[VIEW_PREV_PAGE],
				TRUE);
    }
  else
    {
      gtk_widget_set_sensitive (viewer_data->cmd_menus[VIEW_PREV_PAGE],
				FALSE);
      gtk_widget_set_sensitive (viewer_data->cmd_buttons[VIEW_PREV_PAGE],
				FALSE);
    }
  
  if (viewer_data->zoom_index)
    {
      gtk_widget_set_sensitive (viewer_data->cmd_menus[VIEW_ZOOM_OUT],
				TRUE);     
      gtk_widget_set_sensitive (viewer_data->cmd_buttons[VIEW_ZOOM_OUT],
				TRUE);

      if (viewer_data->zoom_index == MAX_ZOOM_INDEX)
	{
	  gtk_widget_set_sensitive (viewer_data->cmd_menus[VIEW_ZOOM_IN],
				    FALSE);
	  gtk_widget_set_sensitive (viewer_data->cmd_buttons[VIEW_ZOOM_IN],
				    FALSE);
	}
      else
	{
	  gtk_widget_set_sensitive (viewer_data->cmd_menus[VIEW_ZOOM_IN],
				    TRUE);     
	  gtk_widget_set_sensitive (viewer_data->cmd_buttons[VIEW_ZOOM_IN],
				    TRUE);
	}
    }
  else
    {
      gtk_widget_set_sensitive (viewer_data->cmd_menus[VIEW_ZOOM_OUT],
				FALSE);     
      gtk_widget_set_sensitive (viewer_data->cmd_buttons[VIEW_ZOOM_OUT],
				FALSE);
    }
  
  for (bcounter = 0; 
       bcounter < viewer_data->fax_file->nbr_pages + 1;
       bcounter++)
    gtk_widget_set_sensitive (viewer_data->th_buttons[bcounter],
			      TRUE);
  gtk_widget_set_sensitive
    (viewer_data->th_buttons[viewer_data->current_page->nbr],
     FALSE);

  gtk_widget_queue_resize (viewer_data->page_area->parent);
}

GdkPixmap*
pixmap_for_page (GtkWidget *ref_widget,
		 gint ref_width, gint ref_height,
		 FaxRotationType rotation,
		 int with_frame)
{
  GdkPixmap *new_pixmap;
  gint x, y, width, height, img_width, img_height;

  if (rotation == ROT_NONE
      || rotation == ROT_180)
    {
      img_width = ref_width;
      img_height = ref_height;
    }
  else
    {
      img_width = ref_height;
      img_height = ref_width;
    }

  width = img_width;
  height = img_height;

  if (with_frame)
    {
      x = 1;
      y = 1;
      width += 2;
      height += 2;
    }
  else
    {
      x = 0;
      y = 0;
    }

  new_pixmap = gdk_pixmap_new (ref_widget->window, width, height, -1);

  gdk_draw_rectangle (new_pixmap, ref_widget->style->white_gc,
		      TRUE, 0, 0, width, height);

  if (with_frame)
    gdk_draw_rectangle (new_pixmap, ref_widget->style->black_gc,
			FALSE, 0, 0, width - 1, height - 1);

  return new_pixmap;
}

DrawData *
prepare_drawing (GtkWidget *ref_widget, GdkPixmap *ref_pixmap,
		 FaxRotationType rotation)
{
  DrawData *new_draw_data;

  new_draw_data = g_malloc (sizeof (DrawData));
  new_draw_data->ref_widget = ref_widget;
  new_draw_data->ref_pixmap = ref_pixmap;
  new_draw_data->rotation = rotation;

  return new_draw_data;
}

void
draw_page (ViewerData *viewer_data)
{
  gint area_width, area_height;
  FaxPage *zoomed_image;
  DrawData *draw_data;

  if (!viewer_data->current_page)
    viewer_data->current_page =
      ti_seek_fax_page (viewer_data->fax_file, 0);

  if (!viewer_data->current_page->image)
    ti_load_fax_page (viewer_data->fax_file,
		      viewer_data->current_page);

  if (viewer_data->page_pixmap)
    gdk_pixmap_unref (viewer_data->page_pixmap);

  area_width = (gint) ((gfloat) viewer_data->current_page->width
		       / (gfloat) viewer_data->fax_file->x_res
		       * X_DPI * zoom_factor[viewer_data->zoom_index]);
  area_height = (gint) ((gfloat) viewer_data->current_page->height
			/ (gfloat) viewer_data->fax_file->y_res
			* Y_DPI * zoom_factor[viewer_data->zoom_index]);

  if (viewer_data->rotation == ROT_NONE
      || viewer_data->rotation == ROT_180)
    gtk_widget_set_size_request (viewer_data->page_area,
				 area_width + 2, area_height + 2);
  else
    gtk_widget_set_size_request (viewer_data->page_area,
				 area_height + 2, area_width + 2);

  gdkcursor_set (viewer_data->page_area->window,
		 GDK_WATCH);
  gdkcursor_set (viewer_data->viewer_window->window,
		 GDK_WATCH);

  viewer_data->page_pixmap = 
    pixmap_for_page (viewer_data->page_area,
		     area_width, area_height,
		     viewer_data->rotation, TRUE);
  
  gdk_window_set_back_pixmap (viewer_data->page_area->window,
			      viewer_data->page_pixmap, FALSE);
  
  draw_data = prepare_drawing (viewer_data->page_area,
			       viewer_data->page_pixmap,
			       viewer_data->rotation);

  ti_set_draw_func (draw_page_func);
  ti_set_draw_func_user_data (draw_data);

  zoomed_image =
    ti_zoomed_fax_page (viewer_data->current_page,
			area_width, area_height,
			viewer_data->rotation);
	
  ti_destroy_fax_page (zoomed_image);
  ti_unload_fax_page (viewer_data->current_page);
  g_free (draw_data);

  cursor_set (viewer_data->page_area->window,
	      CURSOR_HAND_OPEN);
  gdkcursor_set (viewer_data->viewer_window->window,
		 GDK_LEFT_PTR);

  refresh_widgets (viewer_data);
}
