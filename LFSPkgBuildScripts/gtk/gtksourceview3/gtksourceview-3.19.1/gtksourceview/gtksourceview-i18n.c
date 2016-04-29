/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8; coding: utf-8 -*- *
 * Copyright (C) 1997, 1998, 1999, 2000 Free Software Foundation
 * All rights reserved.
 *
 * This file is part of GtkSourceView
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <string.h>

#include "gtksourceview-i18n.h"

#ifdef OS_OSX

#include <Cocoa/Cocoa.h>

static gchar *
dirs_os_x_get_bundle_resource_dir (void)
{
	NSAutoreleasePool *pool;
	gchar *str = NULL;
	NSString *path;

	pool = [[NSAutoreleasePool alloc] init];

	if ([[NSBundle mainBundle] bundleIdentifier] == nil)
	{
		[pool release];
		return NULL;
	}

	path = [[NSBundle mainBundle] resourcePath];

	if (!path)
	{
		[pool release];
		return NULL;
	}

	str = g_strdup ([path UTF8String]);
	[pool release];
	return str;
}

static gchar *
dirs_os_x_get_locale_dir (void)
{
	gchar *res_dir;
	gchar *ret;

	res_dir = dirs_os_x_get_bundle_resource_dir ();

	if (res_dir == NULL)
	{
		ret = g_build_filename (DATADIR, "locale", NULL);
	}
	else
	{
		ret = g_build_filename (res_dir, "share", "locale", NULL);
		g_free (res_dir);
	}

	return ret;
}

#endif

static gchar *
get_locale_dir (void)
{
	gchar *locale_dir;

#ifdef G_OS_WIN32
	gchar *win32_dir;

	win32_dir = g_win32_get_package_installation_directory_of_module (NULL);

	locale_dir = g_build_filename (win32_dir, "share", "locale", NULL);

	g_free (win32_dir);
#elif defined (OS_OSX)
	locale_dir = dirs_os_x_get_locale_dir ();
#else
	locale_dir = g_build_filename (DATADIR, "locale", NULL);
#endif

	return locale_dir;
}

/*
 * Small hack since we don't have a proper place where
 * do gettext initialization.
 */
const gchar *
_gtksourceview_gettext (const gchar *msgid)
{
	static gboolean initialized = FALSE;

	G_GNUC_UNUSED const char translator_credits[] = N_("translator-credits");
	/* above is a dummy variable to get the string into po files */

	if (G_UNLIKELY (!initialized))
	{
		gchar *locale_dir;

		locale_dir = get_locale_dir ();

		bindtextdomain (GETTEXT_PACKAGE, locale_dir);
		g_free (locale_dir);

		bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
		initialized = TRUE;
	}

	return g_dgettext (GETTEXT_PACKAGE, msgid);
}

/**
 * _gtksourceview_dgettext:
 *
 * Try to translate string from given domain. It returns
 * duplicated string which must be freed with g_free().
 */
#ifdef ENABLE_NLS
char *
_gtksourceview_dgettext (const char *domain,
                         const char *string)
{
	gchar *tmp;
	const gchar *translated;

	g_return_val_if_fail (string != NULL, NULL);

	if (domain == NULL)
		return g_strdup (_gtksourceview_gettext (string));

	translated = dgettext (domain, string);

	if (strcmp (translated, string) == 0)
		return g_strdup (_gtksourceview_gettext (string));

	if (g_utf8_validate (translated, -1, NULL))
		return g_strdup (translated);

	tmp = g_locale_to_utf8 (translated, -1, NULL, NULL, NULL);

	if (tmp == NULL)
		return g_strdup (string);
	else
		return tmp;
}
#else
char *
_gtksourceview_dgettext (const char *domain,
                         const char *string)
{
	return g_strdup (string);
}
#endif
