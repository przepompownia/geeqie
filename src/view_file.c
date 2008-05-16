/*
 * Geeqie
 * Copyright (C) 2008 The Geeqie Team
 *
 * Author: Laurent Monin
 *
 * This software is released under the GNU General Public License (GNU GPL).
 * Please read the included file COPYING for more information.
 * This software comes with no warranty of any kind, use at your own risk!
 */

#include "main.h"
#include "view_file.h"

#include "editors.h"
#include "info.h"
#include "layout.h"
#include "menu.h"
#include "ui_menu.h"
#include "utilops.h"
#include "view_file_list.h"
#include "view_file_icon.h"

/*
 *-----------------------------------------------------------------------------
 * signals
 *-----------------------------------------------------------------------------
 */

void vf_send_update(ViewFile *vf)
{
	if (vf->func_status) vf->func_status(vf, vf->data_status);
}

/*
 *-----------------------------------------------------------------------------
 * misc
 *-----------------------------------------------------------------------------
 */

void vf_sort_set(ViewFile *vf, SortType type, gint ascend)
{
	switch(vf->type)
	{
	case FILEVIEW_LIST: vflist_sort_set(vf, type, ascend); break;
	case FILEVIEW_ICON: vficon_sort_set(vf, type, ascend); break;
	}
}

/*
 *-----------------------------------------------------------------------------
 * row stuff
 *-----------------------------------------------------------------------------
 */

FileData *vf_index_get_data(ViewFile *vf, gint row)
{
	FileData *fd = NULL;

	switch(vf->type)
	{
	case FILEVIEW_LIST: fd = vflist_index_get_data(vf, row); break;
	case FILEVIEW_ICON: fd = vficon_index_get_data(vf, row); break;
	}

	return fd;
}

gint vf_index_by_path(ViewFile *vf, const gchar *path)
{
	gint index = -1;

	switch(vf->type)
	{
	case FILEVIEW_LIST: index = vflist_index_by_path(vf, path); break;
	case FILEVIEW_ICON: index = vficon_index_by_path(vf, path); break;
	}

	return index;
}

gint vf_count(ViewFile *vf, gint64 *bytes)
{
	gint count = 0;

	switch(vf->type)
	{
	case FILEVIEW_LIST: count = vflist_count(vf, bytes); break;
	case FILEVIEW_ICON: count = vficon_count(vf, bytes); break;
	}

	return count;
}

GList *vf_get_list(ViewFile *vf)
{
	GList *list = NULL;

	switch(vf->type)
	{
	case FILEVIEW_LIST: list = vflist_get_list(vf); break;
	case FILEVIEW_ICON: list = vficon_get_list(vf); break;
	}

	return list;
}


/*
 *-------------------------------------------------------------------
 * keyboard
 *-------------------------------------------------------------------
 */

static gint vf_press_key_cb(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
	ViewFile *vf = data;
	gint ret = FALSE;

	switch(vf->type)
	{
	case FILEVIEW_LIST: ret = vflist_press_key_cb(widget, event, data); break;
	case FILEVIEW_ICON: ret = vficon_press_key_cb(widget, event, data); break;
	}

	return ret;
}

/*
 *-------------------------------------------------------------------
 * mouse
 *-------------------------------------------------------------------
 */

static gint vf_press_cb(GtkWidget *widget, GdkEventButton *bevent, gpointer data)
{
	ViewFile *vf = data;
	gint ret = FALSE;

	switch(vf->type)
	{
	case FILEVIEW_LIST: ret = vflist_press_cb(widget, bevent, data); break;
	case FILEVIEW_ICON: ret = vficon_press_cb(widget, bevent, data); break;
	}

	return ret;
}

static gint vf_release_cb(GtkWidget *widget, GdkEventButton *bevent, gpointer data)
{
	ViewFile *vf = data;
	gint ret = FALSE;

	switch(vf->type)
	{
	case FILEVIEW_LIST: ret = vflist_release_cb(widget, bevent, data); break;
	case FILEVIEW_ICON: ret = vficon_release_cb(widget, bevent, data); break;
	}

	return ret;
}


/*
 *-----------------------------------------------------------------------------
 * selections
 *-----------------------------------------------------------------------------
 */

gint vf_selection_count(ViewFile *vf, gint64 *bytes)
{
	gint count = 0;

	switch(vf->type)
	{
	case FILEVIEW_LIST: count = vflist_selection_count(vf, bytes); break;
	case FILEVIEW_ICON: count = vficon_selection_count(vf, bytes); break;
	}

	return count;
}

GList *vf_selection_get_list(ViewFile *vf)
{
	GList *list = NULL;

	switch(vf->type)
	{
	case FILEVIEW_LIST: list = vflist_selection_get_list(vf); break;
	case FILEVIEW_ICON: list = vficon_selection_get_list(vf); break;
	}

	return list;
}

GList *vf_selection_get_list_by_index(ViewFile *vf)
{
	GList *list = NULL;

	switch(vf->type)
	{
	case FILEVIEW_LIST: list = vflist_selection_get_list_by_index(vf); break;
	case FILEVIEW_ICON: list = vficon_selection_get_list_by_index(vf); break;
	}

	return list;
}

void vf_select_all(ViewFile *vf)
{
	switch(vf->type)
	{
	case FILEVIEW_LIST: vflist_select_all(vf); break;
	case FILEVIEW_ICON: vficon_select_all(vf); break;
	}
}

void vf_select_none(ViewFile *vf)
{
	switch(vf->type)
	{
	case FILEVIEW_LIST: vflist_select_none(vf); break;
	case FILEVIEW_ICON: vficon_select_none(vf); break;
	}
}

void vf_select_invert(ViewFile *vf)
{
	switch(vf->type)
	{
	case FILEVIEW_LIST: vflist_select_invert(vf); break;
	case FILEVIEW_ICON: vficon_select_invert(vf); break;
	}
}

void vf_select_by_fd(ViewFile *vf, FileData *fd)
{
	switch(vf->type)
	{
	case FILEVIEW_LIST: vflist_select_by_fd(vf, fd); break;
	case FILEVIEW_ICON: vficon_select_by_fd(vf, fd); break;
	}
}

void vf_mark_to_selection(ViewFile *vf, gint mark, MarkToSelectionMode mode)
{
	switch(vf->type)
	{
	case FILEVIEW_LIST: vflist_mark_to_selection(vf, mark, mode); break;
	case FILEVIEW_ICON: vficon_mark_to_selection(vf, mark, mode); break;
	}
}

void vf_selection_to_mark(ViewFile *vf, gint mark, SelectionToMarkMode mode)
{
	switch(vf->type)
	{
	case FILEVIEW_LIST: vflist_selection_to_mark(vf, mark, mode); break;
	case FILEVIEW_ICON: vficon_selection_to_mark(vf, mark, mode); break;
	}
}

/*
 *-----------------------------------------------------------------------------
 * dnd
 *-----------------------------------------------------------------------------
 */


static void vf_dnd_init(ViewFile *vf)
{
	switch(vf->type)
	{
	case FILEVIEW_LIST: vflist_dnd_init(vf); break;
	case FILEVIEW_ICON: vficon_dnd_init(vf); break;
	}
}

/*
 *-----------------------------------------------------------------------------
 * pop-up menu
 *-----------------------------------------------------------------------------
 */

GList *vf_pop_menu_file_list(ViewFile *vf)
{
	GList *ret = NULL;

	switch(vf->type)
	{
	case FILEVIEW_LIST: ret = vflist_pop_menu_file_list(vf); break;
	case FILEVIEW_ICON: ret = vficon_pop_menu_file_list(vf); break;
	}

	return ret;
}

static void vf_pop_menu_edit_cb(GtkWidget *widget, gpointer data)
{
	ViewFile *vf;
	gint n;
	GList *list;

	vf = submenu_item_get_data(widget);
	n = GPOINTER_TO_INT(data);

	if (!vf) return;

	list = vf_pop_menu_file_list(vf);
	start_editor_from_filelist(n, list);
	filelist_free(list);
}

static void vf_pop_menu_info_cb(GtkWidget *widget, gpointer data)
{
	ViewFile *vf = data;

	info_window_new(NULL, vf_pop_menu_file_list(vf), NULL);
}

static void vf_pop_menu_view_cb(GtkWidget *widget, gpointer data)
{
	ViewFile *vf = data;

	switch(vf->type)
	{
	case FILEVIEW_LIST: vflist_pop_menu_view_cb(widget, data); break;
	case FILEVIEW_ICON: vficon_pop_menu_view_cb(widget, data); break;
	}
}

static void vf_pop_menu_copy_cb(GtkWidget *widget, gpointer data)
{
	ViewFile *vf = data;

	file_util_copy(NULL, vf_pop_menu_file_list(vf), NULL, vf->listview);
}

static void vf_pop_menu_move_cb(GtkWidget *widget, gpointer data)
{
	ViewFile *vf = data;

	file_util_move(NULL, vf_pop_menu_file_list(vf), NULL, vf->listview);
}

static void vf_pop_menu_rename_cb(GtkWidget *widget, gpointer data)
{
	ViewFile *vf = data;

	switch(vf->type)
	{
	case FILEVIEW_LIST: vflist_pop_menu_rename_cb(widget, data); break;
	case FILEVIEW_ICON: vficon_pop_menu_rename_cb(widget, data); break;
	}
}

static void vf_pop_menu_delete_cb(GtkWidget *widget, gpointer data)
{
	ViewFile *vf = data;

	file_util_delete(NULL, vf_pop_menu_file_list(vf), vf->listview);
}

static void vf_pop_menu_copy_path_cb(GtkWidget *widget, gpointer data)
{
	ViewFile *vf = data;

	file_util_copy_path_list_to_clipboard(vf_pop_menu_file_list(vf));
}

static void vf_pop_menu_sort_cb(GtkWidget *widget, gpointer data)
{
	ViewFile *vf;
	SortType type;

	if (!gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(widget))) return;

	vf = submenu_item_get_data(widget);
	if (!vf) return;

	type = (SortType)GPOINTER_TO_INT(data);

	if (vf->layout)
		{
		layout_sort_set(vf->layout, type, vf->sort_ascend);
		}
	else
		{
		vf_sort_set(vf, type, vf->sort_ascend);
		}
}

static void vf_pop_menu_sort_ascend_cb(GtkWidget *widget, gpointer data)
{
	ViewFile *vf = data;

	if (vf->layout)
		{
		layout_sort_set(vf->layout, vf->sort_method, !vf->sort_ascend);
		}
	else
		{
		vf_sort_set(vf, vf->sort_method, !vf->sort_ascend);
		}
}

static void vf_pop_menu_sel_mark_cb(GtkWidget *widget, gpointer data)
{
	ViewFile *vf = data;
	vf_mark_to_selection(vf, vf->active_mark, MTS_MODE_SET);
}

static void vf_pop_menu_sel_mark_and_cb(GtkWidget *widget, gpointer data)
{
	ViewFile *vf = data;
	vf_mark_to_selection(vf, vf->active_mark, MTS_MODE_AND);
}

static void vf_pop_menu_sel_mark_or_cb(GtkWidget *widget, gpointer data)
{
	ViewFile *vf = data;
	vf_mark_to_selection(vf, vf->active_mark, MTS_MODE_OR);
}

static void vf_pop_menu_sel_mark_minus_cb(GtkWidget *widget, gpointer data)
{
	ViewFile *vf = data;
	vf_mark_to_selection(vf, vf->active_mark, MTS_MODE_MINUS);
}

static void vf_pop_menu_set_mark_sel_cb(GtkWidget *widget, gpointer data)
{
	ViewFile *vf = data;
	vf_selection_to_mark(vf, vf->active_mark, STM_MODE_SET);
}

static void vf_pop_menu_res_mark_sel_cb(GtkWidget *widget, gpointer data)
{
	ViewFile *vf = data;
	vf_selection_to_mark(vf, vf->active_mark, STM_MODE_RESET);
}

static void vf_pop_menu_toggle_mark_sel_cb(GtkWidget *widget, gpointer data)
{
	ViewFile *vf = data;
	vf_selection_to_mark(vf, vf->active_mark, STM_MODE_TOGGLE);
}

static void vf_pop_menu_toggle_view_type_cb(GtkWidget *widget, gpointer data)
{
	ViewFile *vf = data;
	
	if (!vf->layout) return;

	switch(vf->layout->file_view_type)
	{
	case FILEVIEW_LIST:
		layout_views_set(vf->layout, vf->layout->dir_view_type, FILEVIEW_ICON);
		break;
	case FILEVIEW_ICON:
		layout_views_set(vf->layout, vf->layout->dir_view_type, FILEVIEW_LIST);
		break;
	}
}

static void vf_pop_menu_refresh_cb(GtkWidget *widget, gpointer data)
{
	ViewFile *vf = data;

	switch(vf->type)
	{
	case FILEVIEW_LIST: vflist_pop_menu_refresh_cb(widget, data); break;
	case FILEVIEW_ICON: vficon_pop_menu_refresh_cb(widget, data); break;
	}
}

static void vf_popup_destroy_cb(GtkWidget *widget, gpointer data)
{
	ViewFile *vf = data;

	switch(vf->type)
	{
	case FILEVIEW_LIST: vflist_popup_destroy_cb(widget, data); break;
	case FILEVIEW_ICON: vficon_popup_destroy_cb(widget, data); break;
	}
}

GtkWidget *vf_pop_menu(ViewFile *vf)
{
	GtkWidget *menu;
	GtkWidget *item;
	GtkWidget *submenu;
	gint active = 0;

	switch(vf->type)
	{
	case FILEVIEW_LIST:
		vflist_color_set(vf, VFLIST_INFO(vf, click_fd), TRUE);
		active = (VFLIST_INFO(vf, click_fd) != NULL);
		break;
	case FILEVIEW_ICON:
		active = (VFICON_INFO(vf, click_id) != NULL);
		break;
	}

	menu = popup_menu_short_lived();

	g_signal_connect(G_OBJECT(menu), "destroy",
			 G_CALLBACK(vf_popup_destroy_cb), vf);

	if (vf->clicked_mark > 0)
		{
		gint mark = vf->clicked_mark;
		gchar *str_set_mark = g_strdup_printf(_("_Set mark %d"), mark);
		gchar *str_res_mark = g_strdup_printf(_("_Reset mark %d"), mark);
		gchar *str_toggle_mark = g_strdup_printf(_("_Toggle mark %d"), mark);
		gchar *str_sel_mark = g_strdup_printf(_("_Select mark %d"), mark);
		gchar *str_sel_mark_or = g_strdup_printf(_("_Add mark %d"), mark);
		gchar *str_sel_mark_and = g_strdup_printf(_("_Intersection with mark %d"), mark);
		gchar *str_sel_mark_minus = g_strdup_printf(_("_Unselect mark %d"), mark);

		g_assert(mark >= 1 && mark <= FILEDATA_MARKS_SIZE);

		vf->active_mark = mark;
		vf->clicked_mark = 0;

		menu_item_add_sensitive(menu, str_set_mark, active,
					G_CALLBACK(vf_pop_menu_set_mark_sel_cb), vf);

		menu_item_add_sensitive(menu, str_res_mark, active,
					G_CALLBACK(vf_pop_menu_res_mark_sel_cb), vf);

		menu_item_add_sensitive(menu, str_toggle_mark, active,
					G_CALLBACK(vf_pop_menu_toggle_mark_sel_cb), vf);

		menu_item_add_divider(menu);

		menu_item_add_sensitive(menu, str_sel_mark, active,
					G_CALLBACK(vf_pop_menu_sel_mark_cb), vf);
		menu_item_add_sensitive(menu, str_sel_mark_or, active,
					G_CALLBACK(vf_pop_menu_sel_mark_or_cb), vf);
		menu_item_add_sensitive(menu, str_sel_mark_and, active,
					G_CALLBACK(vf_pop_menu_sel_mark_and_cb), vf);
		menu_item_add_sensitive(menu, str_sel_mark_minus, active,
					G_CALLBACK(vf_pop_menu_sel_mark_minus_cb), vf);

		menu_item_add_divider(menu);

		g_free(str_set_mark);
		g_free(str_res_mark);
		g_free(str_toggle_mark);
		g_free(str_sel_mark);
		g_free(str_sel_mark_and);
		g_free(str_sel_mark_or);
		g_free(str_sel_mark_minus);
		}

	submenu_add_edit(menu, &item, G_CALLBACK(vf_pop_menu_edit_cb), vf);
	gtk_widget_set_sensitive(item, active);

	menu_item_add_stock_sensitive(menu, _("_Properties"), GTK_STOCK_PROPERTIES, active,
				      G_CALLBACK(vf_pop_menu_info_cb), vf);
	menu_item_add_stock_sensitive(menu, _("View in _new window"), GTK_STOCK_NEW, active,
				      G_CALLBACK(vf_pop_menu_view_cb), vf);

	menu_item_add_divider(menu);
	menu_item_add_stock_sensitive(menu, _("_Copy..."), GTK_STOCK_COPY, active,
				      G_CALLBACK(vf_pop_menu_copy_cb), vf);
	menu_item_add_sensitive(menu, _("_Move..."), active,
				G_CALLBACK(vf_pop_menu_move_cb), vf);
	menu_item_add_sensitive(menu, _("_Rename..."), active,
				G_CALLBACK(vf_pop_menu_rename_cb), vf);
	menu_item_add_stock_sensitive(menu, _("_Delete..."), GTK_STOCK_DELETE, active,
				      G_CALLBACK(vf_pop_menu_delete_cb), vf);
	if (options->show_copy_path)
		menu_item_add_sensitive(menu, _("_Copy path"), active,
					G_CALLBACK(vf_pop_menu_copy_path_cb), vf);

	menu_item_add_divider(menu);

	submenu = submenu_add_sort(NULL, G_CALLBACK(vf_pop_menu_sort_cb), vf,
				   FALSE, FALSE, TRUE, vf->sort_method);
	menu_item_add_divider(submenu);
	menu_item_add_check(submenu, _("Ascending"), vf->sort_ascend,
			    G_CALLBACK(vf_pop_menu_sort_ascend_cb), vf);

	item = menu_item_add(menu, _("_Sort"), NULL, NULL);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), submenu);

	menu_item_add_check(menu, _("View as _icons"), (vf->type == FILEVIEW_ICON),
			    G_CALLBACK(vf_pop_menu_toggle_view_type_cb), vf);

	switch(vf->type)
	{
	case FILEVIEW_LIST:
		menu_item_add_check(menu, _("Show _thumbnails"), VFLIST_INFO(vf, thumbs_enabled),
				    G_CALLBACK(vflist_pop_menu_thumbs_cb), vf);
		break;
	case FILEVIEW_ICON:
		menu_item_add_check(menu, _("Show filename _text"), VFICON_INFO(vf, show_text),
				    G_CALLBACK(vficon_pop_menu_show_names_cb), vf);
		break;
	}
	
	menu_item_add_stock(menu, _("Re_fresh"), GTK_STOCK_REFRESH, G_CALLBACK(vf_pop_menu_refresh_cb), vf);

	return menu;
}

gint vf_refresh(ViewFile *vf)
{
	gint ret = FALSE;

	switch(vf->type)
	{
	case FILEVIEW_LIST: ret = vflist_refresh(vf); break;
	case FILEVIEW_ICON: ret = vficon_refresh(vf); break;
	}

	return ret;
}

gint vf_set_path(ViewFile *vf, const gchar *path)
{
	gint ret = FALSE;

	switch(vf->type)
	{
	case FILEVIEW_LIST: ret = vflist_set_path(vf, path); break;
	case FILEVIEW_ICON: ret = vficon_set_path(vf, path); break;
	}
	
	return ret;
}

static void vf_destroy_cb(GtkWidget *widget, gpointer data)
{
	ViewFile *vf = data;

	switch(vf->type)
	{
	case FILEVIEW_LIST: vflist_destroy_cb(widget, data); break;
	case FILEVIEW_ICON: vficon_destroy_cb(widget, data); break;
	}

	if (vf->popup)
		{
		g_signal_handlers_disconnect_matched(G_OBJECT(vf->popup), G_SIGNAL_MATCH_DATA,
						     0, 0, 0, NULL, vf);
		gtk_widget_destroy(vf->popup);
		}

	g_free(vf->path);
	g_free(vf->info);
	g_free(vf);
}

ViewFile *vf_new(FileViewType type, const gchar *path)
{
	ViewFile *vf;

	vf = g_new0(ViewFile, 1);
	vf->type = type;

	vf->info = NULL;
	vf->path = NULL;
	vf->list = NULL;

	vf->sort_method = SORT_NAME;
	vf->sort_ascend = TRUE;
	
	vf->thumbs_running = FALSE;
	vf->thumbs_count = 0;
	vf->thumbs_loader = NULL;
	vf->thumbs_filedata = NULL;

	vf->popup = NULL;

	vf->widget = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(vf->widget), GTK_SHADOW_IN);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(vf->widget),
				       GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	
	g_signal_connect(G_OBJECT(vf->widget), "destroy",
			 G_CALLBACK(vf_destroy_cb), vf);

	switch(type)
	{
	case FILEVIEW_LIST: vf = vflist_new(vf, path); break;
	case FILEVIEW_ICON: vf = vficon_new(vf, path); break;
	}

	vf_dnd_init(vf);

	g_signal_connect(G_OBJECT(vf->listview), "key_press_event",
			 G_CALLBACK(vf_press_key_cb), vf);
	g_signal_connect(G_OBJECT(vf->listview), "button_press_event",
			 G_CALLBACK(vf_press_cb), vf);
	g_signal_connect(G_OBJECT(vf->listview), "button_release_event",
			 G_CALLBACK(vf_release_cb), vf);

	gtk_container_add(GTK_CONTAINER(vf->widget), vf->listview);
	gtk_widget_show(vf->listview);

	if (path) vf_set_path(vf, path);

	return vf;
}

void vf_set_status_func(ViewFile *vf, void (*func)(ViewFile *vf, gpointer data), gpointer data)
{
	vf->func_status = func;
	vf->data_status = data;
}

void vf_set_thumb_status_func(ViewFile *vf, void (*func)(ViewFile *vf, gdouble val, const gchar *text, gpointer data), gpointer data)
{
	vf->func_thumb_status = func;
	vf->data_thumb_status = data;
}

void vf_thumb_set(ViewFile *vf, gint enable)
{
	switch(vf->type)
	{
	case FILEVIEW_LIST: vflist_thumb_set(vf, enable); break;
	case FILEVIEW_ICON: /*vficon_thumb_set(vf, enable);*/ break;
	}
}

void vf_marks_set(ViewFile *vf, gint enable)
{
	switch(vf->type)
	{
	case FILEVIEW_LIST: vflist_marks_set(vf, enable); break;
	case FILEVIEW_ICON: /*vficon_marks_set(vf, enable);*/ break;
	}
}

void vf_set_layout(ViewFile *vf, LayoutWindow *layout)
{
	vf->layout = layout;
}

/*
 *-----------------------------------------------------------------------------
 * maintenance (for rename, move, remove)
 *-----------------------------------------------------------------------------
 */

gint vf_maint_renamed(ViewFile *vf, FileData *fd)
{
	gint ret = FALSE;

	switch(vf->type)
	{
	case FILEVIEW_LIST: ret = vflist_maint_renamed(vf, fd); break;
	case FILEVIEW_ICON: ret = vficon_maint_renamed(vf, fd); break;
	}

	return ret;
}

gint vf_maint_removed(ViewFile *vf, FileData *fd, GList *ignore_list)
{
	gint ret = FALSE;

	switch(vf->type)
	{
	case FILEVIEW_LIST: ret = vflist_maint_removed(vf, fd, ignore_list); break;
	case FILEVIEW_ICON: ret = vficon_maint_removed(vf, fd, ignore_list); break;
	}

	return ret;
}

gint vf_maint_moved(ViewFile *vf, FileData *fd, GList *ignore_list)
{
	gint ret = FALSE;

	switch(vf->type)
	{
	case FILEVIEW_LIST: ret = vflist_maint_moved(vf, fd, ignore_list); break;
	case FILEVIEW_ICON: ret = vficon_maint_moved(vf, fd, ignore_list); break;
	}

	return ret;
}
