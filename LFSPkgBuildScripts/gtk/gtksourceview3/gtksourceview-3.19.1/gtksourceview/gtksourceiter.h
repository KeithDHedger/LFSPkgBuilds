/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8; coding: utf-8 -*- */
/* gtksourceiter.h
 * This file is part of GtkSourceView
 *
 * Copyright (C) 2014 - Sébastien Wilmet <swilmet@gnome.org>
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

#ifndef __GTK_SOURCE_ITER_H__
#define __GTK_SOURCE_ITER_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS

/* Semi-public functions. */

G_GNUC_INTERNAL
gboolean	_gtk_source_iter_forward_visible_word_end		(GtkTextIter *iter);

G_GNUC_INTERNAL
gboolean	_gtk_source_iter_forward_visible_word_ends		(GtkTextIter *iter,
									 gint         count);

G_GNUC_INTERNAL
gboolean	_gtk_source_iter_backward_visible_word_start		(GtkTextIter *iter);

G_GNUC_INTERNAL
gboolean	_gtk_source_iter_backward_visible_word_starts		(GtkTextIter *iter,
									 gint         count);

G_GNUC_INTERNAL
void		_gtk_source_iter_extend_selection_word			(const GtkTextIter *location,
									 GtkTextIter       *start,
									 GtkTextIter       *end);

/* Internal functions, in the header for unit tests. */

G_GNUC_INTERNAL
void		_gtk_source_iter_forward_full_word_end			(GtkTextIter *iter);

G_GNUC_INTERNAL
void		_gtk_source_iter_backward_full_word_start		(GtkTextIter *iter);

G_GNUC_INTERNAL
gboolean	_gtk_source_iter_starts_full_word			(const GtkTextIter *iter);

G_GNUC_INTERNAL
gboolean	_gtk_source_iter_ends_full_word				(const GtkTextIter *iter);

G_GNUC_INTERNAL
void		_gtk_source_iter_forward_extra_natural_word_end		(GtkTextIter *iter);

G_GNUC_INTERNAL
void		_gtk_source_iter_backward_extra_natural_word_start	(GtkTextIter *iter);

G_GNUC_INTERNAL
gboolean	_gtk_source_iter_starts_extra_natural_word		(const GtkTextIter *iter);

G_GNUC_INTERNAL
gboolean	_gtk_source_iter_ends_extra_natural_word		(const GtkTextIter *iter);

G_GNUC_INTERNAL
gboolean	_gtk_source_iter_starts_word				(const GtkTextIter *iter);

G_GNUC_INTERNAL
gboolean	_gtk_source_iter_ends_word				(const GtkTextIter *iter);

G_GNUC_INTERNAL
gboolean	_gtk_source_iter_inside_word				(const GtkTextIter *iter);

G_END_DECLS

#endif /* __GTK_SOURCE_ITER_H__ */
