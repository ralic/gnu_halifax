/* ghfwdlgwindow.h - this file is part of the GNU HaliFAX Widgets library
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

#ifndef GHFW_DLG_WINDOW_H
#define GHFW_DLG_WINDOW_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define GHFW_TYPE_DLG_WINDOW            (ghfw_dlg_window_get_type ())
#define GHFW_DLG_WINDOW(obj)		(GTK_CHECK_CAST (obj, GHFW_TYPE_DLG_WINDOW, GhfwDlgWindow))
#define GHFW_DLG_WINDOW_CLASS(obj)	(GTK_CHECK_CAST (obj, GHFW_TYPE_DLG_WINDOW, GhfwDlgWindowClass))
#define GHFW_IS_DLG_WINDOW(obj)         (GTK_CHECK_TYPE (obj, GHFW_TYPE_DLG_WINDOW))
#define GHFW_IS_DLG_WINDOW_CLASS(klass) (GTK_CHECK_CLASS_TYPE (klass, GHFW_TYPE_DLG_WINDOW))


typedef struct _GhfwDlgWindow GhfwDlgWindow;
typedef struct _GhfwDlgWindowClass GhfwDlgWindowClass;

struct _GhfwDlgWindow
{
  GtkWindow window;

  GtkWidget *vbox, *content, *button_box;

  guint escapable:1;
};

struct _GhfwDlgWindowClass
{
  GtkWindowClass parent_class;

  void (* escaped) (GhfwDlgWindow *dlg_window);
};

GtkType        ghfw_dlg_window_get_type       (void);


GtkWidget *ghfw_dlg_window_new (gchar *title);
void ghfw_dlg_window_set_content (GhfwDlgWindow *window, GtkWidget *content);
void ghfw_dlg_window_set_content_with_frame (GhfwDlgWindow *window,
					     GtkWidget *content);
void ghfw_dlg_window_set_button_box (GhfwDlgWindow *window,
				     GtkWidget *button_box);
void ghfw_dlg_window_set_button (GhfwDlgWindow *window,
				 GtkWidget *button);

void ghfw_dlg_window_set_escapable (GhfwDlgWindow *window);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* GHFW_DLG_WINDOW_H */