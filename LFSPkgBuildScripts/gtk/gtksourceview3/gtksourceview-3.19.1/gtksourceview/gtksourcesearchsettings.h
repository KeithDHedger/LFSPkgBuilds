/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8; coding: utf-8 -*- */
/* gtksourcesearchsettings.h
 * This file is part of GtkSourceView
 *
 * Copyright (C) 2013 - Sébastien Wilmet <swilmet@gnome.org>
 *
 * GtkSourceView is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * GtkSourceView is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef __GTK_SOURCE_SEARCH_SETTINGS_H__
#define __GTK_SOURCE_SEARCH_SETTINGS_H__

#include <glib-object.h>
#include <gtksourceview/gtksourcetypes.h>

G_BEGIN_DECLS

#define GTK_SOURCE_TYPE_SEARCH_SETTINGS             (gtk_source_search_settings_get_type ())
#define GTK_SOURCE_SEARCH_SETTINGS(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_SOURCE_TYPE_SEARCH_SETTINGS, GtkSourceSearchSettings))
#define GTK_SOURCE_SEARCH_SETTINGS_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_SOURCE_TYPE_SEARCH_SETTINGS, GtkSourceSearchSettingsClass))
#define GTK_SOURCE_IS_SEARCH_SETTINGS(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_SOURCE_TYPE_SEARCH_SETTINGS))
#define GTK_SOURCE_IS_SEARCH_SETTINGS_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_SOURCE_TYPE_SEARCH_SETTINGS))
#define GTK_SOURCE_SEARCH_SETTINGS_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_SOURCE_TYPE_SEARCH_SETTINGS, GtkSourceSearchSettingsClass))

typedef struct _GtkSourceSearchSettingsClass    GtkSourceSearchSettingsClass;
typedef struct _GtkSourceSearchSettingsPrivate  GtkSourceSearchSettingsPrivate;

struct _GtkSourceSearchSettings
{
	GObject parent;

	GtkSourceSearchSettingsPrivate *priv;
};

struct _GtkSourceSearchSettingsClass
{
	GObjectClass parent_class;

	gpointer padding[10];
};

GType			 gtk_source_search_settings_get_type			(void) G_GNUC_CONST;

GtkSourceSearchSettings *gtk_source_search_settings_new				(void);

void			 gtk_source_search_settings_set_search_text		(GtkSourceSearchSettings *settings,
										 const gchar		 *search_text);

const gchar		*gtk_source_search_settings_get_search_text		(GtkSourceSearchSettings *settings);

void			 gtk_source_search_settings_set_case_sensitive		(GtkSourceSearchSettings *settings,
										 gboolean		  case_sensitive);

gboolean		 gtk_source_search_settings_get_case_sensitive		(GtkSourceSearchSettings *settings);

void			 gtk_source_search_settings_set_at_word_boundaries	(GtkSourceSearchSettings *settings,
										 gboolean		  at_word_boundaries);

gboolean		 gtk_source_search_settings_get_at_word_boundaries	(GtkSourceSearchSettings *settings);

void			 gtk_source_search_settings_set_wrap_around		(GtkSourceSearchSettings *settings,
										 gboolean		  wrap_around);

gboolean		 gtk_source_search_settings_get_wrap_around		(GtkSourceSearchSettings *settings);

void			 gtk_source_search_settings_set_regex_enabled		(GtkSourceSearchSettings *settings,
										 gboolean		  regex_enabled);

gboolean		 gtk_source_search_settings_get_regex_enabled		(GtkSourceSearchSettings *settings);

G_END_DECLS

#endif /* __GTK_SOURCE_SEARCH_SETTINGS_H__ */
