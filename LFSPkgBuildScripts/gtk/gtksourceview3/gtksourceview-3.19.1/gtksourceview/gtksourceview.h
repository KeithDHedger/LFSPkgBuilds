/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8; coding: utf-8 -*-
 * gtksourceview.h
 * This file is part of GtkSourceView
 *
 * Copyright (C) 2001 - Mikael Hermansson <tyan@linux.se> and
 *                       Chris Phelps <chicane@reninet.com>
 * Copyright (C) 2003 - Gustavo Giráldez and Paolo Maggi
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

#ifndef __GTK_SOURCE_VIEW_H__
#define __GTK_SOURCE_VIEW_H__

#include <gtk/gtk.h>
#include <gtksourceview/gtksourcetypes.h>

G_BEGIN_DECLS

#define GTK_SOURCE_TYPE_VIEW             (gtk_source_view_get_type ())
#define GTK_SOURCE_VIEW(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_SOURCE_TYPE_VIEW, GtkSourceView))
#define GTK_SOURCE_VIEW_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_SOURCE_TYPE_VIEW, GtkSourceViewClass))
#define GTK_SOURCE_IS_VIEW(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_SOURCE_TYPE_VIEW))
#define GTK_SOURCE_IS_VIEW_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_SOURCE_TYPE_VIEW))
#define GTK_SOURCE_VIEW_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_SOURCE_TYPE_VIEW, GtkSourceViewClass))

typedef struct _GtkSourceViewClass GtkSourceViewClass;
typedef struct _GtkSourceViewPrivate GtkSourceViewPrivate;

/**
 * GtkSourceViewGutterPosition:
 * @GTK_SOURCE_VIEW_GUTTER_POSITION_LINES: the gutter position of the lines
 * renderer
 * @GTK_SOURCE_VIEW_GUTTER_POSITION_MARKS: the gutter position of the marks
 * renderer
 */
typedef enum
{
	GTK_SOURCE_VIEW_GUTTER_POSITION_LINES = -30,
	GTK_SOURCE_VIEW_GUTTER_POSITION_MARKS = -20
} GtkSourceViewGutterPosition;

struct _GtkSourceView
{
	GtkTextView parent;

	GtkSourceViewPrivate *priv;
};

struct _GtkSourceViewClass
{
	GtkTextViewClass parent_class;

	void (*undo) (GtkSourceView *view);
	void (*redo) (GtkSourceView *view);
	void (*line_mark_activated) (GtkSourceView *view,
	                             GtkTextIter   *iter,
	                             GdkEvent      *event);
	void (*show_completion) (GtkSourceView *view);
	void (*move_lines) (GtkSourceView *view,
	                    gboolean       copy,
	                    gint           step);

	void (*move_words) (GtkSourceView *view,
	                    gint           step);

	/* Padding for future expansion */
};

/**
 * GtkSourceSmartHomeEndType:
 * @GTK_SOURCE_SMART_HOME_END_DISABLED: smart-home-end disabled.
 * @GTK_SOURCE_SMART_HOME_END_BEFORE: move to the first/last
 * non-whitespace character on the first press of the HOME/END keys and
 * to the beginning/end of the line on the second press.
 * @GTK_SOURCE_SMART_HOME_END_AFTER: move to the beginning/end of the
 * line on the first press of the HOME/END keys and to the first/last
 * non-whitespace character on the second press.
 * @GTK_SOURCE_SMART_HOME_END_ALWAYS: always move to the first/last
 * non-whitespace character when the HOME/END keys are pressed.
 */
typedef enum
{
	GTK_SOURCE_SMART_HOME_END_DISABLED,
	GTK_SOURCE_SMART_HOME_END_BEFORE,
	GTK_SOURCE_SMART_HOME_END_AFTER,
	GTK_SOURCE_SMART_HOME_END_ALWAYS
} GtkSourceSmartHomeEndType;

/**
 * GtkSourceDrawSpacesFlags:
 * @GTK_SOURCE_DRAW_SPACES_SPACE: whether the space character should be drawn.
 * @GTK_SOURCE_DRAW_SPACES_TAB: whether the tab character should be drawn.
 * @GTK_SOURCE_DRAW_SPACES_NEWLINE: whether the line breaks should be drawn.
 * @GTK_SOURCE_DRAW_SPACES_NBSP: whether the non-breaking whitespaces should be drawn.
 * @GTK_SOURCE_DRAW_SPACES_LEADING: whether leading whitespaces should be drawn.
 * @GTK_SOURCE_DRAW_SPACES_TEXT: whether whitespaces inside text should be drawn.
 * @GTK_SOURCE_DRAW_SPACES_TRAILING: whether trailing whitespaces should be drawn.
 * @GTK_SOURCE_DRAW_SPACES_ALL: wheter all kind of spaces should be drawn.
 *
 * GtkSourceDrawSpacesFlags determine what kind of spaces whould be drawn. If none
 * of GTK_SOURCE_DRAW_SPACES_LEADING, GTK_SOURCE_DRAW_SPACES_TEXT or
 * GTK_SOURCE_DRAW_SPACES_TRAILING is specified, whitespaces at any position in
 * the line will be drawn (i.e. it has the same effect as specifying all of them).
 */
typedef enum
{
	GTK_SOURCE_DRAW_SPACES_SPACE      = 1 << 0,
	GTK_SOURCE_DRAW_SPACES_TAB        = 1 << 1,
	GTK_SOURCE_DRAW_SPACES_NEWLINE    = 1 << 2,
	GTK_SOURCE_DRAW_SPACES_NBSP       = 1 << 3,
	GTK_SOURCE_DRAW_SPACES_LEADING    = 1 << 4,
	GTK_SOURCE_DRAW_SPACES_TEXT       = 1 << 5,
	GTK_SOURCE_DRAW_SPACES_TRAILING   = 1 << 6,
	GTK_SOURCE_DRAW_SPACES_ALL        = 0x7f
} GtkSourceDrawSpacesFlags;


GType		 gtk_source_view_get_type 		(void) G_GNUC_CONST;

GtkWidget 	*gtk_source_view_new 			(void);

GtkWidget 	*gtk_source_view_new_with_buffer	(GtkSourceBuffer *buffer);

void 		 gtk_source_view_set_show_line_numbers 	(GtkSourceView   *view,
							 gboolean         show);

gboolean 	 gtk_source_view_get_show_line_numbers 	(GtkSourceView   *view);

void 		 gtk_source_view_set_tab_width          (GtkSourceView   *view,
							 guint            width);

guint            gtk_source_view_get_tab_width          (GtkSourceView   *view);

void		 gtk_source_view_set_indent_width 	(GtkSourceView   *view,
							 gint             width);

gint		 gtk_source_view_get_indent_width	(GtkSourceView   *view);

void		 gtk_source_view_set_auto_indent 	(GtkSourceView   *view,
							 gboolean         enable);

gboolean	 gtk_source_view_get_auto_indent 	(GtkSourceView   *view);

void		 gtk_source_view_set_insert_spaces_instead_of_tabs
							(GtkSourceView   *view,
							 gboolean         enable);

gboolean	 gtk_source_view_get_insert_spaces_instead_of_tabs
							(GtkSourceView   *view);

void		 gtk_source_view_set_indent_on_tab 	(GtkSourceView   *view,
							 gboolean         enable);

gboolean	 gtk_source_view_get_indent_on_tab 	(GtkSourceView   *view);

void		 gtk_source_view_indent_lines		(GtkSourceView   *view,
							 GtkTextIter     *start,
							 GtkTextIter     *end);

void		 gtk_source_view_unindent_lines		(GtkSourceView   *view,
							 GtkTextIter     *start,
							 GtkTextIter     *end);

void		 gtk_source_view_set_highlight_current_line
							(GtkSourceView   *view,
							 gboolean         highlight);

gboolean 	 gtk_source_view_get_highlight_current_line
							(GtkSourceView   *view);

void		 gtk_source_view_set_show_right_margin 	(GtkSourceView   *view,
							 gboolean         show);

gboolean 	 gtk_source_view_get_show_right_margin 	(GtkSourceView   *view);

void		 gtk_source_view_set_right_margin_position
					 		(GtkSourceView   *view,
							 guint            pos);

guint		 gtk_source_view_get_right_margin_position
					 		(GtkSourceView   *view);

void 		 gtk_source_view_set_show_line_marks    (GtkSourceView   *view,
							 gboolean         show);

gboolean	 gtk_source_view_get_show_line_marks    (GtkSourceView   *view);

void             gtk_source_view_set_mark_attributes    (GtkSourceView           *view,
                                                         const gchar             *category,
                                                         GtkSourceMarkAttributes *attributes,
                                                         gint                     priority);

GtkSourceMarkAttributes *
                 gtk_source_view_get_mark_attributes    (GtkSourceView           *view,
                                                         const gchar             *category,
                                                         gint                    *priority);

void		 gtk_source_view_set_smart_backspace	(GtkSourceView   *view,
							 gboolean        smart_backspace);

gboolean	 gtk_source_view_get_smart_backspace	(GtkSourceView   *view);

void		 gtk_source_view_set_smart_home_end	(GtkSourceView             *view,
							 GtkSourceSmartHomeEndType  smart_home_end);

GtkSourceSmartHomeEndType
		 gtk_source_view_get_smart_home_end	(GtkSourceView   *view);

void		 gtk_source_view_set_draw_spaces	(GtkSourceView            *view,
							 GtkSourceDrawSpacesFlags  flags);

GtkSourceDrawSpacesFlags
		 gtk_source_view_get_draw_spaces	(GtkSourceView   *view);

guint		 gtk_source_view_get_visual_column	(GtkSourceView     *view,
							 const GtkTextIter *iter);

GtkSourceCompletion *
		 gtk_source_view_get_completion		(GtkSourceView   *view);

GtkSourceGutter *gtk_source_view_get_gutter		(GtkSourceView     *view,
                                                         GtkTextWindowType  window_type);

void		 gtk_source_view_set_background_pattern	(GtkSourceView                  *view,
                                                         GtkSourceBackgroundPatternType  background_pattern);

GtkSourceBackgroundPatternType
		 gtk_source_view_get_background_pattern	(GtkSourceView   *view);

G_END_DECLS

#endif /* end of __GTK_SOURCE_VIEW_H__ */
