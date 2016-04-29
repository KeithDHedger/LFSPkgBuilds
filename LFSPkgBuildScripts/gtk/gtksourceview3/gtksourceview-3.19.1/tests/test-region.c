/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8; coding: utf-8 -*- */
/*
 * This file is part of GtkSourceView
 *
 * Copyright (C) 2003 - Gustavo Giráldez
 * Copyright (C) 2006, 2013 - Paolo Borelli
 * Copyright (C) 2013 - Sébastien Wilmet
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

#include <gtk/gtk.h>
#include "gtksourceview/gtktextregion.h"

static void
test_region (void)
{
	GtkTextBuffer *buffer;
	GtkTextRegion *region, *intersection;
	GtkTextRegionIterator reg_iter;
	GtkTextIter iter1, iter2;
	gint i;

#define NUM_OPS 23

	gint ops [NUM_OPS][3] = {
		/* add/remove a 0-length region */
		{  1,  5,  5 },
		{ -1,  5,  5 },
		/* add a region */
		{  1,  5, 10 },
		/* add two adjacent regions */
		{  1,  3,  5 },
		{  1, 10, 12 },
		/* remove all */
		{ -1,  1, 15 },
		/* add two separate regions */
		{  1,  5, 10 },
		{  1, 15, 20 },
		/* join them */
		{  1,  7, 17 },
		/* remove from the middle */
		{ -1, 10, 15 },
		/* exactly remove a subregion */
		{ -1, 15, 20 },
		/* try to remove an adjacent region */
		{ -1, 10, 20 },
		/* try to remove an adjacent region */
		{ -1,  0,  5 },
		/* add another separate */
		{  1, 15, 20 },
		/* join with excess */
		{  1,  0, 25 },
		/* do two holes */
		{ -1,  5, 10 },
		{ -1, 15, 20 },
		/* remove the middle subregion */
		{ -1,  8, 22 },
		/* add the subregion we just removed */
		{  1, 10, 15 },
		/* remove the middle subregion */
		{ -1,  3, 17 },
		/* add the subregion we just removed */
		{  1, 10, 15 },
		/* remove the middle subregion */
		{ -1,  2, 23 },
		/* add the subregion we just removed */
		{  1, 10, 15 },
	};

#define NUM_INTERSECTS 5

	gint inter [NUM_INTERSECTS][2] = {
		{  0, 25 },
		{ 10, 15 },
		{  8, 17 },
		{  1, 24 },
		{  3,  7 }
	};

	buffer = gtk_text_buffer_new (NULL);
	region = gtk_text_region_new (buffer);

	gtk_text_buffer_get_start_iter (buffer, &iter1);
	gtk_text_buffer_insert (buffer, &iter1, "This is a test of GtkTextRegion", -1);

	gtk_text_region_get_iterator (region, &reg_iter, 0);
	if (!gtk_text_region_iterator_is_end (&reg_iter)) {
		g_print ("problem fetching iterator for an empty region\n");
		g_assert_not_reached ();
	}

	for (i = 0; i < NUM_OPS; i++) {
		const gchar *op_name;

		gtk_text_buffer_get_iter_at_offset (buffer, &iter1, ops [i][1]);
		gtk_text_buffer_get_iter_at_offset (buffer, &iter2, ops [i][2]);

		if (ops [i][0] > 0) {
			op_name = "added";
			gtk_text_region_add (region, &iter1, &iter2);
		} else {
			op_name = "deleted";
			gtk_text_region_subtract (region, &iter1, &iter2);
		}
		g_print ("%s %d-%d\n", op_name, ops [i][1], ops [i][2]);

		gtk_text_region_debug_print (region);
	}

	for (i = 0; i < NUM_INTERSECTS; i++) {
		gtk_text_buffer_get_iter_at_offset (buffer, &iter1, inter [i][0]);
		gtk_text_buffer_get_iter_at_offset (buffer, &iter2, inter [i][1]);

		g_print ("intersect %d-%d\n", inter [i][0], inter [i][1]);
		intersection = gtk_text_region_intersect (region, &iter1, &iter2);
		if (intersection) {
			gtk_text_region_debug_print (intersection);
			gtk_text_region_destroy (intersection);
		} else {
			g_print ("no intersection\n");
		}
	}

	i = 0;
	gtk_text_region_get_iterator (region, &reg_iter, 0);

	while (!gtk_text_region_iterator_is_end (&reg_iter))
	{
		GtkTextIter s, e, s1, e1;

		gtk_text_region_iterator_get_subregion (&reg_iter,
							&s, &e);
		gtk_text_region_nth_subregion (region, i, &s1, &e1);

		if (!gtk_text_iter_equal (&s, &s1) ||
		    !gtk_text_iter_equal (&e, &e1))
		{
			g_print ("problem iterating\n");
			g_assert_not_reached ();
		}

		++i;
		gtk_text_region_iterator_next (&reg_iter);
	}

	if (i != gtk_text_region_subregions (region))
	{
		g_print ("problem iterating all subregions\n");
		g_assert_not_reached ();
	}

	g_print ("iterated %d subregions\n", i);

	gtk_text_region_destroy (region);
	g_object_unref (buffer);
}

int
main (int argc, char** argv)
{
	gtk_test_init (&argc, &argv);

	g_test_add_func ("/Region/region", test_region);

	return g_test_run();
}
